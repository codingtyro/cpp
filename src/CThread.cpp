#include "CThread.h"

CThread::CThread(){
    m_IsExit = false;
}

CThread::~CThread(){

}

int CThread::getErrorCode(){
    return m_ErrorCode;
}

bool CThread::needExit(){
    return m_IsExit;
}

void CThread::setExitFlag(bool exit){
    m_IsExit = exit;
}

bool CThread::getExitFlag(){
    return m_IsExit;
}

bool CThread::terminate(){
    _endthreadex(0);
    return true;
}

HANDLE CThread::getThreadHandle(){
    return m_hthreadHandle;
}

void CThread::setThreadHandle(HANDLE handle){
    m_hthreadHandle = handle;
}

void CThread::setErrorCode(int errorCode){
    m_ErrorCode = errorCode;
}

int CThread::getErrorCode(){
    return m_ErrorCode;
}


void CThread::setThreadState(ThreadState state){
    m_ThreadState = state;
}

ThreadState CThread::getThreadState(){
    return m_ThreadState;
}

bool CThread::start(){
    unsigned threadId;
    HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,ThreadFunction,this,0,&threadId);
    this->m_ThreadId = threadId;
    this->setThreadHandle(hThread);
    return true;
}

unsigned __stdcall CThread::ThreadFunction(void* pArg){
    CThread* pThread = static_cast<CThread*>(pArg);
    pThread->run();
    return true;
}


int CThread::getThreadId(){
    return m_ThreadId;
}

void CThread::setThreadName(std::string threadName){
    m_ThreadName = threadName;
}

std::string CThread::getThreadName(){
    return m_ThreadName;
}

