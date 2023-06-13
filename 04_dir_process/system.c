/* System 函数 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
    int s = system("./exec_new hello 123");
    if(WIFEXITED(s)){
        printf("正常结束 : %d\n", WEXITSTATUS(s));
    }else{
        printf("异常终止 : %d\n", WTERMSIG(s));
    }

    s = system("ls -l --color=auto");
    if(WIFEXITED(s)){
        printf("正常结束 : %d\n", WEXITSTATUS(s));
    }else{
        printf("异常终止 : %d\n", WTERMSIG(s));
    }
    
    return 0;
}


