#ifndef  CTHREADPOOL_H
#define CTHREADPOOL_H

#include "CWorkerThread.h"
#include "CThreadMutex.h"
#include "CThreadCondition.h"
#include "CJob.h"
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<Windows.h>
#include<functional>
#include<process.h>

//线程池类，主要负责调度线程，创建线程，删除线程
class CThreadPool{
    friend class CWorkerThread;
private:
    unsigned int m_MaxNum; //当前线程池中允许并发存在的线程的最大数量
    unsigned int m_AvailLow; //当前线程池中允许存在的空闲线程的最小数目
    /**
     * 如果空闲数目低于该值，表明负载可能过重，此时有必要增加空闲线程池的数目
     * 实现中我们总是将线程调整为m_InitNum个
    */
   unsigned int m_AvailHigh;//当前线程池中允许的空闲的线程的最大数目
   //如果空闲数目高于该数值的时候，表明负载可能过轻，此时应该删除多余的线程
   //删除后，调整数目为m_InitNum个
   unsigned int m_CurIdleThreadNum;//当前线程池中实际存在的线程个数
   /**
    * 如果线程的个数始终保持在m_AvailLow 与 m_AvailHigh之间
    * 则线程既不需要创建，也不需要删除，保持平衡
   */
  unsigned int m_InitThreadNum;//初始创建时线程池中的线程个数
protected:
    CWorkerThread* getIdleThread();//获取空闲线程
    void appendToIdleList(CWorkerThread* jobThread);//线程加入空闲队列
    void moveToBusyList(CWorkerThread* idleThread);//线程加入忙碌队列
    void moveToIdleList(CWorkerThread* busyThread);//线程移入空闲队列
    void deleteIdleThread(int num); //删除空闲线程
    void createIdleThread(int num); //创建空闲线程
public:
    CThreadMutex m_busyMutex;//when visit busy list,use m_busyMutex to lock or unlock
    CThreadMutex m_IdleMutex; //when visit idle list,use m_idleMutex to lock or unlock
    CThreadMutex m_threadNumMutex;//变量锁，目前用在m_CurIdleThreadNum修改上面

    CThreadCondition m_busyCond; //m_busyCond is used sync busy thread list
    CThreadCondition m_idleCond; //m_idleCond is used sync idle thread list
    CThreadCondition m_maxNUmCond; //m_maxNumCond is used to sync m_CurIdleThreadNum;

    std::vector<CWorkerThread*> m_vecAllThreads;//创建出来的所有线程列表
    std::vector<CWorkerThread*> m_vecBusyThreads;//忙碌线程队列，随着负载多少会改变
    std::vector<CWorkerThread*> m_vecIdleThreads;//空闲线程队列，随着负载的减少会改变

public:
    void setMaxNum(int maxNum);//设置线程池运行的最大线程数
    int getMaxNum();
    void setAvailLowNum(int minNum);
    int getAvailLowNum();
    void setAvailHighNum(int maxNum);
    int getAvailHighNum();
    int getCurIdleThreadsNum();
    int getAllThreadsNum();
    int getBusyThreadsNum();
    void setInitNum(int initNum);
    int getInitNum();
    CThreadPool();
    ~CThreadPool();
    CThreadPool(int initNum);
    void TerminateAll();
    void run(CJob* job,void* jobData);
};

#endif