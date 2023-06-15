/* 睡眠 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigFunc(int signum){
    printf("%d 进程: %d号信号处理开始\n", getpid(), signum);
    sleep(3);
    printf("%d 号信号处理结束\n", signum);
}

int main(void){
    // 创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }

    // 子进程暂停
    if(pid == 0){
        // 对 2号进行捕获
        if(signal(SIGINT, sigFunc) == SIG_ERR){
            perror("Signal");
            return -1;
        }
        printf("%d 进程 : 子进程准备睡眠\n", getpid());
        int res = sleep(15);
        printf("%d进程 : sleep函数返回 %d\n", getpid(), res);
        return 0;
    }

    // 父进程给子进程发信号, 打断子进程
    printf("%d 进程 : 父进程, 准备给子进程发送 2号信号\n", getpid());
    getchar();
    if(kill(pid, SIGINT) == -1){
        perror("Kill");
        return -1;
    }
    if(wait(NULL) == -1){
        perror("Wait");
        return -1;
    }
    return 0;
}
