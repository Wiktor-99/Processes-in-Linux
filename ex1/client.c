#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


#define FIFO "/tmp/pipe"
#define BUFF_SIZE 100


int main() {
    int pipe_fd, licz;
    char bufor[BUFF_SIZE];
    pipe_fd = open(FIFO, O_RDONLY);
    printf("Server is running\n");
    while (read(pipe_fd, bufor,BUFF_SIZE)> 0) {
        printf("%s\n",bufor);
    }
    close(pipe_fd);
}