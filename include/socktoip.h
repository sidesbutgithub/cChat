#ifndef SOCKTOIP_H
#define SOCKTOIP_H
#include <sys/socket.h>
#include <stddef.h>
const char* sockToIP(struct sockaddr* sock, char* buffer, size_t bufferSize);
#endif