///
// Created by Ben Bergkamp on 1/25/18.
//

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include "ProducerConsumerQueue.h"


pthread_mutex_t cout_lock = PTHREAD_MUTEX_INITIALIZER;

void* Producer(void* p)
{
    ProducerConsumerQueue<int> * queue = (ProducerConsumerQueue<int>*)p;

    for(int i = 0; i < 10; i++)
    {
        if(queue->Size()){
            pthread_yield_np(); // let the consumer thread run
        }

        queue->Push(i);

        pthread_mutex_lock(&cout_lock);
        std::cout << "Pushed: " << i << "\n";
        pthread_mutex_unlock(&cout_lock);
    }

    return p;
}

void* Consumer(void* p)
{
    ProducerConsumerQueue<int> * queue = (ProducerConsumerQueue<int>*)p;

    for(int i = 0; i < 10; i++)
    {
        int r = queue->Pop();

        pthread_mutex_lock(&cout_lock);
        std::cout << "Popped: " << r << "\n";
        pthread_mutex_unlock(&cout_lock);
    }

    return p;
}



int main(int argc, const char * argv[])
{
    ProducerConsumerQueue<int>* queue = new(ProducerConsumerQueue<int>);

    pthread_t producer, consumer;

    pthread_mutex_lock(&cout_lock);
    std::cout << "Creating Consumer\n";
    pthread_mutex_unlock(&cout_lock);
    pthread_create(&consumer, NULL, Consumer, queue);

    pthread_mutex_lock(&cout_lock);
    std::cout << "Creating Producer\n";
    pthread_mutex_unlock(&cout_lock);
    pthread_create(&producer, NULL, Producer, queue);

    pthread_mutex_lock(&cout_lock);
    std::cout << "Waiting for Producer and Consumer\n";
    pthread_mutex_unlock(&cout_lock);
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    delete queue;

    return 0;
}