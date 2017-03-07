#ifndef DRAWSHEEP_CLIENT_HPP
#define DRAWSHEEP_CLIENT_HPP

#include <netinet/in.h>


class Client {
private :
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

public :
    Client(int port);

    ~Client();

    void send_file(const char *filename);

    void read_string();

};

#endif //DRAWSHEEP_CLIENT_HPP

