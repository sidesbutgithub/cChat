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
#include <stdio.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Starting as server listening for any connections...\n");
        server("");
    }
    else{
        if (client(argv[1])==-1){
            printf("Unable to connect to <%d>, starting as server listening for connection from <%d>...\n", argv[1], argv[1]);
            server(argv[1]);
        }
    }
    return 0;
}