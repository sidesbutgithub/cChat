#include "../../include/getRemote.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "../../include/socktoip.h"

#define PORT "9034"

int getRemote(char* targetaddr, char* addrbuffer){

    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    int err;
    if (strcmp(targetaddr, "localhost") == 0){
        hints.ai_flags = AI_PASSIVE;
        err = getaddrinfo(NULL, PORT, &hints, &ai);
    }
    else{
        hints.ai_flags = AI_CANONNAME;
        err = getaddrinfo(targetaddr, PORT, &hints, &ai);
    }

    if (err != 0){
        fprintf(stderr, "Error Getting Address Info: %s\n", gai_strerror(err));
        return -1;
    }

    int sockfd;

    int yes = 1; //for socket options

    for (p = ai; p != NULL; p=p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd<0){
            continue;
        }
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) < 0){
            perror("Unable to connect to socket\n");
            close(sockfd);
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "Client: failed to connect\n");
        return -1;
    }

    sockToIP(p->ai_addr, addrbuffer, sizeof(addrbuffer));
    printf("Connected to: <%s>\n", addrbuffer);

    freeaddrinfo(ai);

    return sockfd;
}