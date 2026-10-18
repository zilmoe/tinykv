// a small networking socket :)

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/un.h>

#define PORT 8080
#define BACKLOG 5
#define SOCKET_PATH "/tmp/macos_local.sock"

class Socket
{
private:
  int soc;
public:
  Socket() {
    unlink(SOCKET_PATH);
    soc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (soc < 0) {
      // an error has happened;
      exit(0);
    }
    std::cout << "A socket has been created!\n";
    // we are now bound to a port;
    // accept(); //maybe?
  }

  int bind_soc() {
    struct sockaddr_un serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCKET_PATH, sizeof(serv_addr.sun_path) - 1);
    int bind_res = bind(soc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (bind_res < 0){
      std::cout << "Unable to bind to an address\n";
      std::cout << std::strerror(errno) << std::endl;
      return -1;
    }
    std::cout << "Socket has been bound to an address\n";
    return 0;
  }

  int listen_soc() {
    if (listen(soc, 5) < 0) {
      std::cout << "Unable to listen for a connection\n";
      return -1;
    }
    std::cout << "Listening for a connection!\n";
    return 0;
  }

  ~Socket() {
    std::cout << "Closing the socket and fd\n";
    shutdown(soc, SHUT_WR);
    close(soc);
  }

  int read() {
    std::cout << "This isn't implemented yet!";
    return 0;
  }

  int write() {
    std::cout << "This is also not implemented yet!";
    return 0;
  }
};

int main() {
  Socket soc = Socket();
  soc.bind_soc();
  soc.listen_soc();
  return 0;
}
