#include "../../include/getListener.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "../../include/socktoip.h"

#define PORT "9034"
int getListener(){
    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    int err = getaddrinfo(NULL, PORT, &hints, &ai);
    if (err != 0){
        fprintf(stderr, "Error Getting Address Info: %s\n", gai_strerror(err));
        exit(1);
    }
    int sockfd;
    int yes; //for socket options
    
    for (p = ai; p != NULL; p=p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd<0){
            continue;
        }
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) < 0){
            perror("Unable to bind to socket\n");
            close(sockfd);
            continue;
        }
        break;
    }
    if (p == NULL){
        fprintf(stderr, "Failed to bind to any of provided sockets");
        exit(1);
    }

    char buffer[INET6_ADDRSTRLEN];
    sockToIP(p->ai_addr, buffer, INET6_ADDRSTRLEN);

    //free address info as socket file descriptor is already bound
    freeaddrinfo(ai);

    if (listen(sockfd, 10) < 0){
        perror("Unable to listen on bound socket\n");
    }

    printf("Listening on %s port %s...\n", buffer, PORT);

    return sockfd;
}