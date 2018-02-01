//
// Created by Ben Bergkamp on 1/31/18.
//

#ifndef EECS398_SEARCH_THREADCLASS_H
#define EECS398_SEARCH_THREADCLASS_H
#include <pthread.h>

class ThreadClass
{
public:
    ThreadClass() { };
    virtual ~ThreadClass() { };

    //Returns true if thread was created successfully
    bool StartThread()
    {
        return (pthread_create(&thread, NULL, StaticFuncToRun, this) == 0);
    }

    //Blocks until thread finishes
    void WaitForFinish()
    {
        pthread_join(thread, NULL);
    }

protected:
    //IMPLEMENT THIS METHOD IN YOUR SUB CLASS WITH CODE YOU WANT YOUR THREAD TO RUN
    virtual void FuncToRun() = 0;

private:
    static void * StaticFuncToRun(void * This) { ((ThreadClass *)This)->FuncToRun(); return nullptr;}
    pthread_t thread;
};



#endif //EECS398_SEARCH_THREADCLASS_H
