/* 动态库的动态加载 */
#include <stdio.h>
#include <dlfcn.h>

int main(void){
    // 将动态库载入内存
    void* handle = dlopen("../shared_lib/libmath.so", RTLD_NOW);
    if(handle == NULL){
        // dlopen 失败
        // fprintf() -> 三个标准文件{stdin, stdout, stderr} 
        // printf() 实际上就是 stdout, 使用时输出的内容会经历缓冲区
        // 而对我们来说, 错误信息是很重要的信息, 我们希望其不经历缓冲区立刻被输出至屏幕
        // 忘记此部分内容需要参考 rebuildCpp Repo中的内容进行复习
        // stderr 是文件指针, 默认输出到显示器上
        fprintf(stderr, "dlopen: %s\n", dlerror());
        return -1;
    }

    // 获取库中函数的地址
    int (*add)(int, int) = dlsym(handle, "add");
    if(add == NULL){
        fprintf(stderr, "dlsym: %s\n", dlerror());
        return -1;
    }

    int (*sub)(int, int) = dlsym(handle, "sub");
    if(sub == NULL){
        fprintf(stderr, "dlsym: %s\n", dlerror());
        return -1;
    }

    void (*show)(int, char, int, int) = dlsym(handle, "show");
    if(add == NULL){
        fprintf(stderr, "dlsym: %s\n", dlerror());
        return -1;
    }



    // 使用函数

    // 卸载动态库

    return 0;
}

