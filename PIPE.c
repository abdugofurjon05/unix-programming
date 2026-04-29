#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXSIZE 1024

int main(int argc, char* argv[]) {

    int fd[2];
    char buf[MAXSIZE];
    const char* str = "hello from the child";

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    int fr = fork();
    if (fr == -1) {
        perror("fork");
        return 1;
    }

    if (fr == 0) {
        close(fd[0]);
        write(fd[1], str, strlen(str) + 1);
        close(fd[1]);
    } else {
        close(fd[1]);
        read(fd[0], buf, MAXSIZE);
        close(fd[0]);
        wait(NULL);
        printf("Text: %s\n", buf);
    }

    return 0;
}