#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<Windows.h>
#include<functional>
#include<process.h>
#include "CThreadManage.h"
#include "MyJob.h"

int main(){
    auto manage = new CThreadManage(50);
    for(int i = 0;i < 1000;i++){
        auto job = new MyJob(i);
        manage->run(job,NULL);
    }
    ::Sleep(2);

    auto job = new MyJob();
    manage->run(job,NULL);
    manage->terminateAll();
    return 0;
}
