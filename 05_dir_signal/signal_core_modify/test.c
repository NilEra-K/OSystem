/* 段错误演示 */
// ulimit -c 1024
// 核文件需要使用 GDB查看 - gdb corefile core
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int* p = NULL;
    *p = 10;
    return 0;
}


