#ifndef CTHREADMANAGE_H
#define CTHREADMANAGE_H

#include "CJob.h"
#include "CThreadPool.h"
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<Windows.h>
#include<functional>
#include<process.h>

class CThreadManage{
public:
    CThreadManage();
    CThreadManage(int num);
    virtual ~CThreadManage();
    //运行任务
    void run(CJob* job,void* jobData);
    //停止所有的线程
    void terminateAll();
private:
    int m_numOfThread;//初始化允许创建的最大线程的个数
    CThreadPool* m_pool;//实际的线程池
    
};
#endif