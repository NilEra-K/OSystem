/* 僵尸进程 */
#include <stdio.h>
#include <unistd.h>

int main(void){
    // 创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return 0;
    }
    // 子进程代码
    if(pid == 0){
        printf("%d进程: 我是子进程, 马上变成僵尸进程!\n", getpid());
        sleep(7);
    }
    // 父进程代码
    printf("%d进程: 我是父进程, 我很忙\n", getpid());
    sleep(15);
    return 0;
}

