#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(){

	pid_t pid = fork();

	if(pid<0){
		perror("wait");
		return 1;
	}

	if(pid==0){
		printf("[CHILD] PID:%d, [PARENT] PID:%d\n", getpid(), getppid());
		exit(0);
	}else{
		printf("[CHILD] PID:%d, [PARENT] PPID:%d\n", pid, getpid());

		sleep(10);
	}

	return 0;
}
