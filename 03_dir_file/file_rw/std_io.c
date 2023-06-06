/* 系统I/O 和 标准I/O */
// 同样读写 1,000,000 次相同的内容, 系统I/O更快还是 标准I/O 更快?
// 标准I/O 更快
// 使用 `time ./std_io` 可以查看该文件的执行时间
/* 运行结果 */
// real    0m0.173s
// user    0m0.076s
// sys     0m0.096s
#include <stdio.h>
int main(void){
    FILE* fp = fopen("./stdio.txt", "w");
    if(fp == NULL){
        perror("fopen");
        return -1;
    }
    for(int i = 0; i< 1000000; i++){
        fwrite(&i, sizeof(i), 1, fp);
    }
    fclose(fp);
    return 0;
}

