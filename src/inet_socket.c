#include "inet_socket.h"

int inet_connect(const char *addr, in_port_t port, int type) {
  int fd;
  socklen_t s;
  struct sockaddr_in sa;

  sa.sin_family = FAMILY;
  sa.sin_addr.s_addr = inet_addr(addr);
  sa.sin_port = htons(port);

  fd = socket_create(FAMILY, type, 0);
  socket_connect(fd, (struct sockaddr *)&sa, sizeof(s));

  return fd;
}

static int inet_passive_socket(const char *addr, in_port_t port, int type,
                               int backlog, int do_listen) {
  int fd, ret;
  int optval = 1;
  socklen_t s;
  struct sockaddr_in sa;

  fd = socket_create(FAMILY, type, 0);

  if (do_listen) {
    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret == -1) {
      close(fd);
      perror_die("inet_passive_socket: setsockopt -1", 1);
    }
  }

  sa.sin_family = FAMILY;
  sa.sin_addr.s_addr = inet_addr(addr);
  sa.sin_port = htons(port);
  s = sizeof(sa);

  socket_bind(fd, (struct sockaddr *)&sa, s);

  if (do_listen)
    socket_listen(fd, backlog);

  return fd;
}

int inet_listen(const char *addr, in_port_t port, int backlog) {
  return inet_passive_socket(addr, port, SOCK_STREAM, backlog, 1);
}

int inet_bind(const char *addr, in_port_t port, int type) {
  return inet_passive_socket(addr, port, type, 0, 0);
}