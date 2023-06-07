/* 文件描述符的复制 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    // 打开文件, 得到文件描述符 fd1
    int fd1 = open("./dup.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd1 == -1){
        perror("Open");
        return -1;
    }
    // 复制文件描述符, 得到 fd2
    // int fd2 = dup(fd1);
    // dup2(fd1, 1)表示将文件描述符 fd1=3对应的文件表型指针复制到文件描述符 1对应的项中
    // 从而 3和 1拥有相同的文件表项指针, 指向同一个文件表项
    int fd2 = dup2(fd1, 1);
    setbuf(stdout, NULL);   // 关闭输出缓冲区, 如果不关闭输出缓冲区, 屏幕和文件中都没有输出
    if(fd2 == -1){
        perror("dup");
        return -1;
    }
    printf("fd1 = %d\n", fd1);
    printf("fd2 = %d\n", fd2);
    // 通过 fd1向文件写入内容
    char* buf = "Hello World!";
    if(write(fd1, buf, strlen(buf)) == -1){
        perror("Write");
        return -1;
    }
    // 通过 fd2调整文件读写位置
    if(lseek(fd2, -6, SEEK_END) == -1){
        perror("lseek");
        return -1;
    }
    // 通过 fd1向文件写入内容
    buf = "Linux_";
    if(write(fd1, buf, strlen(buf)) == -1){
        perror("write2");
        return -1;
    }
    close(fd1);     // 所有文件描述符都要关, 才会释放文件表项
    close(fd2);     // 所有文件表项被关闭, v节点才被释放
    return 0;
}

