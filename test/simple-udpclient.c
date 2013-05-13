#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>


/*********************************************************************
*filename: simple-udpclient.c
*purpose: 基本编程步骤说明，演示了UDP编程的客户端编程步骤

*********************************************************************/

int main(int argc, char **argv)
{
    struct sockaddr_in s_addr;
    int sock;
    int addr_len;
    int len;
    char buff[128];

    /*创建socket，关键在于这个SOCK_DGRAM*/
    if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
    {
        perror("socket");
        exit(errno);
    }
    else
        printf("create socket\n\t");

    /*设置对方地址和端口信息*/
    s_addr.sin_family=AF_INET;
    if(argv[2])
        s_addr.sin_port=htons(atoi(argv[2]));
    else
        s_addr.sin_port=htons(7838);

    if(argv[1])
        s_addr.sin_addr.s_addr=inet_addr(argv[1]);
    else
    {
        printf("message must have one receiver\n");
        exit(0);
    }

    /*发送UDP消息*/
    addr_len=sizeof(s_addr);
	while(1){
    strcpy(buff,"hello i'm here");
    len=sendto(sock,buff,strlen(buff),0,(struct sockaddr *)&s_addr,addr_len);
    if(len<0)
    {
        printf("\n\rsend error\n\r");
        return 3;
    }
    printf("send success\n\r");
	usleep(1*1000*1000);
		}
    return 0;
}
