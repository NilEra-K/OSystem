// 运行结果
// real    0m3.046s
// user    0m0.468s
// sys     0m2.578s
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    int fd = open("./sysio.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("Open");
        return -1;
    }
    for(int i = 0; i < 1000000; i++){
        write(fd, &i, sizeof(i));
    }
    close(fd);
    return 0;
}