#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROCESS_COUNT 10
#define SIDE_LENGTH 1
#define H_SIDE_LENGTH 0.5 // SIDE_LENGTH 1/2 = 0.5
#define RADIUS 0.5        // bok to 2r = 1 -> r = 0.5

double monteCarlo(int numberOfPoints) {
    double square_points = 0;
    double circle_points = 0;
    for (int i = 0; i < numberOfPoints; ++i) {
        double x = drand48();
        double y = drand48();
        double x_2 = (x - H_SIDE_LENGTH) * (x - H_SIDE_LENGTH);
        double y_2 = (y - H_SIDE_LENGTH) * (y - H_SIDE_LENGTH);
        if ((x_2 + y_2) <= (RADIUS * RADIUS)) {
            circle_points++;
        }
        square_points++;
    }
    return 4.0 * (circle_points / square_points);
}

// structure for message queue
struct message {
    long msg_type;
    double monteCarloValue;
};
int main() {
    key_t my_key;
    my_key = ftok("1.txt", 17);
    int procesCount = 0;
    int numberOfPoints = 0;
    double mean = 0.0;
    double sum = 0.0;
    printf("Pleas type how many processes you need. Max is %d: ", PROCESS_COUNT);
    scanf("%d", &procesCount);
    printf("Pleas type how many number of points you need: ");
    scanf("%d", &numberOfPoints);
    if (procesCount <= PROCESS_COUNT && procesCount > 0) {
        for (int i = 0; i < procesCount; ++i) {
            if (fork() == 0) {
                int msg_id = msgget(my_key, 0666 | IPC_CREAT);
                struct message msg_send;
                msg_send.msg_type = 1;
                msg_send.monteCarloValue = monteCarlo(numberOfPoints+i);
                printf("Send msg is: %f\n", msg_send.monteCarloValue);
                msgsnd(msg_id, &msg_send, sizeof(msg_send), msg_send.monteCarloValue); //send message
                exit(0);
            } else {
                int msg_id = msgget(my_key, 0666 | IPC_CREAT);
                struct message msg_r;
                msgrcv(msg_id, &msg_r, sizeof(msg_r), 1, 0);
                msgctl(msg_id, IPC_RMID, NULL);
                printf("Received msg is : %f \n", msg_r.monteCarloValue);
                sum += msg_r.monteCarloValue;
            }
        }
    } else {
        printf("Wrong number of processes.\n");
        exit(1);
    }

    printf("Monte Carlo simulation mean is: %f\n", sum / procesCount);
    for (int i = 0; i < procesCount; ++i) {
        wait(NULL);
    }
}