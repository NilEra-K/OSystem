/* 错误处理 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>  // 错误处理头文件
#include <string.h>

int main(void){
    // malloc失败 --> 获得失败编号 --> 明白失败原因
    void* p = malloc(0xffffffffffffff); 
    if(p == NULL){  // malloc失败
        fprintf(stderr, "errno = %d\n", errno); // [ERROR] errno = 12 -> Cannot Allocate Memory // Out Of Memory
        fprintf(stderr, "malloc: %s\n", strerror(errno));
        perror("malloc");
        return -1;
    }
    free(p);
    return 0;
}