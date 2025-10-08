#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main(){

	pid_t pid = fork();

	if(pid<0){
		perror("wait");
		return 1;
	}

	if(pid==0){
		printf("[Child] PID:%d, [Parent] PID:%d\n", getpid(), getppid());

		exit(100);
	}
	else{
		printf("[Child] PID:%d, [Parent] PID:%d\n", pid, getpid());
		

		int status = 0;
		pid_t w = wait(&status);

		if (w==-1){
			perror("wait");
			return 1;
		}
		
		if(WIFEXITED(status)){
			int code = WEXITSTATUS(status);
			printf("[Parent] Child %d da thoat chuong trinh voi ma trang thai %d\n", w, code);
		}else{
			printf("[Parent] Child %d khong thoat chuong trinh\n", w);
		}
	}

	return 0;
}
