#include "CThreadPool.h"

void CThreadPool::setMaxNum(int maxNum){
    m_MaxNum = maxNum;
}

int CThreadPool::getMaxNum(){
    return m_MaxNum;
}

void CThreadPool::setAvailLowNum(int minNum){
    m_AvailLow = minNum;
}

int CThreadPool::getAvailLowNum(){
    return m_AvailLow;
}

void CThreadPool::setAvailHighNum(int maxNum){
    m_AvailHigh = maxNum;
}

int CThreadPool::getAvailHighNum(){
    return m_AvailHigh;
}

int CThreadPool::getCurIdleThreadsNum(){
    return m_CurIdleThreadNum;
}

int CThreadPool::getAllThreadsNum(){
    return m_vecAllThreads.size();
}

int CThreadPool::getBusyThreadsNum(){
    return m_vecBusyThreads.size();
}

int CThreadPool::getInitNum(){
    return m_InitThreadNum;
}

void CThreadPool::setInitNum(int initNum){
    m_InitThreadNum = initNum;
}

CThreadPool::CThreadPool(){
    m_MaxNum = 50;
    m_AvailHigh = 10;
    m_AvailLow = 5;
    m_InitThreadNum = 10;
    m_CurIdleThreadNum = 10;
    m_vecBusyThreads.clear();
    m_vecIdleThreads.clear();
    for(int i = 0;i < m_InitThreadNum;i++){
        CWorkerThread* newWorkThread = new CWorkerThread();
        newWorkThread->setThreadPool(this);
        appendToIdleList(newWorkThread);
        newWorkThread->start();
    }
}

CThreadPool::CThreadPool(int initNum){
    m_MaxNum = 30;
    m_AvailLow = (initNum - 10 > 0 ? (initNum - 10) : 3);
    m_InitThreadNum = m_CurIdleThreadNum = initNum;
    m_AvailHigh = initNum  + 10;
    m_vecAllThreads.clear();
    m_vecBusyThreads.clear();
    m_vecIdleThreads.clear();
    for(int i = 0;i < m_InitThreadNum;i++){
        CWorkerThread* newWorkThread = new CWorkerThread();
        newWorkThread->setThreadPool(this);
        appendToIdleList(newWorkThread);
        newWorkThread->start();
    }
    printf("CThreadPool::CThreadPool: create Thread [%d] success\n",m_InitThreadNum);
}

CThreadPool::~CThreadPool(){
    TerminateAll();
}

void CThreadPool::TerminateAll(){
    for(int i = 0;i < m_vecAllThreads.size();i++){
        CWorkerThread* workThread = m_vecAllThreads[i];
        workThread->terminate();
    }
}

CWorkerThread* CThreadPool::getIdleThread(){
    while(m_vecIdleThreads.size() == 0){
        printf("no idle thread,must wait\n");
        m_idleCond.wait();
    }
    m_IdleMutex.lock();
    if(m_vecIdleThreads.size() > 0){
        CWorkerThread* idleThread = static_cast<CWorkerThread*>(m_vecIdleThreads.front());
        printf("get idle thread %d\n",idleThread->getThreadId());
        m_IdleMutex.unLock();
        return idleThread;
    }
    m_IdleMutex.unLock();
    printf("%warnig : no idle threads return\n");
    return NULL;
}

void CThreadPool::appendToIdleList(CWorkerThread* jobThread){
    m_IdleMutex.lock();
    m_vecIdleThreads.push_back(jobThread);
    m_vecAllThreads.push_back(jobThread);
    m_IdleMutex.unLock();
}

void CThreadPool::moveToBusyList(CWorkerThread* idleThread){
    m_busyMutex.lock();
    m_vecBusyThreads.push_back(idleThread);
    m_CurIdleThreadNum--;
    m_busyMutex.unLock();

    m_IdleMutex.lock();
    auto pos = std::find(m_vecIdleThreads.begin(),m_vecIdleThreads.end(),idleThread);
    if(pos != m_vecIdleThreads.end()){
        m_vecIdleThreads.erase(pos);
    }
    m_IdleMutex.unLock();

}


void CThreadPool::moveToIdleList(CWorkerThread* busyThread){
    m_IdleMutex.lock();
    m_vecIdleThreads.push_back(busyThread);
    m_CurIdleThreadNum++;
    m_IdleMutex.unLock();

    m_busyMutex.lock();
    auto pos = std::find(m_vecBusyThreads.begin(),m_vecBusyThreads.end(),busyThread);
    if(pos != m_vecBusyThreads.end()){
        m_vecBusyThreads.erase(pos);
    }
    m_busyMutex.unLock();
    m_idleCond.signal();
    m_maxNUmCond.signal();
}


void CThreadPool::createIdleThread(int num){
    for(int i = 0;i < num;i++){
        CWorkerThread* workThread = new CWorkerThread();
        workThread->setThreadPool(this);
        appendToIdleList(workThread);
        m_threadNumMutex.lock();
        m_CurIdleThreadNum++;
        m_threadNumMutex.unLock();
        workThread->start();
    }
}

void CThreadPool::deleteIdleThread(int num){
    printf("Enter into CThreadPool::deleteIdleThread\n");
    m_IdleMutex.lock();
    printf("delete num is %d\n",num);
    for(int i = 0;i < num;i++){
        CWorkerThread* workThread;
        if(m_vecIdleThreads.size() > 0){
            workThread = static_cast<CWorkerThread*>(m_vecIdleThreads.front());
            printf("get Idle thread %d\n",workThread->getThreadId());
        }else{
            printf("no Idle thread,no need to delete thread\n");
            break;
        }
        auto pos = std::find(m_vecIdleThreads.begin(),m_vecIdleThreads.end(),workThread);
        if(pos != m_vecIdleThreads.end()){
            m_vecIdleThreads.erase(pos);
        }
        m_CurIdleThreadNum--;
        printf("The Idle thread available num %d\n",m_CurIdleThreadNum);
        printf("The IdleList num %d\n",m_vecIdleThreads.size());
    }
    m_IdleMutex.unLock();
}

void CThreadPool::run(CJob* job,void* jobData){
    assert(NULL != job);
    /**
     * printf要输出的内容太长了，需要写在多，则每一行都需要用双引号包含起来
    */
    if(m_MaxNum <= getBusyThreadsNum()){
        printf("busy threads beyond the max threads number in the pool" 
        "must wait for Idle threads\n");
        m_maxNUmCond.wait();
    }
    //负载过重，线程少，需要创建新的线程
    if(m_vecIdleThreads.size() < m_AvailLow){
        if(getAllThreadsNum() + m_InitThreadNum - m_vecIdleThreads.size() < m_MaxNum){
            //当前有m_vecIdleThreads.size()个空闲线程
            createIdleThread(m_InitThreadNum - m_vecIdleThreads.size());
        }else{
            createIdleThread(m_MaxNum - getAllThreadsNum());
        }
    }
    auto workThread = getIdleThread();
    if(NULL != workThread){
        workThread->m_workMutex.lock();
        moveToBusyList(workThread);
        workThread->setThreadPool(this);
        job->setWorkThread(workThread);
        printf("Job [%d] bind to thread [%d]\n",job->getJobNo(),workThread->getThreadId());
        workThread->addNewJob(job,jobData);
        workThread->m_workMutex.unLock();
    }else{
        printf("impossible to going here\n");
    }
}
