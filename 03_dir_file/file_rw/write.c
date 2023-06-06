/* 文件写操作 */
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void){
    // 打开文件
    int fd = open("./shared.txt", O_WRONLY | O_CREAT | O_EXCL, 0664);
    if(fd == -1){
        perror("Open");
        return -1;
    }

    // 写入数据
    char* buf = "Hello World";
    ssize_t size = write(fd, buf, strlen(buf));
    if(size == -1){
        perror("Write");
        return -1;
    }
    printf("实际写入的字节数 : %ld\n", size);

    // 关闭文件
    close(fd);
    return 0;
}
