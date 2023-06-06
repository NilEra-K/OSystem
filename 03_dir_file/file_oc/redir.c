/* 三个文件描述符宏的重定向操作 */
#include <stdio.h>
#include <fcntl.h>      // 调用 open
#include <unistd.h>     // 调用 close
// Linux 中有 ./a.out >a.txt可以将输出输出到 a.txt中
// 这个操作本质上和重定向操作相同
int main(void){
    // STDOUT_FILENO 1
    // 解除 文件描述符 1和标准输出的关系
    close(STDOUT_FILENO);
    // 重定向
    int fd = open("./redir.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    printf("fd = %d", fd);  // [Out] fd = 1

    /* -------------------------------------------------------------------- */
    // 同理重定向 0 —— 标准输入, 即表示不从键盘上读入数据, 而是从重定向后的文件读取数据 
    close(STDIN_FILENO);
    int fd_ = open("redir.in", O_RDONLY);
    if(fd_ == -1){
        perror("open");
        return -1;
    }
    int a = 0, b = 0;
    scanf("%d%d", &a, &b);
    printf("a = %d, b = %d", a, b);
    return 0;
}
