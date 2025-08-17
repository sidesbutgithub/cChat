#include "../../include/socktoip.h"
#include <sys/types.h>
#include <stddef.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

//get ip address from socket address
const char* sockToIP(struct sockaddr* sock, char* buffer, size_t bufferSize){
    switch (sock->sa_family){
        case AF_INET:
            return inet_ntop(AF_INET, &(((struct sockaddr_in *)sock)->sin_addr), buffer, bufferSize);
        case AF_INET6:
            return inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sock)->sin6_addr), buffer, bufferSize);
        default:
            return NULL;
    }
}
