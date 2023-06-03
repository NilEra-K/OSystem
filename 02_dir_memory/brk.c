#include <stdio.h>
#include <unistd.h>

int main(void){
    printf("当前堆尾: %p\n", sbrk(0));

    int* p1 = sbrk(0);
    brk(p1 + 1);    // 分配四个字节, 因为 p1是 int型指针
    printf("p1 = %p\n", p1);
    *p1 = 123;

    double * p2 = sbrk(0);
    brk(p2 + 1);
    printf("p2 = %p\n", p2);
    *p2 = 4.56;

    printf("%d %lg\n", *p1, *p2);
    brk(p1);
    printf("当前堆尾: %p\n", sbrk(0));
    return 0;
}
