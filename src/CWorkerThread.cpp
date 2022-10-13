#include "CWorkerThread.h"

void CWorkerThread::terminate(){
    m_workMutex.lock();
    setExitFlag(true);
    m_JobData = NULL;
    m_job = NULL;
    printf("thread [%d] ready to exit\n",getThreadId());
    m_jobAddCond.signal();
    m_workMutex.unLock();
    WaitForSingleObject(getThreadHandle(),INFINITE);
    CloseHandle(getThreadHandle());
}

CWorkerThread::CWorkerThread():m_JobData(NULL),m_job(NULL),m_ThreadPool(NULL){

}

CWorkerThread::~CWorkerThread(){
    if(NULL != m_job){
        delete m_job;
        m_job = NULL;
    }
    if(NULL != m_ThreadPool){
        delete m_ThreadPool;
        m_ThreadPool = NULL;
    }
}

void CWorkerThread::run(){
    printf("Enter CWorkerThread::run\n");
    setThreadState(THREAD_RUNNING);
    while(true){
        while(NULL != m_job && !needExit()){
            printf("thread [%d] wait for job \n",getThreadId());
            m_jobAddCond.wait();
        }
        if(NULL != m_job){
            printf("thread [%d] exitFlag [%d]\n",getThreadId(),needExit());
            if(needExit()){
                //不再等待任务，退出线程
                break;
            }else{
                //任务为NULL 但不是线程退出，跳过这个任务
                printf("m_job [%p] exitFlag [%d]\n",m_job,needExit());
                continue;
            }
        }
        m_workMutex.lock();
        printf("thread [%d] accept the job [%d]\n",getThreadId(),m_job->getJobNo());
        //真正执行任务的地方
        m_job->execute(m_JobData);
        m_job->setWorkThread(NULL);
        m_job = NULL;
        m_JobData = NULL;
        m_ThreadPool->moveToIdleList(this);
        setThreadState(THREAD_IDLE);
        if(m_ThreadPool->m_vecAllThreads.size() > m_ThreadPool->getAvailHighNum()){
            m_ThreadPool->deleteIdleThread(m_ThreadPool->m_vecIdleThreads.size() - m_ThreadPool->getInitNum());

        }
        m_workMutex.unLock();
    }
    printf("thread [%d] exit\n",getThreadId());
}

void CWorkerThread::addNewJob(CJob* job,void* jobData){
    assert(NULL != job);
    m_varMutex->lock();
    m_job = job;
    m_JobData = jobData;
    job->setWorkThread(this);
    m_varMutex->unLock();
    printf("job [%d] add to the pool\n",m_job->getJobNo());
    m_jobAddCond.signal();

}

void CWorkerThread::setThreadPool(CThreadPool* threadPool){
    m_varMutex->lock();
    m_ThreadPool = threadPool;
    m_varMutex->unLock();
}

