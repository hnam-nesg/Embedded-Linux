#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	
	char *command_default = "ls -la";

	if(argc == 2){
		command_default = argv[1];
	}

	if(setenv("MY_COMMAND", command_default, 1) != 0){
		perror("setenv");
		return 1;
	}
	
	pid_t pid = fork();
	if(pid<0){
		perror("wait");
		return 1;
	}

	if (pid==0){

		const char*cmd = getenv("MY_COMMAND");
		if(!cmd){
			fprintf(stderr, "[CHILD] PID:%d, MY_COMMAND khong duoc tai\n", getpid());
			exit(1000);
		}

		execlp("sh", "sh", "-c", cmd, (char*)NULL);

		printf("[CHILD] PID:%d, [PARENT] PID:%d\n", getpid(), getppid());
		exit(1000);
	}else{
		printf("[CHILD] PID:%d, [PARENT] PID:%d\n", pid, getpid());

		int status = 0;
		pid_t w = wait(&status);
		if(w==-1){
			perror("wait");
			return 1;
		}

		if(WIFEXITED(status)){
			int code = WEXITSTATUS(status);
			printf("[PARENT] CHILD %d da thoat voi ma trang thai %d\n", w, code);
		}else{
			printf("[PARENT] CHILD %d khong the thoat binh thuong\n", w);
		}
	}

	return 0;
}
