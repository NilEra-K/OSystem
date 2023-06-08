/* 内存映射文件 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void){
    // 打开文件
    int fd = open("./fmap.txt", O_RDWR  | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    // 修改文件大小
    if(ftruncate(fd, 4096) == -1){
        perror("ftruncate");
        return -1;
    }
    // 内存映射文件 - 需要文件有大小
    char* start = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(start == MAP_FAILED){
        perror("mmap");
        return -1;
    }
    // 写入文件
    strcpy(start, "abcdefg");       // 相当于写文件
    // 读取文件
    printf("%s\n", start);          // 相当于读文件
    // 解除映射关系
    if(munmap(start, 4096) == -1){
        perror("munmap");
        return -1;
    }
    // 关闭文件
    close(fd);
}

