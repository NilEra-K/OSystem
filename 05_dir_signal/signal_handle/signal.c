/* 信号处理 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

void sigFunc(int signum){
    printf("%d 进程: 捕获到 %d号信号\n", getpid(), signum);
}

int main(void){
    // 忽略 SIGINT (2号信号) Ctrl + C
    // SIG_IGN 其实就是被强转为 sighandler_t指针类型之后的 1
    sighandler_t ret = signal(SIGINT, SIG_IGN);
    if(ret == SIG_ERR){
        perror("Signal");
        return -1;
    }
    printf("ret = %p\n", ret);
    ret = signal(SIGINT, sigFunc);
    if(ret == SIG_ERR){
        perror("Signal");
        return -1;
    }
    printf("ret = %p\n", ret);  // 上一次忽略处理, 返回 SIG_IGN -> 0x1

    // 恢复默认处理
    ret = signal(SIGINT, SIG_DFL);
        if(ret == SIG_ERR){
        perror("Signal");
        return -1;
    }
    printf("ret = %p\n", ret);
    printf("sigFunc = %p\n", sigFunc);
    for(;;);
    return 0;
}

