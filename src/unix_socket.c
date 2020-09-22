#include "unix_socket.h"

int unix_connect(int type) {
  int fd;
  struct sockaddr_un su;

  su.sun_family = FAMILY;
  strncpy(su.sun_path, SOCKET_NAME, sizeof(su.sun_path) - 1);

  fd = socket_create(FAMILY, type, 0);
  socket_connect(fd, (struct sockaddr *)&su, sizeof(su));

  return fd;
}

static int unix_passive_socket(int type, int backlog, int do_listen) {
  int fd;
  socklen_t s;
  struct sockaddr_un su;

  su.sun_family = AF_UNIX;
  strncpy(su.sun_path, SOCKET_NAME, sizeof(su.sun_path) - 1);
  s = sizeof(su);

  fd = socket_create(FAMILY, SOCK_SEQPACKET, 0);

  socket_bind(fd, (struct sockaddr *)&su, s);

  if (do_listen)
    socket_listen(fd, backlog);

  return fd;
}

int unix_listen(int type, int backlog) {
  return unix_passive_socket(type, backlog, 1);
}

int unix_bind(int type) { return unix_passive_socket(type, 0, 0); }