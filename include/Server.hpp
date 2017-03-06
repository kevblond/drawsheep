#ifndef DRAWSHEEP_SERVER_HPP
#define DRAWSHEEP_SERVER_HPP

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Server {
private :
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[2048];

public:
    Server(int port);

    void start();

    void read_draw(int sockfd) {}

    void verify_draw(int sockfd) {}

};
#endif //DRAWSHEEP_SERVER_HPP
