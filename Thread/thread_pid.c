#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

static void* thread_number1(){
    pthread_t tid = pthread_self();
    printf("Thread number1 với ID: %lu\n", (unsigned long)tid);
    return NULL;
}

static void* thread_number2(){
    pthread_t tid = pthread_self();
    printf("Thread number2 với ID: %lu\n", (unsigned long)tid);
    return NULL;
}

int main(){

    pthread_t number1;
    pthread_t number2;


    pthread_create(&number1, NULL, thread_number1, NULL);
    pthread_create(&number2, NULL, thread_number2, NULL);

    pthread_join(number1, NULL);
    pthread_join(number2, NULL);

    return 0;
}