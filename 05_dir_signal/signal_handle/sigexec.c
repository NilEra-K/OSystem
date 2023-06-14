/* 新进程是否会继承旧进程的信号处理方式 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// 信号处理函数
void sigFunc(int signum){
    printf("%d 进程 : 捕获到 %d 号信号\n", getpid(), signum);
    return;
}

int main(void){
    // 忽略 2号信号
    if(signal(SIGINT, SIG_IGN) == SIG_ERR){
        perror("Signal");
        return -1;
    }
    
    // 捕获 3号信号
    if(signal(SIGQUIT, sigFunc) == SIG_ERR){
        perror("Signal");
        return -1;
    }

    // 创建新进程
    if(execl("./exec_new", "new", NULL) == -1){
        perror("Execl");
        return -1;
    }
    return 0;
}



