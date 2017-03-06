#ifndef DRAWSHEEP_CLIENT_HPP
#define DRAWSHEEP_CLIENT_HPP
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Client {
private :
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[2048];

public :
    Client(int port);

    ~Client();

    void send_drawing();

};

#endif //DRAWSHEEP_CLIENT_HPP

