/*******************************************************************************
    \file          socket_ser.cpp
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
#include <netinet/in.h>


#define BUF_SIZE 1024

int main(){

    char *filename = "Jar of Love.mp3";
    FILE *fp;

    if ((fp = fopen (filename, "rb")) == NULL)
      printf ("can't open file %s.\n",filename);

    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);
    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    //向客户端发送数据
    char buffer[BUF_SIZE] = {0};
    int nread;
    while( (nread = fread(buffer, 1, BUF_SIZE, fp)) > 0 ){
        send(clnt_sock, buffer, nread, 0);
    }

    shutdown(clnt_sock, SHUT_WR);  //文件读取完毕，断开输出流，向客户端发送FIN包
    recv(clnt_sock, buffer, BUF_SIZE, 0);  //阻塞，等待客户端接收完毕
    fclose(fp);
    
    //关闭套接字
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
