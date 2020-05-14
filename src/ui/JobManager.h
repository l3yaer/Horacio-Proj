#ifndef JOBMANAGER_H_
#define JOBMANAGER_H_

#include <vector>
#include <mutex>
#include <queue>
#include "Singleton.h"

struct Job
{
    void (*function )(void *);   // Job instructions
    void *data;                 // Job parameters
};

typedef void (*job_function)(void *);

class JobExecutor;

class JobManager : public Singleton<JobManager>
{
private:
    JobExecutor *job_executor;

    static void loop_jobs(void *);

    std::mutex job_mutex;

    std::queue<Job*> jobs;

public:
    virtual ~JobManager();

public:

    JobManager();

    void add_job(Job *job);

    void add_job(job_function function, void* data);
};


#endif //JOBMANAGER_H_
