#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO "/tmp/pipe"
#define BUFF_SIZE 100


int main() {
    int pipe_fd;
    char buff[BUFF_SIZE] = {'d'};
    mkfifo(FIFO, S_IFIFO|0640);//0640 to prawa dostepu garnij sobie
    pipe_fd = open(FIFO,O_WRONLY);
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