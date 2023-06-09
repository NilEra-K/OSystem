/* 孤儿进程演示 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    // 父进程创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return 0;
    }
    // 子进程代码
    if(pid == 0){
        printf("%d进程: 我是子进程, 我的父进程是 %d\n", getpid(), getppid());
        sleep(2);   // 等待父进程死亡
        printf("%d进程: 我是子进程, 我的父进程是 %d\n", getpid(), getppid());        
        return 0;
    }
    // 父进程代码
    printf("%d进程: 我是子进程, 我的父进程是 %d\n", getpid(), pid);
    sleep(1);
    return 0;
}

