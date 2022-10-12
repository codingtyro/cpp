#ifndef CLOCKOBJECT_H
#define CLOCKOBJECT_H

//锁的基类

class CLockObject{
public:
    virtual bool lock() = 0;
    virtual bool unLock() = 0;
};

#endif