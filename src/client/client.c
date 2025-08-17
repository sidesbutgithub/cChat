#include "../../include/client.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/socktoip.h"
#include "../../include/getRemote.h"
#include <poll.h>

void client(){
    int remote = getRemote();
    printf("Waiting for connections\n");

    //poll stdin(0) and connected socket
    struct pollfd pfds[2];
    pfds[0].fd = 0; //stdin
    pfds[0].events = POLLIN;

    pfds[1].fd = remote; //remote socket
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
            send(remote, serverbuffer, bytesread, 0);
        }
        if (pfds[1].revents & POLLHUP){
            printf("client hung up\n");
            break;
        }
        if (pfds[1].revents & POLLIN){
            char clientbuffer[256] = {0};
            recv(remote, clientbuffer, 256, 0);
            printf("%s", clientbuffer);
        }
    }
    return;
}