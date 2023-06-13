/* 变身的目标 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]){
    printf("PID: %d\n", getpid());
    printf("命令行参数内容: \n");
    for(char** pp = argv; *pp; pp++){
        // printf("pp 的内容: %p\n", pp);
        printf("%s\n", *pp);
    }
    
    printf("------------------------------\n");
    printf("环境变量名:\n");
    for(char** pp = envp; *pp; pp++){
        printf("%s\n", *pp);
    }
    printf("------------------------------\n");
    return 0;
}




