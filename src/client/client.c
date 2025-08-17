#include "../../include/client.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/socktoip.h"
#include "../../include/getRemote.h"
#include "../../include/peerToPeer.h"
#include <poll.h>
#include <arpa/inet.h>

int client(char* targetAddr){
    char addrbuffer[INET6_ADDRSTRLEN] = { 0 };
    int remote = getRemote(targetAddr, addrbuffer);
    if (remote == -1){
        printf("Failed to obtain connection port\n");
        return -1;
    }
    peerToPeer(remote, addrbuffer);
    return 0;
}