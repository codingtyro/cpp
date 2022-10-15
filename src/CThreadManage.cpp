#include "CThreadManage.h"

CThreadManage::CThreadManage(){
    m_numOfThread = 10;
    m_pool = new CThreadPool(m_numOfThread);
}

CThreadManage::CThreadManage(int num){
    m_numOfThread = num;
    m_pool = new CThreadPool(m_numOfThread);
}

CThreadManage::~CThreadManage(){
    if(NULL != m_pool){
        delete m_pool;
        m_pool = NULL;
    }
}

void CThreadManage::run(CJob* job,void* jobData){
    m_pool->run(job,jobData);
}

void CThreadManage::terminateAll(){
    m_pool->TerminateAll();
}