/* 从管道中读取数据 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    // 打开有名管道文件
    printf("%d 进程 : 打开有名管道文件\n", getpid());
    int fd = open("./fifo", O_RDONLY);
    if(fd == -1){
        perror("open");
        return -1;
    }

    // 读取有名管道文件
    printf("%d 进程 : 读取有名管道文件\n", getpid());
    for(;;){
        char buf[128] = {};
        ssize_t size  = read(fd, buf, sizeof(buf)-1);
        if(size == -1){
            perror("Read");
            return -1;
        }
        // 将读取到的数据显示
        printf("%s", buf);  // fgets 获取的时候已经获取了 '\n', 不需要额外输出 '\n'
        if(size == 0){  // read函数返回 0, 表示对方关闭了管道文件
            printf("%d 进程 : 对方关闭有名管道文件\n", getpid());
            break;
        }
    }

    // 关闭有名管道文件
    printf("%d 进程 : 关闭有名管道文件\n", getpid());
    close(fd);
    return 0;
}

