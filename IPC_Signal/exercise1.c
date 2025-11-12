#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int count = 0; 

void handle_sigint(int sig) {
    count++;
    printf("SIGINT received (%d)\n", count);
}


int main() {


    void(*oldHandle)(int);

    oldHandle = signal(SIGINT, handle_sigint);


    printf("Program is running. Press Ctrl+C to send SIGINT.\n");

    while (1) {
        if(count >= 2){
            signal(SIGINT, oldHandle);
           // signal(SIGINT, SIG_DFL);
        } 
    }

    return 0;
}
