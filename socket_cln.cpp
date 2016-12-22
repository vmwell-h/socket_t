/*******************************************************************************
    \file          socket_cln.cpp
    \author        huanghai
    \mail          huanghai@auto-link.com
    \version       0.13
    \date          2016-06-27
------------------------------------------------------------------------------\n*/

/*******************************************************************************
    Include Files
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(){

    char filename[100] = "recv.mp3";  //文件名
    FILE *fp;
    if((fp = fopen(filename, "wb")) == NULL) {
        printf("Cannot open file, press any key to exit!\n");
        exit(0);
    }

    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //循环接收数据，直到文件传输完毕
    char buffer[BUF_SIZE] = {0};  //文件缓冲区
    int nrecv;
    while( (nrecv = recv(sock, buffer, BUF_SIZE, 0)) > 0 ){
        fwrite(buffer, nrecv, 1, fp);
    }

    //文件接收完毕后直接关闭套接字，无需调用shutdown()
    fclose(fp);
    //关闭套接字
    close(sock);
    return 0;
}