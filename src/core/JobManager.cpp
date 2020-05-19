#include "JobManager.h"
#include <MTScheduler.h>
#include <stack>

template<> JobManager *Singleton<JobManager>::_instance = nullptr;

struct Job
{
  MT_DECLARE_TASK(Job, MT::StackRequirements::STANDARD, MT::TaskPriority::NORMAL, MT::Color::Blue);

  JobFunction function;
  JobData data;

  explicit Job (JobFunction function, JobData data) : function (function), data (data)
  {}

  void Do (MT::FiberContext &)
  {
	if (function)
	  {
		function (data);
	  }
  }
};

class JobExecutor
{
 private:
  MT::TaskScheduler task_scheduler;
  MT::TaskPool<Job, 1024> task_pool;

 public:
  void execute (JobFunction function, JobData data);
  JobExecutor () = default;
  ~JobExecutor ()
  {
	task_scheduler.WaitAll (10000);
  }
};

void JobExecutor::execute (JobFunction function, JobData data)
{
  auto handler = task_pool.Alloc (Job (function, data));
  task_scheduler.RunAsync (MT::TaskGroup::Default (), &handler, 1);
}

JobManager::JobManager () : Singleton<JobManager> (), executor (new JobExecutor ())
{}

JobManager::~JobManager ()
{
  delete executor;
}

void JobManager::add_job (JobFunction function, JobData data)
{
  executor->execute (function, data);
}
