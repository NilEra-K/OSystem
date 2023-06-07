/* 修改文件大小 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    int fd = open("./truncate.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("Open");
        return -1;
    }
    // 向文件写入 abcde
    char* buf = "abcde";
    if(write(fd, buf, strlen(buf)) == -1){
        perror("Write");
        return -1;
    }
    // 修改文件大小为 3字节
    if(truncate("./truncate.txt", 3) == -1){
        perror("truncate");
        return -1;
    }

    // 修改文件回 5字节
    if(ftruncate(fd, 5) == -1){
        perror("ftruncate");
        return -1;
    }
    close(fd);
}

