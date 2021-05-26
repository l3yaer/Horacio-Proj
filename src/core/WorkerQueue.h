#ifndef _WORKERQUEUE_H_
#define _WORKERQUEUE_H_

#include <vector>
#include <deque>
#include <utility>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "Singleton.h"

class Job {
public:
	struct Response {
		bool success;
		std::string msg;

		Response(bool success, const std::string msg) : success(success), msg(msg)
		{
		}
	};

	virtual Response execute() = 0;
	virtual void notify(const Response &) = 0;

	bool syncronous_response = false;
};

class LambdaJob : public Job {
public:
	template <class EXECUTE_FN, class RESPONSE_HANDLER>
	LambdaJob(EXECUTE_FN &&exec_fn, RESPONSE_HANDLER &&response_handler, bool sync_response = false)
	{
		this->execute_fn = std::forward<EXECUTE_FN>(exec_fn);
		this->notify_fn = std::forward<RESPONSE_HANDLER>(response_handler);
		this->syncronous_response = sync_response;
	}

	virtual Job::Response execute()
	{
		return execute_fn();
	}

	virtual void notify(const Job::Response &response)
	{
		notify_fn(response);
	}

private:
	std::function<Job::Response()> execute_fn;
	std::function<void(const Job::Response &)> notify_fn;
};

class WorkerQueue : public Singleton<WorkerQueue> {
protected:
	struct Func {
		WorkerQueue *queue;
		Func(WorkerQueue *queue) : queue(queue)
		{
		}

		void operator()();
		void operator()() const;
	};

public:
	WorkerQueue(int num_of_workers);
	~WorkerQueue();

	void start(bool force_restart);
	void process_jobs();
	void process_sync_responses();
	void add_job(Job *const);

private:
	void shutdown();
	void wait_request();
	void process_request();

	bool running;
	int num_of_workers;
	Func worker_func;

	std::deque<Job *> request_queue;
	std::vector<Job *> process_queue;
	std::vector<std::pair<Job *, Job::Response> > response_queue;

	std::vector<std::thread *> workers;
	mutable std::recursive_mutex request_mutex;
	mutable std::recursive_mutex process_mutex;
	mutable std::recursive_mutex response_mutex;
	std::condition_variable_any request_cond;
};

#endif //_WORKERQUEUE_H_
