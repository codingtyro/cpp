#ifndef CTHREADMUTEX_H
#define CTHREADMUTEX_H

#include "CLockObject.h"
#include<Windows.h>
#include<process.h>
#include<functional>
#include<stdio.h>
#include<stdlib.h>


//线程互斥锁
class CThreadMutex: public CLockObject{
private:
    CRITICAL_SECTION m_CritSec;//临界区
public:
    CThreadMutex();
    ~CThreadMutex();
    bool lock() override;//加锁，阻塞式
    bool unLock() override;//解锁
    bool tryLock(); //加锁，非阻塞式

};

#endif