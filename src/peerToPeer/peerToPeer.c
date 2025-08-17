#include "../../include/peerToPeer.h"

#include <poll.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void peerToPeer(int sockfd, char* sender){
    //poll stdin(0) and connected socket
    struct pollfd pfds[2];
    pfds[0].fd = 0; //stdin
    pfds[0].events = POLLIN;
    pfds[0].revents = 0;

    pfds[1].fd = sockfd; //connected socket
    pfds[1].events = POLLIN;
    pfds[1].revents = 0;

    int numevents;

    for (;;){
        numevents = poll(pfds, 2, -1);
        if (numevents == 0){
            perror("No events polled\n");
        }
        if (pfds[1].revents & (POLLIN | POLLHUP)){
            char* remoteBuffer = calloc(256, sizeof(char));
            int bytesrecv = recv(sockfd, remoteBuffer, 255, 0);
            
            if (bytesrecv == 0){
                printf("<%s> Hung Up\n", sender);
                close(sockfd);
                free(remoteBuffer);
                return;
            }

            remoteBuffer[strlen(remoteBuffer)] = '\0';
            printf("<%s>: %s", sender, remoteBuffer);
            free(remoteBuffer);
        }
        if (pfds[0].revents & POLLIN){
            char* stdinBuffer = malloc(256*sizeof(char));
            int bytesread = read(0, stdinBuffer, 255);
            stdinBuffer[strlen(stdinBuffer)] = '\0';
            send(sockfd, stdinBuffer, bytesread, 0);
            free(stdinBuffer);
        }
    }
    return;
}
