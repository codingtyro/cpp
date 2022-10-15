#include "MyJob.h"

MyJob::MyJob(){

}

MyJob::MyJob(int i){
    setJobNo(i);
}

void MyJob::execute(void* jobData){
    printf("The Job comes from CXJOB\n");
    ::Sleep(2);
}