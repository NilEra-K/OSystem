/* kill 函数发送信号 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void sigFunc(int signum){
    printf("%d 进程 : 捕获到 %d 号信号\n", getpid(), signum);
}

// 用来判断进程是否存在
int isExist(pid_t pid){
    if(kill(pid, 0) == -1){
        if(errno == ESRCH){ // kill 失败是因为进程不存在
            return 1;
        }else{
            perror("KILL");
            exit(-1);
        }
    }
    return 0;   // kill 成功, 表示进程 pid存在
}

int main(void){
    // 创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }

    // 子进程对 2 号信号进行捕获
    if(pid == 0){
        printf("%d 进程 : 我是子进程\n", getpid());
        // if(signal(SIGINT, sigFunc) == SIG_ERR){
        //     perror("Signal");
        //     return -1;
        // }
        sleep(10);
        return 0;
    }    

    // 父进程向子进程发送 2号信号
    printf("%d 进程 : 我要向子进程 %d发送 2号信号\n", getpid(), pid);
    getchar();  // 敲一个按键才会发送信号
    if(kill(pid, SIGINT) == -1){
        perror("Kill");
        return -1;
    }
    getchar();
    printf("子进程%s\n", isExist(pid) ? "不存在" : "存在");
    if(wait(NULL) == -1){
        perror("Wait");
        return -1;
    }
    printf("子进程%s\n", isExist(pid) ? "不存在" : "存在");
    return 0;
}




