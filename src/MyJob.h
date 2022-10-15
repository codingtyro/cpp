#ifndef MYJOB_H
#define MYJIOB_H

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<Windows.h>
#include<functional>
#include<process.h>
#include "CJob.h"

class MyJob:public CJob{
public:
    MyJob();
    MyJob(int i);
    ~MyJob();
    void execute(void* jobData);
};

#endif