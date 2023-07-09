/* 线程同步-互斥锁 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

// 全局变量
int a = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // 互斥锁, 全局

// 线程过程函数
void* pthread_func(void*){
    // 加锁
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < 1000000; i++){
        a++;
    }
    // 解锁
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(void){
    // 互斥锁: 互斥锁在这里声明并不合适
    // 互斥锁要在线程中使用, 如果在这里声明的话, 是属于 main函数的局部成员
    // 而使用时需要这些线程互相竞争锁, 因此需要声明全局变量
    // pthread_mutex_t mutex;
    pthread_t tid_1;
    pthread_t tid_2;
    pthread_create(&tid_1, NULL, pthread_func, NULL);
    pthread_create(&tid_2, NULL, pthread_func, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    printf("a = %d\n", a);
    return 0;
}

