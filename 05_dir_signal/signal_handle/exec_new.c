/* exec创建新进程的对象 */
#include <stdio.h>
#include <unistd.h>

int main(void){
    printf("PID: %d\n", getpid());
    for(;;);
    return 0;
}

