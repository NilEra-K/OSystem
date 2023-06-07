/* 访问测试 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    // ./a.out 文件名
    // 若文件不存在, 输出文件名不存在
    // 若文件存在, 输出文件名是否可读可写可执行
    if(argc < 2){
        fprintf(stderr, "用法: ./a.out <文件名>\n");
        return -1;
    }
    printf("文件: %s", argv[1]);

    if(access(argv[1], F_OK) == -1){
        printf("文件名不存在\n");
    } else {
        if(access(argv[1], F_OK) == -1){
            printf("不可读, ");
        } else {
            printf("可读, ");
        }
        
        if(access(argv[1], W_OK) == -1){
            printf("不可写, ");
        } else {
            printf("可写, ");
        }

        if(access(argv[1], X_OK) == -1){
            printf("不可执行, \n");
        } else {
            printf("可执行, \n");
        }
    }
    return 0;
}

