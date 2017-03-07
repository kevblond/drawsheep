#include <Server.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
Server::Server(int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        throw "ERROR opening socket";
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        throw "ERROR on binding";
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
}

void Server::start() {
    std::cout << "Server start" << std::endl;
    while (1)
    {
        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            throw "ERROR on accept";
        // un process par client
        int pid = fork();
        if (pid < 0)
            throw "ERROR on fork";
        if (pid == 0)
        {
            read_file(newsockfd);
//            verify_draw(newsockfd);
            send_answer(newsockfd);
            exit(0);
        }
        else
            close(newsockfd);
    } /* end of while */
}

void Server::read_file(int sockfd) {
    std::string filename;
    filename = "client" + cli_addr.sin_addr.s_addr;
    std::ofstream file(filename);

    char buffer[2048];
    long n;
    n = recv(newsockfd,buffer,2047, 0);
    if (n < 0)
        throw "ERROR server reading from socket";
    file << buffer;
    file.close();
    std::cout << "file received" << std::endl;

}

void Server::send_answer(int sockfd) {
    long n;
    std::string comment = "J'ai reçu le fichier !";
    n = write(sockfd,comment.c_str(),comment.size());
    if (n < 0)
        throw "ERROR writing to socket";
}

