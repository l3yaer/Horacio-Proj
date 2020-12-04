#include "JobManager.h"
#include <MTScheduler.h>
#include <stack>
#include <utility>

#define CREATE_JOB(NAME, PRIORITY)                                                                                     \
	struct NAME {                                                                                                      \
		MT_DECLARE_TASK(NAME, MT::StackRequirements::STANDARD, PRIORITY, MT::Color::Blue);                             \
		JobFunction function;                                                                                          \
		JobData data;                                                                                                  \
		explicit NAME(JobFunction function, JobData data) : function(function), data(data)                             \
		{                                                                                                              \
		}                                                                                                              \
		void Do(MT::FiberContext &)                                                                                    \
		{                                                                                                              \
			if (function) {                                                                                            \
				function(data);                                                                                        \
			}                                                                                                          \
		}                                                                                                              \
	};

CREATE_JOB(LowPJob, MT::TaskPriority::LOW)
CREATE_JOB(Job, MT::TaskPriority::NORMAL)
CREATE_JOB(HighPJob, MT::TaskPriority::HIGH)

IMPLEMENT_SINGLETON(JobManager)

static const uint32 TASK_COUNT = 512;

class JobExecutor {
private:
	MT::TaskScheduler task_scheduler;
	MT::TaskPool<Job, TASK_COUNT> job_pool;
	MT::TaskPool<LowPJob, TASK_COUNT> low_job_pool;
	MT::TaskPool<HighPJob, TASK_COUNT> high_job_pool;
public:
	std::vector<std::pair<JobFunction, JobData>> main_jobs;

	void execute(JobFunction function, JobData data, JobManager::Queue queue);
	JobExecutor() = default;
	~JobExecutor()
	{
		task_scheduler.WaitAll(10000);
	}
};

void JobExecutor::execute(JobFunction function, JobData data, JobManager::Queue queue)
{
	MT::TaskHandle handler;

	switch (queue) {
	case JobManager::DEFAULT:
		handler = job_pool.Alloc(Job(function, data));
		break;
	case JobManager::LOW:
		handler = low_job_pool.Alloc(LowPJob(function, data));
		break;
	case JobManager::HIGH:
		handler = high_job_pool.Alloc(HighPJob(function, data));
		break;
	case JobManager::MAIN:
		main_jobs.emplace_back(std::pair<JobFunction, JobData>(function, data));
		return;
	}

	task_scheduler.RunAsync(MT::TaskGroup::Default(), &handler, 1);
}

JobManager::JobManager() : Singleton<JobManager>(), executor(new JobExecutor())
{
}

JobManager::~JobManager()
{
	delete executor;
}

void JobManager::add_job(JobFunction function, JobData data, JobManager::Queue queue)
{
	executor->execute(function, data, queue);
}

void JobManager::process_main_jobs()
{
	for(auto &job : executor->main_jobs)
		job.first(job.second);
	executor->main_jobs.clear();
}
