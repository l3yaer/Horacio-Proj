#include "JobManager.h"
#include <MTScheduler.h>
#include <stack>

template<> JobManager *Singleton<JobManager>::_instance = nullptr;

 #define CREATE_JOB(NAME, PRIORITY) \
    struct NAME \
    { \
    MT_DECLARE_TASK(NAME, MT::StackRequirements::STANDARD, PRIORITY, MT::Color::Blue); \
    JobFunction function; \
    JobData data; \
    explicit NAME (JobFunction function, JobData data) : function (function), data (data) {} \
    void Do (MT::FiberContext &) \
    { \
            if (function) \
	        { \
                    function (data); \
					} \
    } \
    };

CREATE_JOB(Job, MT::TaskPriority::NORMAL)
CREATE_JOB(InputJob, MT::TaskPriority::LOW)

class JobExecutor
{
 private:
  MT::TaskScheduler task_scheduler;
	MT::TaskPool<Job, 1024> job_pool;
	MT::TaskPool<InputJob, 8> input_job_pool;

 public:
  void execute (JobFunction function, JobData data, JobManager::Queue queue);
  JobExecutor () = default;
  ~JobExecutor ()
  {
	task_scheduler.WaitAll (10000);
  }
};

void JobExecutor::execute (JobFunction function, JobData data, JobManager::Queue queue)
{
	MT::TaskHandle handler;

	switch (queue)
		{
			case JobManager::DEFAULT: handler = job_pool.Alloc (Job (function, data)); break;
			case JobManager::INPUT: handler = input_job_pool.Alloc (InputJob (function, data)); break;
		}

  task_scheduler.RunAsync (MT::TaskGroup::Default (), &handler, 1);
}

JobManager::JobManager () : Singleton<JobManager> (), executor (new JobExecutor ())
{}

JobManager::~JobManager ()
{
  delete executor;
}

void JobManager::add_job (JobFunction function, JobData data, JobManager::Queue queue)
{
  executor->execute (function, data, queue);
}
