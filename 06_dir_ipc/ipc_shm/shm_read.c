/* 读取共享内存 */
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

int main(){
    // 合成键 路径和整数保证与写进程一致
    printf("%d 进程 : 合成键\n", getpid());
    key_t key = ftok(".", 100);
    if(key == -1){
        perror("Ftok");
        return -1;
    }

    // 获取共享内存
    printf("%d 进程 : 获取共享内存\n", getpid());
    // 获取的时候可以不指定大小
    int shmid = shmget(key, 0, 0);
    if(shmid == -1){
        perror("Shmget");
        return -1;
    }

    // 加载共享内存
    printf("%d 进程 : 加载共享内存\n", getpid());
    void* start = shmat(shmid, NULL, 0);
    if(start == (void*) -1){
        perror("Shmat");
        return -1;
    }

    // 读取共享内存
    printf("%d 进程 : 读取内存数据\n", getpid());
    getchar();
    printf("%s\n", (char *)start);

    // 卸载共享内存
    printf("%d 进程 : 卸载内存数据\n", getpid());
    getchar();
    if(shmdt(start) == -1){
        perror("Shmdt");
        return -1;
    }
    
    printf("FINISHED\n");
    return 0;
}


