/* 太平间信号 */
#define     PID_NUM     5
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void sigchild(int signum){
    sleep(3);   // 信号处理函数休眠 3秒
    printf("%d 进程: 捕获到 %d 信号\n", getpid(), signum);
    for(;;){    // 修改代码, 如果不能一个信号收一次尸, 那么我们希望一次信号尽可能多的收尸
        pid_t pid = wait(NULL);
        if(pid == -1){
            if(errno == ECHILD){
                printf("%d 进程: 没有子进程了\n", getpid());
                break;
            }else{
                 perror("Wait");
                return;
            }
        }
        printf("%d 进程: 回收了 %d进程的僵尸\n", getpid(), pid);
    }
}

void sigchild_(int signum){
    sleep(3);   // 信号处理函数休眠 3秒
    printf("%d 进程: 捕获到 %d 信号\n", getpid(), signum);
    for(;;){
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if(pid == -1){
            if(errno == ECHILD){
                printf("%d 进程 : 没有子进程了\n", getpid());
                break;
            }else{
                perror("Waitpid");
                return;
            }
        }else if(pid == 0){
            printf("%d进程 : 子进程正在运行, 无法收尸\n", getpid());
            break;
        }else{
            printf("%d进程 : 回收了 %d 进程的僵尸\n", getpid(), pid);
        }
    }
}

int main(void){
    // 对 17号信号进行捕获 -> wait函数 -> 阻塞式
    // if(signal((SIGCHLD), sigchild) == SIG_ERR){
    //     perror("Signal");
    //     return -1;
    // }

    // 对 17号信号进行捕获 -> waitpid函数 -> 非阻塞式
    if(signal((SIGCHLD), sigchild_) == SIG_ERR){
        perror("Signal");
        return -1;
    }

    // 创建多个子进程
    for(int i = 0; i < PID_NUM; i++){
        pid_t pid = fork();
        if(pid == -1){
            perror("Fork");
            return -1;
        }
        if(pid == 0){
            printf("%d进程 : 我是子进程\n", getpid());
            sleep(1);   // 使多个进程同时到达
            return 0;
        }
    }
    // 定义一个长时间不结束的进程
    pid_t pid_  = fork();
    if(pid_ == -1){
        perror("Fork");
        return -1;
    }
    if(pid_ == 0){
        printf("%d 进程: 六号进程\n", getpid());
        sleep(15);
        return  0;
    }

    // 父进程代码
    while(1){}
    return 0;
}

