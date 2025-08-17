/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>
#include "include/socktoip.h"
*/
#include "../include/server.h"
#include "../include/client.h"
#include <string.h>

int main(int argc, char *argv[]){
    if (strcmp(argv[1], "server") == 0){
        server();
    }
    else if (strcmp(argv[1], "client") == 0){
        client();
    }
    /*
    printf("Enter Address You Would Like to Message(Leave Blank to Remain Open to Listen for Connections to Decide if You Want to Connect):\n");
    //accomodate enough space for IPv6 > IPv4
    
    char peerIP[INET6_ADDRSTRLEN];
    scanf("%s", peerIP);
    printf("%ld\n", strlen(peerIP));
    */
    /*
    if (strlen(peerIP) == 0){
        printf("No Target IP Specified\n");
    }
    else{
        printf("%s\n", peerIP);
    }*/
/*
    struct addrinfo hints, *ai, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    //AI_PASSIVE to use current host ip, need to figure out how to get accurate host ip though, AI_CANONNAME
    hints.ai_flags = AI_PASSIVE;

    int err = getaddrinfo(NULL, PORT, &hints, &ai);

    if (err != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(1);
    }
    printf("%s", hints.ai_canonname);
    
    int sockfd;
    int yes = 1; //need this to set socket options to reuse address
    int availableAddresses = 0;

    for (p = ai; p != NULL; p = p->ai_next) {
        availableAddresses++;
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        printf("%d\n", sockfd);
        if (sockfd < 0){
            continue;
        }

        char ipaddr[p->ai_addrlen];

        sockToIP(p->ai_addr, ipaddr, p->ai_addrlen);
        printf("attempting to bind to: %s\n", ipaddr);

        // Lose the pesky "address already in use" error message (yes this is straight from a guide)
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        
        //attempt to bind to current address, if we cant we close the provided socket desc (because everything is a file in unix)
        
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) < 0){
            perror("");
            close(sockfd);
            continue;
        }
        
        break;

    }

    if (p == NULL){
        fprintf(stderr, "failed to bind to any of %d available addresses\n", availableAddresses);
        exit(1);
    }

    char ipaddr[p->ai_addrlen];

    printf("%s\n", p->ai_addr->sa_data);

    sockToIP(p->ai_addr, ipaddr, p->ai_addrlen);
    //inet_ntop(p->ai_addr->sa_family, p->ai_addr, ipaddr, p->ai_addrlen);

    printf("bound to: %s\n", ipaddr);

    //free the provided address info as we only need the socket descriptor which is already bound
    freeaddrinfo(ai);

    
    if (listen(sockfd, 10) == -1){
        perror("failed to listen on bound socket\n");
    }

    printf("socket desciptor: %d\n", sockfd);
    return sockfd;

    
}*/
}