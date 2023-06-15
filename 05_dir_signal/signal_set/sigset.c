/* 信号集操作 */
// #define _POSIX_C_SOURCE 2
// #define _XOPEN_SOURCE 1
// #define _POSIX_SOURCE 1
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


// 输出一个字节八个比特位的值
void printb(char byte){
    for(int i = 0; i < 8; i++){
        printf("%d", byte & 1 << (7 - i) ? 1 : 0);
    }
    printf(" ");
}

// 输出一个缓冲区里所有字节的比特位值
// buf 接受缓冲区的首地址
// size 接受缓冲区的大小
void printm(void* buf, size_t size){
    // 从最后一个字节开始, 倒着输出
    for(int i = 0; i < size; i++){
        // buf 优先类型转换
        printb(((char*)buf)[size - i - 1]);
        if((i + 1) % 8 == 0){
            printf("\n");
        }
    }
}

int main(void){
    // 信号集类型的变量
    sigset_t s;
    printf("填满信号集\n");
    sigfillset(&s);
    printm(&s, sizeof(s));

    printf("清空信号集\n");
    sigemptyset(&s);
    printm(&s, sizeof(s));

    printf("添加 2号信号\n");
    sigaddset(&s, SIGINT);
    printm(&s, sizeof(s));

    printf("添加 3号信号\n");
    sigaddset(&s, SIGQUIT);
    printm(&s, sizeof(s));

    printf("删除 2号信号\n");
    sigdelset(&s, SIGINT);
    printm(&s, sizeof(s));

    printf("信号集中 %s 2号信号\n", sigismember(&s, SIGINT) ? "存在" : "不存在");
    printf("信号集中 %s 3号信号\n", sigismember(&s, SIGQUIT) ? "存在" : "不存在");
    return 0;
}

