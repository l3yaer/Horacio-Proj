#ifndef _JOBMANAGER_H_
#define _JOBMANAGER_H_

#include "Singleton.h"

typedef void (*JobFunction)(void *);
typedef void *JobData;
class JobExecutor;

class JobManager : public Singleton<JobManager> {
public:
	enum Queue { DEFAULT, LOW, HIGH, MAIN };

private:
	JobExecutor *executor;

public:
	JobManager();

	~JobManager();

	void add_job(JobFunction function, JobData data, Queue queue = DEFAULT);

	void process_main_jobs();
};

#endif //_JOBMANAGER_H_
