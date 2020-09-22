#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inet_socket.h"

#define N 20

int main(int argc, char const *argv[]) {
  int fd, iter;
  char *buffer;
  struct sockaddr_in sa;
  socklen_t s;

  if (argc < 2) {
    fprintf(stderr, "usage: ./server <iter>\n");
    exit(1);
  }

  iter = atoi(argv[1]);
  srand(time(0));
  fd = inet_bind("127.0.0.1", 7777, SOCK_DGRAM);
  buffer = alloca(N);

  while (iter--) {
    recvfrom(fd, buffer, N, 0, (struct sockaddr *)&sa, &s);
    printf("%s:%d -> %s\n", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port), buffer);

    buffer[rand() % N] = 'x';
    sendto(fd, buffer, N, 0, (struct sockaddr *)&sa, s);
  }

  close(fd);
  return 0;
}