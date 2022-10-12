#include "CThreadCondition.h"

CThreadCondition::CThreadCondition(){
    m_hEvent = ::CreateEvent(NULL,true,false,NULL);
}

CThreadCondition::~CThreadCondition(){
    if(NULL != m_hEvent){
        ::CloseHandle(m_hEvent);
    }
}

void CThreadCondition::wait(){
    WaitForSingleObject(m_hEvent,INFINITE);
    ResetEvent(m_hEvent);
}

void CThreadCondition::signal(){
    SetEvent(m_hEvent);
}