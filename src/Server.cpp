#include <Server.hpp>

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
            close(sockfd);
            verify_draw(newsockfd);
            exit(0);
        }
        else
            close(newsockfd);
    } /* end of while */
}

