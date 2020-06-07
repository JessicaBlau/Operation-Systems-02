#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "ipc.h"

int pipeArray[2];
int flag = 1, ballNum = 0;
int FatherID, ChildID;

void signalParent(int sigNum){
    read(pipeArray[0], &ballNum, sizeof(ballNum));
    if(ballNum > 5){
            flag = 0;
    }
    else{
        printf("%d\n", ballNum++);
        write(pipeArray[1], &ballNum, sizeof(ballNum));
        sleep(1);
        kill(ChildID, SIGUSR1);
    }
}
void signalChild(int sigNum){
    read(pipeArray[0], &ballNum, sizeof(ballNum));
    printf("%d\n", ballNum++);
    write(pipeArray[1], &ballNum, sizeof(ballNum));
    sleep(1);
    kill(FatherID, SIGUSR1);
    
    if(ballNum == 6){
      exit(0);
    }
}
int main(){
    if (pipe(pipeArray) == -1){
        perror("fail pipe");
    }

    pid_t pid = fork(); // created a child

    if (pid == -1){
        printf("Fork error\n");
        return -1;
    }
    else if (pid == 0){
        FatherID = getppid();
        signal(SIGUSR1, signalChild);
        write(pipeArray[1], &ballNum, sizeof(ballNum));
        kill(FatherID, SIGUSR1);
    }
    else{
        ChildID = pid;
        signal(SIGUSR1, signalParent);
    }

    while(flag);
    wait(NULL);
    printf("Parent is going to be terminated\n");
    printf("child is going to be terminated\n");
    close(pipeArray[0]);
    close(pipeArray[1]);

    return 0;

}

