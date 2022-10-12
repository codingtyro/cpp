#ifndef CTHREADCONDITION_H
#define CTHREADCONDITION_H

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<Windows.h>
#include<functional>
#include<process.h>

//条件变量
class CThreadCondition{
private:
    HANDLE m_hEvent;//句柄
public:
    CThreadCondition();
    ~CThreadCondition();
    void wait();
    void signal();
};

#endif