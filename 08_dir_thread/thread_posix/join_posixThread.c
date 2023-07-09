/* 线程的汇入 */
/* 使用 pthread_join 函数 */
#define PI  3.1415926
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// 线程过程函数, 计算圆的面积
void* pthread_area(void* arg){
    double r = *(double*)arg;
    /* ===============================================================================================
    double static S;    // 如果是 double S 的话会因为变量的生命周期过短
                        // 函数结束时 S也会消失, 其所对应的地址空间会被释放
                        // 我们再进行访问就会访问到野指针
                        // 而声明 S为静态成员变量则会延长其生命周期, 静态成员变量的生命周期是进程级的
                        // [注意] 因为 S是静态变量成员, 所以其占用一块固定的存储区, 所以会出现 *覆盖问题*
                        // 即: 当调用 pthread_join() 函数的时候可能因为时间问题产生覆盖存储区的问题, 输出相同的结果
    ____________________*/
    
    // 更换为 malloc() 动态分配内存, 其存储区的生命周期会一直延续到用 free() 函数释放
    // 也就是说, S在线程结束后已经释放/销毁/失效了, 但是这块存储区是一直有效的, 其已经给到了函数的返回值
    double* S = malloc(sizeof(double));
    *S = PI * r * r;
    return S;
}

int main(void){
    pthread_t tid;
    double r = 10;
    double* rlt;        // 用于输出线程过程函数的返回值
    pthread_create(&tid, NULL, pthread_area, &r);
    // pthread_join(tid, (void**)&rlt);    // pthread_join(pthread_t tid, void** retval);
    //                                     // 第二个参数需要传入 void** 型的二级指针
    // printf("圆的面积 = %lu 线程的返回值 = %lg\n", pthread_self(), *rlt);

    pthread_t tid_2;
    double r_2 = 20;
    double* rlt_2;
    pthread_create(&tid_2, NULL, pthread_area, &r_2);
    // pthread_join(tid_2, (void**)&rlt_2);
    // printf("圆的面积 = %lu 线程的返回值 = %lg\n", pthread_self(), *rlt_2);

    // 当使用 double static S; 时
    // 下面的这种写法就会出现所谓的 *覆盖问题* , 输出
    // 圆的面积 = 140005025752896 线程的返回值 = 314.159 | 1256.64 | 314.159
    // 圆的面积 = 140005025752896 线程的返回值 = 314.159 | 1256.64 | 1256.64
    pthread_join(tid, (void**)&rlt);
    printf("圆的面积 = %lu 线程的返回值 = %lg\n", pthread_self(), *rlt);
    free(rlt);      // 释放 rlt 所占据的存储区, 也就是函数中 S所占据的地址
    pthread_join(tid_2, (void**)&rlt_2);
    printf("圆的面积 = %lu 线程的返回值 = %lg\n", pthread_self(), *rlt_2);
    free(rlt_2);    // 释放 rlt_2 所占据的存储区, 也就是函数中 S所占据的地址
    return 0;
}

