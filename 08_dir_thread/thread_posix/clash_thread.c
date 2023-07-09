/* 线程并发冲突 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

// 全局变量
int a = 0;

// 线程过程函数
void* pthread_func(void*){
    for(int i = 0; i < 1000000; i++){
        a++;
    }
    return NULL;
}

int main(void){
    pthread_t tid_1;
    pthread_t tid_2;
    pthread_create(&tid_1, NULL, pthread_func, NULL);
    pthread_create(&tid_2, NULL, pthread_func, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    printf("a = %d\n", a);
    return 0;
}



