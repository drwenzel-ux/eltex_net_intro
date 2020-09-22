#include "unix_socket.h"

int main(int argc, char *argv[]) {
  int ret;
  int result;
  int down_flag = 0;
  int data_socket;
  int connection_socket;
  char buffer[BUFFER_SIZE];

  connection_socket = unix_listen(SOCK_SEQPACKET, 20);

  for (;;) {
    data_socket = accept(connection_socket, NULL, NULL);
    if (data_socket == -1) {
      perror("accept");
      exit(1);
    }

    result = 0;
    for (;;) {
      ret = read(data_socket, buffer, BUFFER_SIZE);
      if (ret == -1) {
        perror("read");
        exit(1);
      }

      buffer[BUFFER_SIZE - 1] = 0;

      if (!strncmp(buffer, "DOWN", BUFFER_SIZE)) {
        down_flag = 1;
        break;
      }

      if (!strncmp(buffer, "END", BUFFER_SIZE))
        break;

      result += atoi(buffer);
    }

    sprintf(buffer, "%d", result);
    ret = write(data_socket, buffer, BUFFER_SIZE);
    if (ret == -1) {
      perror("write");
      exit(1);
    }

    close(data_socket);

    if (down_flag) {
      break;
    }
  }

  close(connection_socket);
  unlink(SOCKET_NAME);

  return 0;
}