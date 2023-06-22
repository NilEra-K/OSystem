/* 读取消息队列 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/msg.h>

int main(void){
    // 合成键
    printf("%d 进程 : 合成键\n", getpid());
    key_t key = ftok(".", 100);
    if(key == -1){
        perror("Ftok");
        return -1;
    }

    // 获取消息队列
    printf("%d 进程 : 获取消息队列\n", getpid());
    int msgid = msgget(key, 0);
    if(msgid == -1){
        perror("Msgget");
        return -1;
    }

    // 接收数据
    for(;;){
        // 构建存储区
        struct {
            long type;
            char data[128];
        }msgbuf = {};

        // 接收数据
        //                                                    接收 123类型数据
        //                                                           v
        size_t size = msgrcv(msgid, &msgbuf, sizeof(msgbuf.data)-1, 123, /*0*/IPC_NOWAIT);
        if(size == -1){
            if(errno == EIDRM){
                printf("%d 进程 : 对方销毁消息队列\n", getpid());
                break;
            } else if (errno == ENOMSG){
                printf("%d 进程 : 暂时没有消息, 一会再来\n", getpid());
                sleep(1);
            } else {
                perror("Msgrcv");
                return -1;
            }
        } else {
            // 显示数据
            printf("%ld > %s", msgbuf.type, msgbuf.data);
        }
    }
    printf("FINISHED");
    return 0;
}

