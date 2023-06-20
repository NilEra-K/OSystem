/* 写入共享内存 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

int main(void){
    // 合成键
    printf("%d 进程 : 合成键\n", getpid());
    key_t key = ftok(".", 100);
    if(key == -1){
        perror("Ftok");
        return -1;
    }

    // 创建共享内存
    printf("%d 进程 : 创建共享内存\n", getpid());
    int shmid = shmget(key, 4096, IPC_CREAT | IPC_EXCL | 0664);
    if(shmid == -1){
        perror("Shmget");
        return -1;
    }

    // 加载共享内存
    printf("%d 进程 : 加载共享内存\n", getpid());
    void* start = shmat(shmid, NULL, 0);
    if(start == (void *) -1){
        perror("Shmat");
        return -1;
    }

    // 写入数据
    (char*)start;
    sprintf(start, "key = 0x%x, shmid = %d, pid = %d", key, shmid, getpid());

    // 卸载共享内存
    printf("%d 进程 : 卸载共享内存\n", getpid());
    if(shmdt(start) == -1){
        perror("Shmdt");
        return -1;
    }

    // 销毁共享内存
    getchar();
    printf("%d 进程 : 销毁共享内存\n", getpid());
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
        perror("Shmctl");
        return -1;
    }
    printf("%d 进程 : Finished\n", getpid());
    return 0;
}





