/* 非阻塞方式回收 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void){
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return 0;
    }
    // 子进程代码, 暂时不结束
    if(pid == 0){
        printf("%d 进程: 子进程尚未结束...\n", getpid());
        sleep(10);
        return 0;
    }
    for(;;){
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        printf("非阻塞结束\n");
        // pid_t pid_ = wait(NULL);    // 阻塞: 如果被阻塞了会停在这里, 可以取消注释看看两者的区别
        // printf("阻塞结束\n");
        if(pid == -1){
            if(errno == ECHILD){
                printf("%d进程: 没有子进程了\n", getpid());
                break;
            }else{
                perror("Waitpid");
                return -1;
            }
        }else if(pid == 0){
            printf("%d 子进程正在运行...\n", getpid());
            sleep(1);
        }else{
            printf("%d 进程: 回收 %d 子进程\n", getpid(), pid);
        }
    }
    return 0;
}


