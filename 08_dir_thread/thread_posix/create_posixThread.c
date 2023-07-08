/* 创建线程-使用 POSIX接口 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// man 手册: man 3 pthread_create1
// Compile and link with -pthread.
// 编译时需要链接 pthread库
// gcc create_posixThread.c -o create_posixThread -lpthread

// 线程过程函数
void* pthread_func(void* arg){
    printf("%lu 线程 : 我是子线程, 接收到 %s\n", pthread_self(), (char*)arg);
    return NULL;
}

int main(void){
    printf("%lu 线程 : 我是主线程, 我要创建自己的子线程\n", pthread_self());
    pthread_t tid;
    int error = pthread_create(&tid, NULL, pthread_func, "Hello World");
    if(error){// 如果是 0则表示 pthread_create()正常执行, 非零则输出错误码
        fprintf(stderr, "pthread_create: %s\n", strerror(error));
        return -1;
    }
    printf("%lu 线程 : 我是主线程, 我创建了 %lu 子线程\n", pthread_self(), tid);
    sleep(1);   // 主线程结束过快, 会导致子线程还没被执行, 父线程就结束了
                // 如果不加 sleep() 就会看不到输出
    return 0;
}






