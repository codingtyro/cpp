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

