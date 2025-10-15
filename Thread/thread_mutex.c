#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_NUMBER 1000000

static int number = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void *thread_counter(void* thread_number){

    int* thread_num = (int*)thread_number;
    while(1){

        pthread_mutex_lock(&lock);

        if (number > MAX_NUMBER){
            pthread_mutex_unlock(&lock);
            break;
        }

        number++;
        pthread_mutex_unlock(&lock);
        usleep(5000);
    }

    return NULL;
}

int main(){

    pthread_t number1, number2, number3;
    int t1 = 1, t2 = 2, t3 = 3;


    pthread_create(&number1, NULL, thread_counter, &t1);
    pthread_create(&number2, NULL, thread_counter, &t2);
    pthread_create(&number3, NULL, thread_counter, &t3);

    pthread_join(number1, NULL);
    pthread_join(number2, NULL);
    pthread_join(number3, NULL);

    printf("Giá trị cuối cùng của biến đếm number: %d\n", number);
    pthread_mutex_destroy(&lock);

    return 0;
}