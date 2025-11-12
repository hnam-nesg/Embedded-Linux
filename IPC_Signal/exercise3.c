#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int count =0;

void signal_handle(int sig){
    if(sig==SIGUSR1){
    printf("Received signal from parent!\n");
    count++;
    if(count == 5) exit(0);
    }
}

int main(){

    pid_t pid = fork();
    
    if(pid < 0){
        perror("Wait!");
        return 1;
    }
    else if(pid == 0){
        printf("Child [PID]: %d, Parent [PID]: %d\n", getpid(), getppid());
        signal(SIGUSR1, signal_handle);
        while(1){pause();}
    }
    else{
        
        sleep(1);
        
        for(int i=0; i<5;i++){
            kill(pid, SIGUSR1);
            sleep(2);
        }

        int status = 0;
        pid_t w = wait(&status);
    }

    return 0;
}