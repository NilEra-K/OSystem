/* 基于 TCP 通信的服务器 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>          // 使用 toupper 函数需要包含该头文件
#include <signal.h>         // 使用信号处理函数
#include <errno.h>
#include <wait.h>
#include <sys/types.h>      // 基本上网络通信部分的代码都需要包含以下三个头文件
#include <sys/socket.h>
#include <arpa/inet.h>

void sigfun(int signum){
    for(;;){
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if(pid == -1){
            if(errno == ECHILD){
                printf("服务器: 没有子进程了\n");
                break;
            }else{
                perror("Waitpid");
                return;
            }
        }else if(pid == 0){
            printf("服务器: 子进程在运行\n");
            return;
        }else{
            printf("服务器: 回收了 %d 进程的僵尸\n", pid);
        }

    }
}

int main(void){
    // 对 17号信号进行信号捕获处理
    if(signal(SIGCHLD, sigfun) == SIG_ERR){
        perror("Signal");
        return -1;
    }
    // 创建套接字
    // int socket(int domain, int type, int protocol);
    // 表示 IPv4网络 TCP协议 
    // 此处的套接字又被称之为 侦听套接字 -> 在调用完 listen 后变为侦听套接字
    printf("服务器: 创建套接字\n");
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Socket");
        return -1;
    }

    // 准备地址结构
    printf("服务器: 准备地址结构\n");
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;   // 基于 IPv4通信
    ser.sin_port = htons(8888); // 端口号, 需要注意字节序转换
    // ser.sin_addr.s_addr = inet_addr("192.168.226.128"); // IP地址: 点分十进制串转化为整数形式地址 
    // ser.sin_addr.s_addr = inet_addr("127.0.0.1");       // 本机 IP地址
    ser.sin_addr.s_addr = INADDR_ANY;   // 可以使用 INADDR_ANY宏表示 *可以接收任何 IP地址传来的信息*

    // 绑定套接字和地址结构
    // bind(int sockfd, struct sockaddr const* addr, socklen_t addrlen);
    printf("服务器: 绑定套接字和地址结构\n");
    if(bind(sockfd, (struct sockaddr*)&ser, sizeof(ser)) == -1){
        perror("Bind");
        return -1;
    }

    // 启动侦听, 由主动套接字变为被动套接字, 感受客户端的连接请求
    if(listen(sockfd, 1024) == -1){
        perror("Listen");
        return -1;
    }

    // 等待并接收连接请求
    for(;;){
        printf("服务器: 等待并接收连接请求\n");
        struct sockaddr_in cli;         // 用来输出客户端的地址结构
        socklen_t len = sizeof(cli);    // 用来输出客户端地址结构大小
        // accept()函数 返回一个套接字用于通信, 这个套接字又被称为通信套接字
        int conn = accept(sockfd, (struct sockaddr*)&cli, &len);
        if(conn == -1){
            perror("Accept");
            return -1;
        }
        // OUTPUT:
        // inet_ntoa() 是将网络字节序形式整数地址 转 点分十进制字符串地址
        // 前面端口号使用了 htons()
        // 这里端口号需使用 ntohs()
        printf("服务器: 接收到 %s > %hu 的客户端\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        // 创建子进程, 子进程负责和客户端通信
        pid_t pid = fork();
        if(pid == -1){
            perror("Fork");
            return -1;
        }

        if(pid == 0){       // 子进程: 负责通信部分
            close(sockfd);  // 子进程不需要侦听套接字, 关闭侦听套接字
            // 业务处理
            // 假设该服务器的业务是将小写字母转为大写字母
            // 此处的数据不需要进行转换
            // 因为 TCP充当一个快递员的角色, 它需要知道一个包裹的门牌号和手机号, 但是并不需要关心运输的是什么东西
            printf("服务器: 业务处理\n");
            for(;;){
                // 接收客户端的小写字符串
                char buf[128] = {};
                ssize_t size = read(conn, buf, sizeof(buf) - 1);
                if(size == -1){
                    perror("Read");
                    return -1;
                }
                // 当一方关闭文件, 此时 read无法读取数据, 返回 0
                if(size == 0){
                    printf("服务器: 客户端关闭套接字\n");
                    break;
                }
                // 将小写的字符转化为大写的字符
                for(int i = 0; i < strlen(buf); i++){
                    buf[i] = toupper(buf[i]);   // ctype.h
                }
                // 将大写的字符串回传给客户端
                if(write(conn, buf, strlen(buf)) == -1){
                    perror("Write");
                    return -1;
                }
            }
            // 子进程通信结束, 关闭通信套接字
            close(conn);
            return 0;
        }
        // 父进程关闭通信套接字, 进入下次循环, 等待新的客户端连接
        printf("服务器: 父进程关闭套接字\n");
        close(conn);
    }
    close(sockfd);
    return 0;
}
