CC=gcc

all: init_process.c env_process.c orphan_process,c zombie_process.c
	$(CC) -o init_process init_process.c
	$(CC) -o env_process env_process.c 
	$(CC) -o orphan_process orphan_process.c
	$(CC) -o zombie_process zombie_process.c

init: init_process.c
	$(CC) -o $@ $^

env: env_process.c
	$(CC) -o $@ $^

orphan: orphan_process.c
	$(CC) -o $@ $^

zombie: zombie_process.c
	$(CC) -o $@ $^


clean: 
	rm -rf init env orphan zombie 

