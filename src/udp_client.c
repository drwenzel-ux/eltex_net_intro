#include <alloca.h>
#include <stdio.h>

#include "inet_socket.h"

int main(int argc, char const *argv[]) {
  int fd;
  char buffer[] = "hello from client!";

  fd = inet_connect("127.0.0.1", 7777, SOCK_DGRAM);
  send(fd, buffer, sizeof(buffer), 0);

  recv(fd, buffer, sizeof(buffer), 0);
  printf("from server: %s\n", buffer);

  close(fd);
  return 0;
}