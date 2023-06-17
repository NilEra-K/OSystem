/* 写入管道 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void){
    // 创建有名管道文件
    printf("%d 进程 : 创建有名管道文件\n", getpid());
    if(mkfifo("./fifo", 0664) == -1){
        perror("Mkfifo");
        return -1;
    }

    // 打开有名管道文件
    printf("%d 进程 : 打开有名管道文件\n", getpid());
    int fd = open("./fifo", O_WRONLY);
    if(fd == -1){
        perror("Open");
        return -1;
    }

    // 写入有名管道文件
    printf("%d 进程 : 写入有名管道文件\n", getpid());
    for(;;){
        // 通过键盘获取要写入的数据
        char buf[128];
        fgets(buf, sizeof(buf), stdin);
        
        // 设置输入 ！ 退出循环
        if(strcmp(buf, "!\n") == 0){
            break;
        }

        // 将数据写入管道文件
        if(write(fd, buf, strlen(buf)) == -1){
            perror("Write");
            return -1;
        }

    }

    // 关闭有名管道文件
    printf("%d 进程 : 关闭有名管道文件\n", getpid());
    close(fd);

    // 删除有名管道文件
    printf("%d 进程 : 删除有名管道文件\n", getpid());
    unlink("./fifo");
    printf("FINISHED\n");
    return 0;
}




