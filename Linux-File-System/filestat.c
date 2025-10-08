#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	struct stat filestat;
	
	if(argc != 2){
		printf("Usage: ./filestat <path_file>\n");
		return 1;
	}

	char *path = argv[1];

	if(lstat(path, &filestat) < 0){
		perror("lstat error");
		return 1;
	}

	printf("File path: %s\n", path);
	printf("File type: ");
	if(S_ISREG(filestat.st_mode)){printf("Regular File\n");}

	else if(S_ISDIR(filestat.st_mode)){printf("Directory\n");}

	else if(S_ISLNK(filestat.st_mode)){printf("Symbolic Link\n");}
	
	else{printf("Other\n");}

	printf("Size: %ld bytes\n", filestat.st_size);

	char time[100];
	struct tm *tm_info = localtime(&filestat.st_mtime);
	strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", tm_info);
	printf("Last Modified: %s\n", time);

	return 0;
}
