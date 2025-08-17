#include "../../include/server.h"

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../include/socktoip.h"
#include "../../include/peerToPeer.h"
#include "../../include/getListener.h"
#include <arpa/inet.h>

void server(char* targetAddr){
    char addrbuffer[INET6_ADDRSTRLEN] = { 0 };

    if (strcmp(targetAddr, "") == 0){
        for (;;){
            int listener = getListener(addrbuffer);
            if (listener == -1){
                printf("Failed to obtain listener port\n");
                return;
            }
            printf("Listening on <%s>...\n", addrbuffer);
            //wait for connection to accept
            struct sockaddr_storage conn_addr;
            int connfd;
            socklen_t connaddrsize;
            
            connaddrsize = sizeof(conn_addr);
            memset(&conn_addr, 0, connaddrsize);
            connfd = accept(listener, (struct sockaddr *)&conn_addr, &connaddrsize);
            if (connfd == -1){
                perror("Error getting socket descriptor of connection");
                return;
            }
            char connbuffer[INET6_ADDRSTRLEN] = { 0 };
            sockToIP((struct sockaddr *)&conn_addr, connbuffer, INET6_ADDRSTRLEN);

            printf("Connected to: <%s>\n", connbuffer);
            close(listener);
            sleep(1);
            peerToPeer(connfd, connbuffer);
        }
    }

    else{
        struct addrinfo hints, *ai, *p;
        memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = AF_UNSPEC;
        hints.ai_flags = AI_CANONNAME;
        int err = getaddrinfo(targetAddr, "9043", &hints, &ai);
        if (err != 0){
            fprintf(stderr, "Error Getting Address Info: %s\n", gai_strerror(err));
            return;
        }


        for (;;){
            int listener = getListener(addrbuffer);
            if (listener == -1){
                printf("Failed to obtain listener port\n");
                return;
            }
            printf("Listening on <%s> for connection from <%s>...\n", addrbuffer, targetAddr);
            struct sockaddr_storage conn_addr;
            int connfd;
            socklen_t connaddrsize;
            connaddrsize = sizeof(conn_addr);
            char connbuffer[INET6_ADDRSTRLEN] = { 0 };
            for (;;){
                //wait for connection to accept
                memset(&conn_addr, 0, connaddrsize);
                connfd = accept(listener, (struct sockaddr *)&conn_addr, &connaddrsize);
                if (connfd == -1){
                    perror("Error getting socket descriptor of connection");
                    return;
                }
                memset(&connbuffer, 0, INET6_ADDRSTRLEN);
                sockToIP((struct sockaddr *)&conn_addr, connbuffer, INET6_ADDRSTRLEN);
                

                for (p = ai; p != NULL; p=p->ai_next){
                    char checkbuffer[INET6_ADDRSTRLEN] = { 0 };
                    sockToIP(p->ai_addr, checkbuffer, INET6_ADDRSTRLEN);
                    if (strcmp(checkbuffer, connbuffer) != 0){
                        //silently refuse connections
                        continue;
                    }
                    break;
                }
                if (p == NULL){   
                    close(connfd);
                    printf("Closed attempted connection from %s as it did not match target address\n", connbuffer);
                    continue;
                }
                break;
            }
            close(listener);
            printf("Connected to: <%s>\n", connbuffer);
            peerToPeer(connfd, connbuffer);
        }
    }
    return;
}