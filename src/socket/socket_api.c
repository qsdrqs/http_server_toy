/*
 * src/socket/socket_api.c: provide basic socket package apis
 *
 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket/socket_api.h"
#include "global.h"

int socket_write(int socket_fd, char* buffer)
{
    return write(socket_fd, buffer, strlen(buffer));
}

char* socket_read(int socket_fd, int max_read_size)
{
    char* buffer = malloc(max_read_size * sizeof(char));
    ssize_t n = read(socket_fd, buffer, max_read_size);
    while (n <= 0) {
        n = read(socket_fd, buffer, max_read_size);
    }
    return buffer;
}

int listen_on_port(uint16_t port, char* ip, int listen_queue)
{
    // init sockaddr
    struct sockaddr_in listen_addr;
    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &listen_addr.sin_addr);
    listen_addr.sin_port = htons(port);

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd > 0) {
        // bind
        if (bind(listen_fd, (SA*)&listen_addr, sizeof(listen_addr))) {
            printf("Error on binding ip at %s and port at %d!", ip, port);
            return -1;
        }
        // listen
        if (listen(listen_fd, listen_queue)) {
            puts("Error on listening");
            return -1;
        }
        // accept
        while (true) {
            SA_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int connect_fd = accept(listen_fd, (SA*)&client_addr, &client_len);
            int child_pid = fork();
            if (child_pid == 0) {
                // child process
                close(listen_fd); // child process close listen_fd
                return connect_fd;
                exit(0);
            }
            close(connect_fd); // TODO: understand
        }
        return 0;
    } else {
        puts("can't open socket!");
        return -1;
    }
}
