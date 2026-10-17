// a small networking socket :)

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket
{
public:
  Socket() {
    struct sockaddr_in serv_addr;
    int soc = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (soc < 0) {
      // an error has happened;
      exit(0);
    }
    std::cout << "A socket has been created!\n";
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);
    int bind_res = bind(soc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (bind_res < 0){
      std::cout << "Unable to bind to an address\n";
      exit(0);
    }
    std::cout << "Socket has been bound to an address\n";

    if (listen(soc, 5) < 0) {
      std::cout << "Unable to listen for a connection\n";
      exit(0);
    }
    std::cout << "Listening for a connection!\n";

    // we are now bound to a port;
    // accept(); //maybe?
  }

  ~Socket() {
    std::cout << "fuck this stupid languauge wtf is this\n";
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
  return 0;
}
