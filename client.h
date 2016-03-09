#ifndef MESSAGE_CLIENT_H
#define MESSAGE_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define CHAT_CLIENT_ADDRESS "127.0.0.1"
#define CHAT_PORT 19345

#define MESSAGE_BUFFER_SIZE 1024

int main(void);
void initialize_socket(int *sock);
void initialize_sockaddr(struct sockaddr_in *sock_addr);
void connect_socket_sockaddr(int *sock, struct sockaddr_in *sock_addr);
void x_write(int *client_socket);

#endif