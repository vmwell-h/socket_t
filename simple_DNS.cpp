/*******************************************************************************
    \file          simpleDNS.cpp
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

#include <netdb.h>

/**
 * main - get ip address for the given domain
 *
 * @argc:
 * @argv:
 *
 * returns:
 * 
 */
int main(int argc,char * argv[])
{

    char domain[1024];
    int arg_flg = 0;
    for (int i=0; i<argc; i++)
    {
        printf("Argument %d is %s.\n",i,argv[i]);
        if (strcmp(argv[i],"-a") == 0)
        {
            strcpy(domain,argv[i+1]);
            printf("the domain is %s\n",domain);
            arg_flg = 1;
            break;
        }
    }
    
    if (arg_flg == 0)
        strcpy(domain,"www.baidu.com");
    struct hostent *host;
    if(!(host = gethostbyname(domain))) {
      printf("Get IP address error!.\n");
      exit(0);
    }
    //别名
    for(int i=0; host->h_aliases[i]; i++)
      printf("Aliases %d: %s\n", i+1, host->h_aliases[i]);
    //地址类型
    printf("Address type: %s\n", (host->h_addrtype==AF_INET) ? "AF_INET": "AF_INET6");
    //IP地址
    for(int i=0; host->h_addr_list[i]; i++)
      printf("IP addr %d: %s\n", i+1, inet_ntoa( *(struct in_addr*)host->h_addr_list[i] ) );

}