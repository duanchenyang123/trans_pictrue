/*************************************************************************
	> File Name: tcp_clinet.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月28日 星期六 17时54分06秒
 ************************************************************************/
#include "head.h"
#include "common.h"
int socket_connect(char *host, int port) {
	int sockfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);
    

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    printf("socket creat\n");
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("connect\n");
        perror("connect");
        return -1;
    }
        printf("connect succeed\n");
	return sockfd; 

}

int socket_connect_timeout(char *host, int port, long timeout) {
	int sockfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);
    

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    make_nonblock(sockfd);
    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = timeout;
    
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(sockfd, &wfds);

    printf("socket creat\n");
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) { //会在这里阻塞
        int retval, error = -1;
        int len = sizeof(int);
        retval = select(sockfd + 1, NULL, &wfds, NULL, &tv);
        if (retval < 0) {
            close(sockfd);
           return -1;                                                                
        } else if(retval) {
            if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error,(socklen_t *)&len) < 0) {
                close(sockfd);
                return -1;
            }
            if(error) {
                close(sockfd);
                return -1;
            }
        }else {
            printf("Connection Timeout\n");
            close(sockfd);
            return -1;
        }
    }

	make_block(sockfd);
    return sockfd; 

}
