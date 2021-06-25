#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define FIFO "/tmp/pipe"
#define BUFF_SIZE 100


int main() {
    int pipe_fd;
    pipe_fd = open(FIFO,O_WRONLY);
    char buff[BUFF_SIZE] = {'d'};
    printf("Client is running\n");
    printf("Type any msg and q to quit app\n");
    while(buff[0] !=  'q' ){
        scanf ("%s",buff);
        if(buff[0] != 'q'){
            write(pipe_fd,buff,sizeof(buff));
            printf("Type any msg and q to quit app\n");
        }
    }
    close(pipe_fd);
}