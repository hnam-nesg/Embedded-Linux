#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void handle_alarm(int sig) {
    counter++;
    printf("Timer: %d seconds\n", counter);

    if (counter >= 10) {
        printf("Timer finished. Exiting...\n");
        _exit(0);
    }

    alarm(1);
}

int main() {
    signal(SIGALRM, handle_alarm);

    printf("Starting timer...\n");

    alarm(1);

    while (1) {
        pause(); 
    }

    return 0;
}
