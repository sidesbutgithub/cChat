#include "../../include/server.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/socktoip.h"
#include "../../include/getListener.h"
#include <poll.h>

void server(){
    int listener = getListener();
    printf("Waiting for connections\n");

    //wait for connection to accept
    struct sockaddr_storage conn_addr;
    int connfd;
    socklen_t connaddrsize;

    connaddrsize = sizeof(conn_addr);

    connfd = accept(listener, (struct sockaddr *)&conn_addr, &connaddrsize);
    if (connfd == -1){
        perror("Error getting socket descriptor of connection");
        exit(1);
    }

    char buffer[256];
    int buffSize = sizeof(buffer);
    sockToIP((struct sockaddr *)&conn_addr, buffer, buffSize);
    printf("Connected to: %s\n", buffer);

    //poll stdin(0) and connected socket
    struct pollfd pfds[2];
    pfds[0].fd = 0; //stdin
    pfds[0].events = POLLIN;

    pfds[1].fd = connfd; //connected socket
    pfds[1].events = POLLIN;
    pfds[1].revents = 0;

    int numevents;

    for (;;){
        numevents = poll(pfds, 2, -1);
        if (numevents == 0){
            perror("No events polled\n");
        }
        if (pfds[0].revents & POLLIN){
            char serverbuffer[256] = {0};
            int bytesread = read(0, serverbuffer, 255);
            send(connfd, serverbuffer, bytesread, 0);
        }
        if (pfds[1].revents & POLLHUP){
            printf("client hung up\n");
            break;
        }
        if (pfds[1].revents & POLLIN){
            char clientbuffer[256] = {0};
            recv(connfd, clientbuffer, 256, 0);
            printf("%s", clientbuffer);
        }
    }
}