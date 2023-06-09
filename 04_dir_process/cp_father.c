/* 子进程是父进程的副本 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global = 1;     // 数据区
int main(void){
    int local = 2;   // 栈区
    int* heap = malloc(sizeof(int));
    *heap = 3;
    printf("%d进程: %p: %d %p: %d %p: %d\n", getpid(), &global, global, &local, local, heap, *heap);
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }
    if(pid == 0){
        /* 子进程代码 */
        printf("%d进程: %p: %d %p: %d %p: %d\n", getpid(), &global, ++global, &local, ++local, heap, ++*heap);
        return 0;
    } 
    /* 父进程代码 */
    // 等待子进程执行结束
    sleep(1);
    // 观察父进程的相关变量地址有没有改变
    printf("%d进程: %p: %d %p: %d %p: %d\n", getpid(), &global, global, &local, local, heap, *heap);
    return 0;
}


