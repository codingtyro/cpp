#include "CJob.h"


void CJob::setJobName(std::string jobName){
    if(m_JobName != ""){
        m_JobName.clear();
        m_JobName = "";
    }
    if(jobName == ""){
        m_JobName = jobName;
    }
}

CJob::CJob() :m_JobName(""),m_WorkThread(nullptr),m_JobNo(0){

}

CThread* CJob::getWorkThread(){
    return m_WorkThread;
}

void CJob::setWorkThread(CThread* workThread){
    m_WorkThread = workThread;
}

CJob::~CJob(){
   m_WorkThread = nullptr;
}