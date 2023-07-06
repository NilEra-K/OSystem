/* 基于 UDP协议的服务器端 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(void){
    // 创建套接字
    printf("服务器: 创建套接字\n");
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }

    // 组织地址结构
    printf("服务器: 组织地址结构\n");
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(9999);
    ser.sin_addr.s_addr = INADDR_ANY;

    // 绑定套接字和地址结构
    printf("服务器: 绑定套接字和地址结构\n");
    if(bind(sockfd, (struct sockaddr*)&ser, sizeof(ser)) == -1){
        perror("Bind");
        return -1;
    }

    // 业务处理
    printf("服务器: 业务处理\n");
    for(;;){
        // 接收数据
        char buf[128] = {};
        struct sockaddr_in cli;         // 用于输出客户端的地址结构
        socklen_t len = sizeof(cli);    // 用于输出客户端地址结构的大小
        ssize_t size = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&cli, &len);
        if(size == -1){
            perror("Recvfrom");
            return -1;
        }
        // 将小写字母转化为大写字母
        for(int i = 0; buf[i]; i++){
            buf[i] = toupper(buf[i]);
        }
        // 发送数据
        if(sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&cli, sizeof(cli)) == -1){
            perror("sendto");
            return -1;
        }
    }

    // 关闭套接字
    printf("服务器: 发送数据\n");
    close(sockfd);
    return 0;
}



