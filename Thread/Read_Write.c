#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

static int number = 0;

static void* thread_read(){
    usleep(rand()%800);

    pthread_rwlock_rdlock(&rwlock);
    printf("Thread ID: %lu doc duoc gia tri: %d\n", (unsigned long)pthread_self(), number);
    pthread_rwlock_unlock(&rwlock);


    return NULL;
}

static void* thread_write(){
    usleep(rand()%1000);

    pthread_rwlock_wrlock(&rwlock);
    number++;
    printf("Thread ID: %lu tang gia tri tu %d len thanh %d\n", (unsigned long)pthread_self(),number-1, number);
    pthread_rwlock_unlock(&rwlock);
    
    return NULL;
}

int main(){

    pthread_t r[5];
    pthread_t w[2];

    pthread_rwlock_init(&rwlock, NULL);

    for(int i=0;i<5;i++){
        pthread_create(&r[i], NULL, thread_read, NULL);
    }
    for(int i=0;i<2;i++){
        pthread_create(&w[i], NULL, thread_write, NULL);
    }

    for(int i=0;i<5;i++){
        pthread_join(r[i], NULL);
    }
    for(int i=0;i<2;i++){
        pthread_join(w[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}