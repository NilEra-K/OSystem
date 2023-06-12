/* exit 函数 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* atexit 退出处理函数 */
void doit(void){
    printf("我是退出处理函数\n");
}

/* to_exit 退出处理函数 */
void doit_(int status, void* arg){
    // status参数由操作系统自动赋予, 其值与 exit(status)中的 status相同
    printf("status = %d\n", status);
    printf("arg = %s\n", (char*)arg);
}

int fun(void){
    printf("调用fun函数\n");
    // exit(0);
    _exit(0);
    return 10;
}

int main(void){
    // 注册退出处理函数
    atexit(doit);
    // 注册退出处理函数
    on_exit(doit_, "hello");

    int ret = fun();
    printf("fun函数返回: %d", ret);
    return 0;
}

