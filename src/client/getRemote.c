#include "../../include/getRemote.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "../../include/socktoip.h"

#define PORT "9034"

int getRemote(){
    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    //change later for targeting
    hints.ai_flags = AI_PASSIVE;

    int err = getaddrinfo(NULL, PORT, &hints, &ai);
    if (err != 0){
        fprintf(stderr, "Error Getting Address Info: %s\n", gai_strerror(err));
        exit(1);
    }

    int sockfd;

    char buffer[256];
    int yes = 1; //for socket options

    for (p = ai; p != NULL; p=p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd<0){
            continue;
        }

        sockToIP(p->ai_addr, buffer, sizeof(buffer));
        printf("attempting connection to %s\n", buffer);

        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) < 0){
            perror("Unable to connect to socket\n");
            close(sockfd);
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 1;
    }
    sockToIP(p->ai_addr, buffer, sizeof(buffer));
    printf("connected to %s\n", buffer);

    freeaddrinfo(ai);

    return sockfd;
}