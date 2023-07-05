// 基于 TCP协议的客户端
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(void){
    // 创建套接字
    printf("客户端: 创建套接字\n");
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Socket");
        return -1;
    }

    // 准备地址结构, 需要准备客户端要连接的服务器的地址结构
    // 服务器端的端口号是需要固定的, 方便客户机找到服务器程序
    // 客户机端的端口号是无需固定的, TCP协议会随机分配可用程序
    printf("客户端: 组织服务器的地址结构\n");
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(8888);
    ser.sin_addr.s_addr = inet_addr("192.168.226.128");

    // 向服务器发送连接请求
    // 调用 connect()函数 -> 即开始三次握手
    printf("客户端: 发起连接\n");
    if(connect(sockfd, (struct sockaddr*)&ser, sizeof(ser)) == -1){
        perror("Connect");
        return -1;
    }

    // 业务处理
    printf("客户端: 业务处理\n");
    for(;;){
        // 通过键盘获取小写的串
        char buf[128] = {};
        fgets(buf, sizeof(buf), stdin);
        // 输入 ! 退出循环
        if(strcmp(buf, "!\n") == 0){
            break;
        }
        // 发送给服务器
        if(send(sockfd, buf, strlen(buf), 0) == -1){
            perror("Send");
            return -1;
        }
        // 接收服务器回传的数据
        ssize_t size = recv(sockfd, buf, sizeof(buf)-1, 0);
        // printf("size = %ld\n", size);
        if(size == -1){
            perror("Recv");
            return -1;
        }
        // 显示服务器回传的数据
        // printf("收到消息\n");
        printf("%s", buf);
    }
    // 关闭套接字
    printf("客户端: 关闭套接字\n");
    close(sockfd);
    return 0;
}
