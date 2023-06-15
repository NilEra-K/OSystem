/* 闹钟 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigFunc(int signum){
    printf("%d 进程 : 捕获到 %d 信号\n", getpid(), signum);
}

int main(void){
    // 捕获到 14号信号
    if(signal(SIGALRM, sigFunc) == SIG_ERR){
        perror("Signal");
        return -1;
    }

    // 设置闹钟
    printf("alarm(10) 返回 %d \n", alarm(10));
    getchar();
    printf("此时 alarm(5) 返回 %d \n", alarm(5));
    for(;;);
    return 0;
}
