/* 回收多个子进程 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void){
    // 创建多个子进程 -> 下面的代码负责创建 5个子进程
    // 可以注释 pid == 0的部分, 没有 return时会创建 32个进程
    for(int i = 0; i < 5; i++){
        pid_t pid = fork();
        if (pid == -1){
            perror("Fork");
            return -1;
        }
        if(pid == 0){
            printf("%d 进程: 我是子进程\n", getpid());
            sleep(i + 1);
            return i;
        }
    }

    // 回收多个子进程
    // 死循环
    for(;;){
        int s = 0;
        pid_t pid = wait(&s);
        if(pid == -1){
            if(errno = ECHILD){
                printf("没有子进程回收\n");
                break;
            }else{
                perror("Wait");
                return -1;
            }
        }
        printf("%d 进程: 回收了 %d 进程 \n", getpid(), pid);
        if(WIFEXITED(s)){
            // 真 : 正常终止
            printf("正常终止: %d\n", WEXITSTATUS(s));
        } else {
            // 假 : 异常终止
            printf("异常终止: %d\n", WTERMSIG(s));
        }
    }
    return 0;
}


