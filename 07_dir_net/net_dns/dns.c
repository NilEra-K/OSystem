/* 域名解析 */
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
    // ./a.out www.baidu.com
    struct hostent* host = gethostbyname(argv[1]);
    if(host == NULL){
        perror("Gethostbyname");
        return -1;
    }
    printf("主机官方名: \n");
    printf("%s\n", host->h_name);
    printf("主机别名表: \n");
    for(char** pp = host->h_aliases; *pp; pp++){
        printf("*pp = %s\n", *pp);
    }
    printf("IP 地址表: \n");
    for(struct in_addr** pp = (struct in_addr**)host->h_addr_list; *pp; pp++){
        printf("%s\n", inet_ntoa(**pp));
    }
    return 0;
}


