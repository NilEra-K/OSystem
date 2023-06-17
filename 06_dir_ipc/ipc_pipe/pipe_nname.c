/* 无名管道 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void){
    // 父进程创建无名管道
    printf("%d 进程 : 创建无名管道\n", getpid());
    int fd[2];
    if(pipe(fd) == -1){
        perror("Pipe");
        return -1;
    }
    printf("fd[0] = %d\n", fd[0]);
    printf("fd[1] = %d\n", fd[1]);

    // 父进程创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }

    // 子进程负责接受数据
    if(pid == 0){
        printf("%d 进程 : 子进程, 关闭写端\n", getpid());
        printf("fd[0] = %d\n", fd[0]);
        printf("fd[1] = %d\n", fd[1]);
        close(fd[1]);   // 关闭写端
        printf("%d 进程 : 子进程, 接受数据\n", getpid());
        for(;;){
            char buf[128] = {};
            ssize_t size = read(fd[0], buf, sizeof(buf)-1);
            printf("size = %ld\n", size);
            if(size == 0){
                printf("%d 进程 : 父进程关闭写端\n", getpid());
                break;
            }
            if(size == -1){
                perror("Read");
                return -1;
            }
            printf(">> %s\n", buf);
        }
        printf("%d 进程 : 关闭读端\n", getpid());
        close(fd[0]);
        printf("%d 进程 : FINISHED...\n", getpid());
        return 0;
    }

    // 父进程负责发送数据
    printf("%d 进程 : 关闭读端\n", getpid());
    close(fd[0]);   //关闭读端
    printf("%d 进程 : 发送数据\n", getpid());
    for(;;){
        char buf[128] = {};
        fgets(buf, sizeof(buf), stdin);
        if(strcmp(buf, "!\n") == 0){
            break;
        }
        if(write(fd[1], buf, strlen(buf))== -1){
            perror("Write");
            return -1;
        }
    }
    printf("%d 进程 : 关闭写端\n", getpid());
    close(fd[1]);
    if(wait(NULL) == -1){
        perror("Wait");
        return -1;
    }
    printf("FINISHED\n");
    return 0;
}

