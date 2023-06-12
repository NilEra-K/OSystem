/* 回收子进程 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    // 创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }

    // 子进程代码
    if(pid == 0){
        printf("%d 进程, 我是子进程\n", getpid());
        sleep(5);
        printf("我要结束了\n");
        // 正常终止尝试
        // exit(0);
        // _exit(0);
        // _Exit(0);
        // return 0;
        // 异常终止尝试
        // abort(); // 调用 abort()函数会使进程以 6号信号终止
        // 段错误 -> 会以 11号信号终止
        int* p = NULL;
        *p = 1;
    }

    // 父进程代码
    int s = 0;  // 用来输出子进程的终止状态
    pid_t childpid = wait(&s);  // 这里调用 wait函数, 传入 s, 会将终止状态传递给 s
    if(childpid == -1){
        perror("Wait");
        return -1;
    }
    printf("%d 进程: 我是父进程, 回收了 %d 进程的僵尸\n", getpid(), childpid);

    if(WIFEXITED(s)){
        // 真 : 正常终止
        printf("正常终止: %d\n", WEXITSTATUS(s));
    } else {
        // 假 : 异常终止
        printf("异常终止: %d\n", WTERMSIG(s));
    }
    return 0;
}




