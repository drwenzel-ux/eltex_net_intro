#ifndef __UNIX_SOCKET_H__
#define __UNIX_SOCKET_H__

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "socket.h"

#define FAMILY AF_UNIX

#define SOCKET_NAME "/tmp/9Lq7BNBnBycd6nxy.socket"
#define BUFFER_SIZE 12

int unix_connect(int type);
int unix_bind(int type);
int unix_listen(int type, int backlog);

#endif