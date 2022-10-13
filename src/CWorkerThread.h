#ifndef CWORKERTHREAD_H
#define CWORKERTHREAD_H

#include "CThread.h"
#include "CThreadCondition.h"
#include "CThreadMutex.h"
#include "CThreadPool.h"
#include "CJob.h"
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<Windows.h>
#include<functional>
#include<process.h>


//真正的线程工程，执行操作的线程
class CWorkerThread : public CThread{
public:
    CWorkerThread();
    virtual ~CWorkerThread();
    //有新任务时触发条件变量，每个线程一个条件变量，可以指定线程去执行任务
    CThreadCondition m_jobAddCond; 
    CThreadMutex m_workMutex;
    void run();
    void addNewJob(CJob* job,void* jobData);
    CJob* getJob();
    void setThreadPool(CThreadPool* threadPool);
    CThreadPool* getThreadPool();
    void terminate();
private:
    CThreadPool* m_ThreadPool;//线程池
    CJob* m_job;
    void* m_JobData;
    CThreadMutex* m_varMutex;
};


#endif