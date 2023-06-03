/* 内存映射 */
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int main(void){
    // 内存映射
    // MAP_ANONYMOUS: 显示为定义标识符, 可以忽略该错误
    // 表示调用 mmap函数, 让系统自动分配 8192大小的内存, 进行读/写操作, 非文件操作, fd和 offset参数忽略
    char* start = mmap(NULL, 8192, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if(start == MAP_FAILED){
        perror("mmap");
        return -1;
    }
    // printf("No Problem\n");

    // 内存使用
    // 向 start地址中复制 "Hello World"字符串
    strcpy(start, "Hello World");   // 写入数据
    printf("%s\n", start);

    // 解除映射
    // if(munmap(start, 8192) == -1){
    //     perror("munmap");
    //     return -1;
    // }

    // 解除一个页的映射
    munmap(start, 4096);
    // 算出解除一个页后的地址
    char* p2 = start + 4096;
    strcpy(p2, "Hello World!");
    printf("%s\n", p2);
    if(munmap(p2, 4096) == -1){
        perror("munmap");
        return -1;
    }

    // 解除映射后读取数据会发生段错误
    // printf("%s\n", start);
    return 0;
}
