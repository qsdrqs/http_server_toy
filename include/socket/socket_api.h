/*
 * include/socket/socket_api.h

 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */
#ifndef SOCKET_API_H
#define SOCKET_API_H
#include <netinet/in.h>
#include <sys/socket.h>
typedef struct sockaddr SA;
typedef struct sockaddr_in SA_in;


/*
 * write to socket_fd
 *
 * @param socket_fd: client socket descriptor
 * @param buffer: message to send
 */
int socket_write(int socket_fd, char* buffer);

/*
 * read from socket_fd (block thread)
 *
 * @param socket_fd: client socket descriptor
 * @param read_size: message size
 */
char* socket_read(int socket_fd, int max_read_size);

/*
 * listen on specific port and ip thorough TCP socket
 *
 * @param listenq_len: max length of socket queue (connected plus waiting for connect)
 * @return: -1: errors, other: socket descriptor
 */
int listen_on_port(uint16_t port, char* ip, int listenq_len);

#endif
