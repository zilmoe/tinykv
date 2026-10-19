// a small networking socket :)

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/macos_local.sock"
#define BACKLOG 5

class Socket
{
private:
  int soc;
  int fd_conn;
public:
  Socket(): soc(socket(AF_UNIX, SOCK_STREAM, 0)) {
    unlink(SOCKET_PATH);
    if (soc < 0) {
      exit(0); // maybe don't exit here
    }
    std::cout << "A socket has been created!\n";
  }

  int bindSoc() const {
    struct sockaddr_un serv_addr{};
    serv_addr.sun_family = AF_UNIX;
    strncpy(static_cast<char *>(serv_addr.sun_path), SOCKET_PATH, sizeof(serv_addr.sun_path) - 1);
    int bind_res = bind(soc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (bind_res < 0){
      close(soc);
      std::cout << "Unable to bind to an address\n";
      std::cout << std::strerror(errno) << "\n";
      return -1;
    }
    std::cout << "Socket has been bound to an address\n";
    return 0;
  }

  int listenSoc() const {
    if (listen(soc, BACKLOG) < 0) {
      std::cout << "Unable to listen for a connection\n";
      return -1;
    }
    std::cout << "Listening for a connection!\n";
    return 0;
  }

  int acceptSoc() {
    fd_conn = accept(soc, 0, 0);
    if (fd_conn < 0) {
      std::cout << "Unable to accept a connection\n";
    }
    std::cout << "Accepted a connection\n";
    return fd_conn;
  }

  ~Socket() {
    std::cout << "Closing the socket and fd\n";
    unlink(SOCKET_PATH);
    shutdown(soc, SHUT_WR);
    close(soc);
  }

  std::string readSoc(int nbytes) const {
    std::array<char, 0x20> buf = {};
    read(fd_conn, static_cast<void *>(&buf), 0x20);
    std::string res(std::begin(buf), std::end(buf));
    return res;
  }

  size_t writeSoc(const std::string &mes) const {
    std::cout << "Writing: " << mes << " to the client!\n";
    size_t res = write(fd_conn, static_cast<const void *>(mes.data()), mes.size());
    return res;
  }
};

int main() {
  Socket soc = Socket();
  if (soc.bindSoc() < 0) {
    return -1;
  }
  if (soc.listenSoc() < 0) {
    return -1;
  }
  if (soc.acceptSoc() < 0) {
    return -1;
  }
  soc.writeSoc("Hello from the other side!");
  sleep(5);
  return 0;
}
