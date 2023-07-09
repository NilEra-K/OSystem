/* 分离线程 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// 线程过程函数
void* pthread_func(void*){
    for(int i = 0; i < 100; i++){
        putchar('-');
        usleep(50000);  // 休眠 0.05s
    }
    return NULL;
}

int main(void){
    setbuf(stdout, NULL);   // 关闭输出缓冲区
                            // 为了能够第一时间看到输出的字符
    pthread_t tid;
    int error = pthread_create(&tid, NULL, pthread_func, NULL);
    if(error){
        fprintf(stderr, "pthread_create: %s\n", strerror(error));
    }
    // pthread_join(tid, NULL); // NULL: 不接受线程的返回值
    // 将线程设置成分离线程 : 内核负责回收线程资源
    pthread_detach(tid);
    for(int i = 0; i < 100; i++){
        putchar('+');
        usleep(100000); // 休眠 0.1s
    }
    printf("\n");
    return 0;
}

