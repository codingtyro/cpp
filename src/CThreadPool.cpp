#include "CThreadPool.h"

void CThreadPool::setMaxNum(int maxNum){
    m_Maxnum = maxNum;
}

int CThreadPool::getMaxNum(){
    return m_Maxnum;
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

}

CThreadPool::CThreadPool(int initNum):m_InitThreadNum(initNum){

}

