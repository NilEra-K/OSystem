/* 信号屏蔽 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// 信号处理函数
void sigFunc(int signum){
    printf("%d 进程 : 捕获到 %d 号信号\n", getpid(), signum);
}

// 假装更新数据库
void updateDataBase(void){
    for(int i = 0; i < 5; i++){
        printf("正在更新第 %d 条数据...\n", i + 1);
        sleep(1);
    }
}

int main(void){
    int signum = SIGINT;
    // 对 2号信号进行捕获处理
    if(signal(signum, sigFunc) == SIG_ERR){
        perror("Signal");
        return -1;
    }
    
    // 父进程屏蔽 2号信号
    printf("设置屏蔽 2号信号\n");
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, signum);

    sigset_t oldset;    // 用来输出原信号掩码
    if(sigprocmask(SIG_SETMASK, &sigset, &oldset) == -1){
        perror("Sigprocmask");
        return -1;
    }

    // 父进程创建子进程
    int pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }

    // 子进程负责给父进程发送 2号信号
    if (pid == 0){
        for(int i = 0; i < 5; i++){
            printf("%d 进程 : 我要向父进程发送 %d 号信号\n", getpid(), signum);
            kill(getppid(), signum);
        }
        return 0;
    }

    // 父进程假装更新数据库
    updateDataBase();

    // 解除信号屏蔽
    if(sigprocmask(SIG_SETMASK, &oldset, NULL) == -1){
        perror("Sigprocmask");
        return -1;
    }
    // 结束后会执行处理函数
    for(;;);
    return 0;
}


