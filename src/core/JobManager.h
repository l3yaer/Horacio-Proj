#ifndef _JOBMANAGER_H_
#define _JOBMANAGER_H_

#include <mutex>
#include "Singleton.h"

typedef void (*JobFunction) (void *);
typedef void *JobData;
class JobExecutor;

class JobManager : public Singleton<JobManager>
{
 private:
  JobExecutor *executor;
 public:
  JobManager ();

  ~JobManager ();

  void add_job (JobFunction function, JobData data);
};

#endif //_JOBMANAGER_H_
