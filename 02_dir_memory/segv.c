/* 段错误 */
#include <stdio.h>

int main(void){
    int* p = (int*)0x12345678;  // 只是给指针赋了一个值
    printf("p = %p\n", p);      // 不会报错, 因为还没有用这个地址进行访问
    *p = 1;     // [ERROR] Segmentation Fault (Core Dumped)
                // 段错误, 核心已转储

    const int i = 1;
    const static int j = 2;
    *(int*) &i = 2;     // const int i = 1;
                        // i 为 const int 型变量
                        // &i 为 const int * 型地址
                        // 将 const int * 型地址强转为 (int*)型地址
    *(int*) &j = 3;     // 段错误
    printf("i = %d\n", i);
    return 0;
}



