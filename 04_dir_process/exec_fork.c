/* fork + exec */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    // 创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return -1;
    }

    // 子进程代码
    if(pid == 0){
        if(execl("./exec_new", "new", "hello", NULL) == -1){
            perror("execl");
            return -1;
        }
        // return 0;
    }

    // 父进程代码
    int s = 0;
    if(waitpid(pid, &s, 0) == -1){
        perror("Waitpid");
        return -1;
    }
    if(WIFEXITED(s)){
        printf("正常终止 : %d\n", WEXITSTATUS(s));
    } else {
        printf("异常终止 : %d\n", WTERMSIG(s));
    }
}



