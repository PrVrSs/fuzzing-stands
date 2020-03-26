#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void shell(int sock) {
    char data[256];
    bzero(data, sizeof(data));

    int len = read(sock, data, 256);
    if (len == 0)
        return;

    int verify = strncmp(data, "admin", 5);
    if (verify == 0)
    {
        write(sock, "Did it\n", 7);
//        system("/bin/sh");
        exit(1);
    }

    write(sock, "ok", 2);

    return;
}


int main( int argc, char *argv[] ) {
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[256];

    int portno = argc == 2 ? atoi(argv[1]) : 5001;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEPORT) failed");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    printf("Listening on port: %i\n", portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    listen(sockfd, 5);
    int clilen = sizeof(cli_addr);

    while (1) {
        int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) {
             perror("ERROR on accept");
             exit(1);
        }

        printf("New client connected\n");

        shell(newsockfd);
        shutdown(newsockfd, 2);
        close(newsockfd);
    }
}
