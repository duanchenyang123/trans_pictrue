/*************************************************************************
	> File Name: tcp_clinet.h
	> Author: 
	> Mail: 
	> Created Time: 2020年03月28日 星期六 17时52分40秒
 ************************************************************************/

#ifndef _TCP_CLINET_H
#define _TCP_CLINET_H
int socket_connect(char *host, int port);
int socket_connect_timeout(char *host, int port, long timeout);
#endif
