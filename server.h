#ifndef MESSAGE_SERVER_H
#define MESSAGE_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define REQUEST_LIMIT 5
#define CHAT_PORT 19345

#define MESSAGE_BUFFER_SIZE 1024

int main(void);
void initialize_socket(int *sock);
void initialize_sockaddr(struct sockaddr_in *client);
void bind_socket_server(int *sock, struct sockaddr_in *server);
void listen_socket(int *sock);
void accept_client(int *sock);
void receive_from_client(void *sock_ptr);

#endif