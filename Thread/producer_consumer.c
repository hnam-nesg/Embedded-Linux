#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

static int data;
static bool data_ready;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER  ;

static void* Producer(void* arg){
    //pthread_t tid = pthread_self();
    
    for(int i=0;i<10;i++){
        pthread_mutex_lock(&lock);
        int number = rand() % 100;

        while(data_ready){
            pthread_cond_wait(&cond, &lock);
        }
        data = number;
        data_ready = true;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

static void* Consumer(void* arg){

    for(int i=0;i<10;i++){

        pthread_mutex_lock(&lock);
        
        while(!data_ready){
            pthread_cond_wait(&cond, &lock);
        }

        data_ready = false;
        printf("Consumer nhan duoc data: %d\n", data);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t consumer, producer;

    pthread_create(&producer, NULL, Producer, NULL);
    pthread_create(&consumer, NULL, Consumer, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}