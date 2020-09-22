#include "unix_socket.h"

int main(int argc, char *argv[]) {
  int i;
  int ret;
  int data_socket;
  char buffer[BUFFER_SIZE];

  data_socket = unix_connect(SOCK_SEQPACKET);

  for (i = 1; i < argc; ++i) {
    ret = write(data_socket, argv[i], strlen(argv[i]) + 1);
    if (ret == -1) {
      perror("write");
      break;
    }
  }

  strcpy(buffer, "END");
  ret = write(data_socket, buffer, strlen(buffer) + 1);
  if (ret == -1) {
    perror("write");
    exit(1);
  }

  ret = read(data_socket, buffer, BUFFER_SIZE);
  if (ret == -1) {
    perror("read");
    exit(1);
  }

  buffer[BUFFER_SIZE - 1] = 0;
  printf("Result = %s\n", buffer);

  close(data_socket);

  return 0;
}