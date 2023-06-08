/* 创建子进程 */
#include <stdio.h>
#include <unistd.h>
// 简单理解一下: 调用fork函数之后, fork之后父进程有的子进程也有了
const int const_global = 1;     // 常全局变量
int main(void){
    printf("%d 进程: Father Process, Now Create Son Process...\n", getpid());
    pid_t a = fork();
    int x = 100;
    static int father_a = 20;
    static const int father_b = 40;    
    if(a == -1){
        perror("Fork");
        return -1;
    }
    if(a == 0) {
        printf("%d 进程: 调用子进程\n", getpid());
        printf("Global x = %d\n", x);
        int son_a = 10;
        printf("Global father_a = %d\n", father_a);
        printf("Global father_b = %d\n", father_b);
        printf("Const Global = %d\n", const_global);
        return 0;
    } else {
        printf("%d 进程: 调用父进程\n", getpid());
        // printf("Son_Data: son_a = %d", son_a);  // son_a无法使用, 未定义的标识符
    }
    printf("%d 进程: Hello World!\n", getpid());
    // 思考: 下面的代码会生成多少子进程 （8个）
    // for(int i = 0; i < 3; i++){
    //     fork();
    // }
    //      for   for   for
    //       v     v     v
    // -- A -+- A -+- A -+- A
    //       |     |     |
    //       |     |     +- B
    //       |     |     
    //       |     +- B -+- B
    //       |           |
    //       |           +- C 
    //       |
    //       +- B -+- B -+- B
    //             |     |
    //             |     +- C
    //             |     
    //             +- C -+- C
    //                   |
    //                   +- D
    return 0;
}

