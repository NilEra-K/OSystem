/* 文件读操作 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    // 打开文件
    int fd = open("./shared.txt", O_RDONLY);
    if(fd == -1){
        perror("Open");
        return -1;
    }

    // 读取文件内容
    char buf[128];
    ssize_t size = read(fd, buf, sizeof(buf)-1);
    if(size == -1){
        perror("Write");
        return -1;
    }
    printf("buf : %s\n", buf);
    // 关闭文件
    close(fd);
    return 0;
}



