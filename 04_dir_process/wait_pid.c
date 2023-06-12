/* 回收特定子进程 */
#define     PID_NUM     5
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    pid_t pids[PID_NUM];
    // 创建五个子进程
    for(int i = 0; i < PID_NUM; i++){
        pids[i] = fork();
        if(pids[i] == -1){
            perror("Fork");
            return -1;
        }
        printf("创建了 %d 进程\n", pids[i]);
        if(pids[i] == 0){
            printf("%d进程 : 第 %d 号进程\n", getpid(), i);
            sleep(i + 1);
            return 0;
        }
    }

    // 父进程回收子进程
    for(int i = PID_NUM-1; i >= 0; i--){
        printf("即将回收 %d 进程的僵尸\n", pids[i]);
        pid_t pid = waitpid(pids[i], NULL, 0);
        if(pid == -1){
            perror("Waitpid");
            return -1;
        }
        printf("回收了 %d 进程的僵尸\n", pid);
    }
    printf("回收结束\n");
    return 0;
}
