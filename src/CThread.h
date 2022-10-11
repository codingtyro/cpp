#ifndef CTHREAD_H
#define CTHREAD_H

#include<string>
#include<Windows.h>
typedef enum Thread_State{
    THREAD_RUNNING = 0X0, //运行
    THREAD_IDLE = 0x1,     //空闲
    THREAD_EXIT = 0x2,      //退出
}ThreadState;


class CThread{
private:
    int m_ErrorCode;
    unsigned long m_ThreadId;
    std::string m_ThreadName;
    ThreadState m_ThreadState;
    HANDLE m_hthreadHandle;
    bool m_IsExit;
protected:
    static unsigned __stdcall ThreadFunction(void* pArg);
public:
    CThread();
    virtual ~CThread();
    virtual void run() = 0;

    void setThreadState(ThreadState state);

    ThreadState getThreadState();

    bool start();

    int getThreadId();

    void setErrorCode(int errorCode);

    int getErrorCode();

    void setThreadName(std::string threadName);

    std::string getThreadName();

    bool setPriority(int priority);

    int getPriority();

    bool terminate();

    HANDLE getThreadHandle();

    void setThreadHandle(HANDLE handle);

    void setExitFlag(bool exit);

    bool getExitFlag();

    bool needExit();

};
#endif