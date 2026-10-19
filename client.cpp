#include<unistd.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<iostream>

#define SOCKET_PATH "/tmp/macos_local.sock"
#define BUFSIZE 0x20

int main(){
  int soc = socket(AF_UNIX, SOCK_STREAM, 0);
  if (soc < 0){
    std::cout << "Failed to make a socket!\n";
    exit(0);
  }

  struct sockaddr_un serv_addr{};
  serv_addr.sun_family = AF_UNIX;
  strncpy(static_cast<char *>(serv_addr.sun_path), SOCKET_PATH, sizeof(serv_addr.sun_path) - 1);

  int fd_conn = connect(soc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  if (fd_conn < 0) {
    close(soc);
    std::cout << "Couldn't connect to a socket. Is the server open?\n";
    exit(0);
  }

  std::array<char, BUFSIZE> buf = {};
  size_t bytes = 0;
  while ((bytes = read(soc, &buf, BUFSIZ)) > 0)
    write(1, &buf, bytes);
  close(soc);
  return 0;
}
