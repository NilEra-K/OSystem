/* 写入消息队列 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

int main(void){
    // 合成键
    printf("%d 进程 : 合成键\n", getpid());
    key_t key = ftok(".", 100);
    if(key == -1){
        perror("Ftok");
        return -1;
    }

    // 创建消息队列
    printf("%d 进程 : 创建消息队列\n", getpid());
    int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0664);
    if(msgid == -1){
        perror("Msgget");
        return -1;
    }

    // 发送消息
    printf("%d 进程 : 发送消息\n", getpid());
    for(;;){
        // 构建存储区
        struct {
            long type;
            char data[128];
        }msgbuf = {123, ""};

        // 通过键盘获取要发送的数据
        fgets(msgbuf.data, sizeof(msgbuf.data), stdin);
        if(strcmp(msgbuf.data, "!\n") == 0){
            break;
        }

        // 发送信息
        if(msgsnd(msgid, &msgbuf, strlen(msgbuf.data), 0) == -1){
            perror("Msgsnd");
            return -1;
        }
    }

    // 销毁消息队列
    printf("%d 进程 : 销毁消息队列\n", getpid());
    if(msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("Msgctl");
        return -1;
    }
    printf("FINISHED");
    return 0;
}


