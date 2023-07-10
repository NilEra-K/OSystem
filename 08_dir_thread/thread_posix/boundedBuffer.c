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

// 显示库存
void show(char* who, char* op, char prod){
    printf("%s: ", who);
    for(int i = 0; i < stock; i++){
        printf("%c", storage[i]);
    }
    printf("%s%c\n", op, prod);
}

// 生产者线程
void* producer(void* arg){
    char* who = (char*)arg;
    for(;;){
        // 加锁
        pthread_mutex_lock(&mutex); // 这里加了锁
                                    // 下面判断仓库条件时候传入该锁
                                    // 保证在睡入时可以加锁
        
        // 仓库是否满了
        if(stock == 10){
            // 输入生产者卧室
            printf("%s: 满仓\n", who);
            pthread_cond_wait(&pcond, &mutex);  // 睡入时配合锁使用
        }

        // 生产
        char prod = 'A' + rand() % 26;
        show(who, "<--", prod);         // 调用显示函数
        storage[stock] = prod;
        stock++;
        printf("+");

        // 唤醒消费者
        pthread_cond_signal(&ccond);    // 生产者只要有生产了就表示仓库非空
                                        // 仓库非空消费者就可以消费, 唤醒消费者

        // 解锁
        pthread_mutex_unlock(&mutex);
        usleep((rand() % 100)*1000);    // 0~99 ms
    }
    return NULL;
}

// 消费者线程
void* consumer(void* arg){
    char* who = (char*)arg;
    for(;;){
        // 加锁
        pthread_mutex_lock(&mutex);
        
        // 仓库是否空了
        if(stock == 0){
            printf("%s: 空仓\n", who);
            pthread_cond_wait(&ccond, &mutex);  // 睡入时配合锁使用
        }

        // 消费
        char prod = storage[--stock];
        show(who, "-->", prod);         // 调用显示函数
        printf("-");

        // 唤醒生产者
        pthread_cond_signal(&pcond);    // 消费者只要消费了就说明仓库非满
                                        // 仓库非满生产者就可以生产, 唤醒生产者

        // 解锁
        pthread_mutex_unlock(&mutex);
        usleep((rand() % 100)*1000);    // 0~99 ms
    }
    return NULL;
}

int main(void){
    pthread_t tid;
    pthread_create(&tid, NULL, producer, "生产者");
    pthread_create(&tid, NULL, consumer, "消费者");
    getchar();
    return 0;
}

