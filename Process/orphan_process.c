#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

	pid_t pid = fork();

	if(pid<0){
		perror("wait");
		return 1;
	}

	if(pid==0){
		for(int i=0;i<5;i++){
			printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
			sleep(1);
		}
		exit(0);
	}

	else{
		printf("Child PID: %d, Parent PID: %d\n", pid, getpid());
	}

	return 0;
}