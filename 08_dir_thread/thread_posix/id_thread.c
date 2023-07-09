/* 线程的 ID */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

// 线程过程函数
void* pthread_func(void*){
    printf("子线程 : 进程的 PID: %d\n", getpid());
    printf("子线程 : POSIX TID: %lu\n", pthread_self());
    printf("子线程 : 系统内核 TID: %ld\n", syscall(SYS_gettid));
    return NULL;
}

int main(void){
    printf("主线程 : 进程的 PID: %d\n", getpid());
    printf("主线程 : POSIX TID: %lu\n", pthread_self());
    printf("主线程 : 系统内核 TID: %ld\n", syscall(SYS_gettid));
    pthread_t tid;
    pthread_create(&tid, NULL, pthread_func, NULL);
    pthread_join(tid, NULL);
    return 0;
}


