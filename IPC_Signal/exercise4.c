#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <errno.h>

volatile sig_atomic_t sigint_flag = 0;
volatile sig_atomic_t sigterm_flag = 0;

void signal_handler(int sig) {
    if (sig == SIGINT) {
        sigint_flag = 1;              
    } else if (sig == SIGTERM) {
        sigterm_flag = 1;             
    }
}

int main() {
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal SIGINT");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("signal SIGTERM");
        exit(EXIT_FAILURE);
    }

    printf("Nhap chuoi, nhan Enter de in lai.\n");
    printf("Ctrl+C -> SIGINT, kill -TERM <pid> -> SIGTERM.\n");


    while (1) {

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
    
        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL);


        if (ret == -1) {
            if (errno == EINTR) {
                if (sigint_flag) {
                    printf("SIGINT received.\n");
                    sigint_flag = 0;
                }

                if (sigterm_flag) {
                    printf("SIGTERM received. Exiting...\n");
                    break;           
                }

                continue;            
            } else {
                perror("select");
                break;
            }
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char buf[512];

            if (fgets(buf, sizeof(buf), stdin) == NULL) {
                printf("EOF hoac loi input, thoat.\n");
                break;
            }

            printf("Ban vua nhap: %s", buf);
        }

        if (sigint_flag) {
            printf("SIGINT received.\n");
            sigint_flag = 0;
        }

        if (sigterm_flag) {
            printf("SIGTERM received. Exiting...\n");
            break;
        }
    }

    return 0;
}
