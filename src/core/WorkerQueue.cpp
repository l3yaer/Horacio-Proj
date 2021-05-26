#include "WorkerQueue.h"

IMPLEMENT_SINGLETON(WorkerQueue)

WorkerQueue::WorkerQueue(int num_of_workers)
		: Singleton<WorkerQueue>(), num_of_workers(num_of_workers), worker_func(WorkerQueue::Func(this)), running(false)
{
}

WorkerQueue::~WorkerQueue()
{
	shutdown();
}

void WorkerQueue::start(bool force_restart)
{
	if (running) {
		if (force_restart)
			shutdown();
		else
			return;
	}

	running = true;

	for (int i = 0; i < num_of_workers; ++i) {
		std::thread *t = new std::thread(this->worker_func);
		workers.push_back(t);
	}
}

void WorkerQueue::shutdown()
{
	if (!running)
		return;

	running = false;

	request_cond.notify_all();
	//TODO: abort all;

	for (auto thread : workers) {
		thread->join();
		delete thread;
	}

	workers.clear();
}

void WorkerQueue::process_jobs()
{
	while (running) {
		wait_request();
		process_request();
	}
}

void WorkerQueue::wait_request()
{
	std::unique_lock<std::recursive_mutex> request_lock(request_mutex);

	if (request_queue.empty())
		request_cond.wait(request_mutex);
}

void WorkerQueue::process_request()
{
	Job *request = nullptr;
	{
		std::unique_lock<std::recursive_mutex> request_lock(request_mutex);
		if (!request_queue.empty()) {
			std::unique_lock<std::recursive_mutex> process_lock(process_mutex);
			request = request_queue.front();
			request_queue.pop_front();
			process_queue.push_back(request);
		}
	}
	if (request != nullptr) {
		Job::Response response = request->execute();
		{
			std::unique_lock<std::recursive_mutex> process_lock(process_mutex);
			for (std::vector<Job *>::iterator it = process_queue.begin(); it < process_queue.end(); ++it) {
				if ((*it) == request) {
					process_queue.erase(it);
					break;
				}
			}
		}
		if (request->syncronous_response) {
			std::unique_lock<std::recursive_mutex> response_lock(response_mutex);
			std::pair<Job *, Job::Response> response_pair(request, response);
			response_queue.push_back(response_pair);
		} else {
			request->notify(response);
			delete request;
		}
	}
}

void WorkerQueue::process_sync_responses()
{
	std::unique_lock<std::recursive_mutex> response_lock(response_mutex);

	for (auto response : response_queue) {
		response.first->notify(response.second);
		delete response.first;
	}

	response_queue.clear();
}

void WorkerQueue::add_job(Job *const job)
{
	if (!running)
		return;

	std::unique_lock<std::recursive_mutex> request_lock(request_mutex);
	request_queue.push_back(job);

	request_cond.notify_one();
}

void WorkerQueue::Func::operator()()
{
	queue->process_jobs();
}

void WorkerQueue::Func::operator()() const
{
	queue->process_jobs();
}
