#if 0
/* 环境变量 */
// 通过全局环境变量表指针 environ可以访问所有的环境变量
#include <stdio.h>
// main函数 更完整的形式
// int main(int argc, char* argv[], char* envp[]){...}
int main(void){
    //            +=====+
    // environ -> |  *  | -> PATH=/bin:/usr/bin:/usr/local/bin:.
    //            +=====+
    //            |  *  | -> LIBRARY_PATH=.
    //            +=====+
    //            |  *  | -> LD_LIBRARY_PATH=/usr/locaal/lib:.
    //            +=====+
    //            |  *  | -> SHELL=/bin/bash
    //            +=====+  
    extern char** environ;  // 该变量在开始时就存在与某一个库文件中
    char** pp;
    for(char** pp = environ; *pp; pp++){
        // 当使用 **p 时, 获得一个数字, 即 PATH字符串第一个字符的 ASCII码
        // printf("%d\n", **pp);
        printf("%d\n", *pp);
    }
    return 0;
}
#endif

#if 1
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[], char* envp[]){
    extern char** environ;
    // for(char** pp = environ; *pp; pp++){
    //     // 当使用 **p 时, 获得一个数字, 即 PATH字符串第一个字符的 ASCII码
    //     // printf("%d\n", **pp);
    //     printf("%d\n", *pp);
    // }
    // 可以发现二者的首地址是一样的
    printf("environ: %p\n", environ);   // [Out]: 0x7ffea9362818
    printf("envp: %p\n", envp);         // [Out]: 0x7ffea9362818
    for(char** pp = envp; *pp; pp++){
        printf("%s\n", *pp);
    }
    return 0;
}
#endif
