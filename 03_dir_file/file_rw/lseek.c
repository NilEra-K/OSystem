/* 文件读写位置 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    // 打开文件
    int fd = open("./lseek.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("Open");
        return -1;
    }
    // 向文件中写入数据
    char* buf = "Hello World!";
    if(write(fd, buf, strlen(buf)) == -1){
        perror("Write");
        return -1;
    }
    // 修改文件读写位置
    if(lseek(fd, -6, SEEK_END) == -1){
        perror("lseek");
        return -1;
    }
    // 再次向文件中写入数据
    buf = "LINUX_";
    if(write(fd, buf, strlen(buf)) == -1){
        perror("Write");
        return -1;
    }
    // 查看 lseek.txt // [Out]: Hello Linux_
    
    // 修改文件读写位置
    if(lseek(fd, 8, SEEK_END) == -1){
        perror("lseek");
        return -1;
    }

    buf = "Third Input";
    if(write(fd, buf, strlen(buf)) == -1){
        perror("Write");
        return -1;
    }
    // [Out] 形成文件空洞 Hello LINUX_\0\0\0\0Third Input
    // 关闭文件
    close(fd);
    return 0;
}
