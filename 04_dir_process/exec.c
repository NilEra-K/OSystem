/* 新进程的创建 */
#include <stdio.h>
#include <unistd.h>

int main(void){
    printf("#============================#\n");
    printf("%d 进程: 创建新进程\n", getpid());
    printf("#============================#\n");

    // 命令行参数, 第一个参数为./new 对应 argv[0]
    // [Warning]: Missing Sentinel In Function Call -> 注意 execl的参数需要给他一个 NULL 作为结束的标志
    if(execl("./exec_new", "./exec_new", "hello", "123", NULL) == -1){
        perror("EXECL");
        return -1;
    }

    // 还可以变成命令行的命令
    // execl("/bin/ls", "ls", "-l", NULL);

    // execlp 用法
    // execlp("./new", "ls", "-l", "--color=auto", NULL);

    // execle 用法
    // char* envp[] = {"NAME=nilera", "AGE=18", "FOOD=DANTA", NULL};
    // execle("./new", "new", "hello", "123", NULL, envp[]);
    return 0;
}


