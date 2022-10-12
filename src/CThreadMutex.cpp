#include "CThreadMutex.h"

CThreadMutex::CThreadMutex(){
    #if(_WIN32_WINNT >= 0x0403)
        ::InitializeCriticalSectionAndSpinCount(&m_CritSec,4000);
    #else
        ::InitializeCriticalSection(m_CritSec);
    #endif
}

CThreadMutex::~CThreadMutex(){
    ::DeleteCriticalSection(&m_CritSec);
}

bool CThreadMutex::lock(){
    ::EnterCriticalSection(&m_CritSec);
    return true;
}

bool CThreadMutex::unLock(){
    ::LeaveCriticalSection(&m_CritSec);
    return true;
}

bool CThreadMutex::tryLock(){
    bool bRet = TryEnterCriticalSection(&m_CritSec);
    return bRet;
}