/* 通过加锁方式解决冲突 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// 加锁函数
int wlock(int fd, int wait){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;   // 两个参数制定锁起点为文件头
    lock.l_len = 0;     // 0 表示一直锁到文件尾
    lock.l_pid = -1;
    return fcntl(fd, wait ? F_SETLKW : F_SETLK, &lock); // 三目运算符
                                                        // wait = 1返回阻塞模式加锁
                                                        // wait = 0返回非阻塞模式加锁
}

// 解锁函数
int unlock(int fd){
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = -1;
    return fcntl(fd, F_SETLK, &lock);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "用法: ./a.out <字符串>\n");
        return -1;
    }
    int fd = open("./lock.txt", O_WRONLY | O_CREAT | O_APPEND, 0664);
    if(fd == -1){
        perror("Open");
        return -1;
    }
    // 写之前加锁——阻塞方式
    // if(wlock(fd, 1) == -1){
    //     perror("Wlock");
    //     return -1;
    // }

    // 非阻塞方式加锁
    while(wlock(fd, 0) == -1){
        // 干点别的
        if(errno == EACCES || errno == EAGAIN){
            // printf不加 '\n', 输出到缓冲区, 程序技术后一股脑从缓冲区输出一堆
            // printf中加 '\n', 则逐行从缓冲区输出
            printf("Wait A Minute, Doing Somethings Now...\n");
            sleep(1);
        }else{
            perror("wlock");
            return -1;
        }
    }

    for(int i = 0; i < strlen(argv[1]); i++){
        if(write(fd, &argv[1][i], sizeof(argv[1][i])) == -1){
            perror("Write");
            return -1;
        }
        sleep(1);
    }
    // 解锁
    if(unlock(fd) == -1){
        perror("Unlock");
        return -1;
    }
    // 关闭文件
    close(fd);
}


