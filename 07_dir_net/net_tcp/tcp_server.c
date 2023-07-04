/* 基于 TCP 通信的服务器 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>          // 使用 toupper 函数需要包含该头文件
#include <sys/types.h>      // 基本上网络通信部分的代码都需要包含以下三个头文件
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void){
    // 创建套接字
    // int socket(int domain, int type, int protocol);
    // 表示 IPv4网络 TCP协议 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Socket");
        return -1;
    }

    // 准备地址结构
    

    return 0;
}




