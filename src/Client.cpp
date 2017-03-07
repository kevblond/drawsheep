#include <Client.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
Client::Client(int port) {
    portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        throw "ERROR opening socket";
    // TODO Modifier plus tard pour co a distance
    server = gethostbyname("localhost");
    if (server == NULL) {
        throw "ERROR, no such host\n";
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        throw "ERROR connecting";
    std::cout << "Client Connected" << std::endl;
}

void Client::send_file(const char * filename) {
    std::ifstream infile(filename);
    std::string line;
    int n;
    while (std::getline(infile, line)) {
        n = write(sockfd,line.c_str(),line.size());
        if (n < 0)
            throw "ERROR writing to socket";
    }
    std::cout << "file sent" << std::endl;

}

void Client::read_string() {
    char buffer[2048];
    long n;
    n = recv(sockfd,buffer,2047, 0);
    if (n < 0)
        throw "ERROR reading from socket";
    std::cout << buffer << std::endl;
}

Client::~Client() {
    close(sockfd);
}
