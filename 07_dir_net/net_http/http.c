/*  HTTP 协议 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

// 传输层上使用 TCP协议, 应用层使用 HTTP协议
int main(int argc, char* argv[]){
    // ./a.out www.baidu.com 110.242.68.3 /hello.html
    char* name = argv[1];
    char* ip = argv[2];
    char* path = argc < 4 ? "" : argv[3];

    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Socket");
        return -1;
    }

    // 组织服务器地址结构
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(80);
    ser.sin_addr.s_addr = inet_addr(ip);
    
    // 向服务器发起连接
    if(connect(sockfd, (struct sockaddr*)&ser, sizeof(ser)) == -1){
        perror("Connect");
        return -1;
    }
    
    // 组织 HTTP 请求
    char buf[1024] = {};
    // sprintf() 输出一个串到指定的存储区里
    // fprintf() 输出一个串到指定的文件里
    sprintf(buf, "GET /%s HTTP/1.1\r\n"
                 "Host: %s\r\n"
                 "Accept: */*\r\n"
                 "User-agent: Mozilla/5.0\r\n"
                 "Connection: close\r\n"
                 "Referer: %s\r\n\r\n", path, name, name);

    // 发送给服务器
    if(send(sockfd, buf, strlen(buf), 0) == -1){
        perror("Send");
        return -1;
    }
    
    // 接收服务器的响应
    for(;;){
        char respond[1024] = {};
        ssize_t size = recv(sockfd, respond, sizeof(respond) - 1, 0);
        if(size == -1){
            perror("Recv");
            return -1;
        }
        printf("%s", respond);
    }
    printf("\n");
    close(sockfd);
    return 0;
}



