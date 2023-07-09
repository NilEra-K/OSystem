/* POSIX练习: 线程过程函数的传递 */
#define PI  3.1415926
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* pthread_area(void* arg){
    double r = *(double*)arg;
    double S = PI * r * r;
    *(double*)arg = S;
    printf("S = PI * r * r = %lg\n", S);
    return NULL;
}

void* pthread_mean(void* arg){
    // *d <=> d[0]
    // *(d + 1) <=> d[1];
    // *(d + 2) <=> d[2];
    double* d = (double*)arg;
    *(d + 2) = (*d + *(d + 1))/2;
    return NULL;
}

int main(void){
    pthread_t tid;  // 用来输出线程的 ID
    double r = 10;  // 半径
    // 创建新线程, 用于计算元的面积
    pthread_create(&tid, NULL, pthread_area, &r);
    sleep(1);
    printf("圆的面积为 : %lg\n", r);

    double data[3] = {6, 7, 0}; // 第一个元素是 3
                                // 第二个元素是 7
                                // 第三个元素是 输出型参数也叫"值结果参数"
    pthread_create(&tid, NULL, pthread_mean, data); // 数组名即数组的首地址
    sleep(1);
    printf("平均数为 : %lg\n", data[2]);
    return 0;
}



