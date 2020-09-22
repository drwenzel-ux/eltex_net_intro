#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inet_socket.h"

#define N 20

int main(int argc, char const *argv[]) {
  int fd, cfd, iter;
  char *buffer;
  struct sockaddr_in sa;
  socklen_t s;

  if (argc < 2) {
    fprintf(stderr, "usage: ./server <iter>\n");
    exit(1);
  }

  iter = atoi(argv[1]);
  srand(time(0));

  fd = inet_listen("127.0.0.1", 7777, 3);
  buffer = alloca(N);
  while (iter--) {
    cfd = accept(fd, (struct sockaddr *)&sa, &s);

    read(cfd, buffer, N);
    printf("%s:%d -> %s\n", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port), buffer);

    buffer[rand() % N] = 'x';

    write(cfd, buffer, N);
    close(cfd);
  }

  close(fd);
  return 0;
}