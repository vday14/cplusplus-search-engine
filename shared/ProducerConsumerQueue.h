//
// Created by Ben Bergkamp on 1/25/18.
//

#ifndef EECS398_SEARCH_PRODUCERCONSUMERQUEUE_H
#define EECS398_SEARCH_PRODUCERCONSUMERQUEUE_H

#include <queue>
#include <pthread.h>

//for now use STL queue, create better one later


template <class T> class ProducerConsumerQueue {
private:
    std::queue<T> queue;
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t consumer_cv = PTHREAD_COND_INITIALIZER;

public:

    ProducerConsumerQueue() {}
    void Push(T obj);
    T Pop();
    size_t Size();

    //Right now these pass objects by value but
    // probably should pass pointers in future

};

//Necessary because this class is templated
#include"ProducerConsumerQueue.cpp"

#endif //EECS398_SEARCH_PRODUCERCONSUMERQUEUE_H
