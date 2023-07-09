/* 条件变量解决 生产者-消费者问题 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// 准备全局变量
char storage[10];   // 仓库
int stock = 0;      // 库存量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // 互斥锁
pthread_cond_t pcond = PTHREAD_COND_INITIALIZER;    // 生产者条件变量
pthread_cond_t ccond = PTHREAD_COND_INITIALIZER;    // 消费者条件变量

// 生产者线程

int main(void){

    return 0;
}

