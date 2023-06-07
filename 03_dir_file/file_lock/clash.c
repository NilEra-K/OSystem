/* 写冲突 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
// ./a.out hello
// ./a.out world
// [Out] wohrelldlo
// argv 记录的是命令行首地址, argv[]有两个参数 
// argv[1] 记录的是第二个参数 hello字符串首字符'h'的首地址, 即 argv第二个参数的首地址
// argv[1][0] 记录的是第二个参数的首地址的内容'h', 等价于 *(argv[1])
// argv[1][1] 记录的是第二个参数字符串的第二个字符的内容'e', 等价于 *(argv[1]+1)
// &argv[1][1] 为 'e'的地址
int main(int argc, char* argv[]){
    printf("argv[0] = %s, argv[1] = %s\n", argv[0], argv[1]);
    if(argc < 2){
        fprintf(stderr, "用法: ./a.out <字符串>\n");
        return -1;
    }
    // 打开文件
    int fd = open("./shared.txt", O_WRONLY | O_CREAT | O_APPEND, 0664);
    if(fd == -1){
        perror("Open");
        return -1;
    }
    // 放慢程序向文件写入字符串的速度
    // 一个字符一个字符地写
    for(int i = 0; i< strlen(argv[1]); i++){
        if(write(fd, &argv[1][i], sizeof(argv[1][i])) == -1){
            perror("Write");
            return -1;
        }
        sleep(1);   // 暂停 1s, 1s写一个字符
    }
    // 关闭文件
    close(fd);
    return 0;
}
