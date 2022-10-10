#ifndef CJOB_H
#define CJOB_H

#include<string>
#include<iostream>


class CThread;
class CJob{
private:
    int m_JobNo; //任务ID 用来调试是否绑定特定线程
    std::string  m_JobName; //任务名字，用来调试是否绑定特定线程
    CThread* m_WorkThread;  //这个线程关联这个任务
public:
    CJob();
    virtual ~CJob();
    CThread* getWorkThread(); //获取工作的线程
    void setWorkThread(CThread* workThread); //设置工作线程
    virtual void execute(void* ptr) = 0; //执行函数
    int getJobNo();
    void setJobNo(int jobNo);
    std::string getJobName();
    void setJobName(std::string jobName);
};


#endif