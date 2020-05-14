#include "JobManager.h"
#include <MTScheduler.h>
#include <stack>

#ifdef MT_THREAD_SANITIZER
#define SMALLEST_STACK_SIZE (566656)
#else
#define SMALLEST_STACK_SIZE (32768)
#endif

class JobExecutor
{
 public:
  static const int WORKER_THREAD_COUNT = 4;
  MT::Thread worker_thread[WORKER_THREAD_COUNT];
  bool done = false;
};

template<> JobManager *Singleton<JobManager>::_instance = nullptr;

void JobManager::add_job (Job *job)
{
  job_mutex.lock ();
  jobs.push (job);
  job_mutex.unlock ();
}

void JobManager::add_job (job_function function, void *data)
{
  add_job (new Job{function, data});
}

JobManager::JobManager () : Singleton<JobManager> (), job_executor (new JobExecutor ())
{
  for (auto &thread : job_executor->worker_thread)
	thread.Start (SMALLEST_STACK_SIZE, loop_jobs, this);
}

void JobManager::loop_jobs (void *data)
{
  auto *self = (JobManager *)data;
  while (!self->job_executor->done)
	{
	  Job *job = nullptr;
	  self->job_mutex.lock ();
	  if (!self->jobs.empty ())
		{
		  job = self->jobs.front ();
		  self->jobs.pop ();
		}
	  self->job_mutex.unlock ();

	  if (job)
		{
		  job->function (job->data);
		  delete job;
		}
	}
}

JobManager::~JobManager ()
{
  job_executor->done = true;
  for (auto &thread : job_executor->worker_thread)
	thread.Join ();
}
