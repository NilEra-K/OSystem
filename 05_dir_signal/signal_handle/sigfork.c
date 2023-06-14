/* 子进程是否会继承父进程的信号处理方式 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// 信号处理函数
void sigFunc(int signum){
    printf("%d进程 : 捕获到 %d 号信号\n", getpid(), signum);
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
    
    // 创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }

    // 子进程代码
    if(pid == 0){
        printf("%d 进程 : 我是子进程\n", getpid());
        sleep(20);
        return 0;
    }

    // 父进程代码
    if(wait(NULL) == -1){
        perror("Wait");
        return -1;
    }
    printf("%d 进程 : 回收了子进程的僵尸\n", getpid());
    return 0;
}
// 需要使用 kill 命令给子进程发信号
// kill -2 process_num  // 发送 2号信号给 process_num进程
// kill -3 process_num  // 发送 3号信号给 process_num进程

