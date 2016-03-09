#include "server.h"

int main(void)
{
	int sock;
	struct sockaddr_in sock_addr;
	
	initialize_socket(&sock);
	initialize_sockaddr(&sock_addr);
	bind_socket_server(&sock, &sock_addr);
	listen_socket(&sock);
	for(;;)
	{
		accept_client(&sock);
	}
	
	return EXIT_SUCCESS;
}

void initialize_socket(int *sock)
{
	*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (*sock == -1)
	{
		fprintf(stderr, "ERROR: client could not create socket\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		fprintf(stderr, "SUCCESS: client socket created\n");
	}
}

void initialize_sockaddr(struct sockaddr_in *sock_addr)
{
	memset(sock_addr, 0, sizeof(struct sockaddr_in));
	sock_addr->sin_family = AF_INET;
	sock_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	sock_addr->sin_port = htons(CHAT_PORT);
}

void bind_socket_server(int *sock, struct sockaddr_in *sock_addr)
{
	int status = bind(*sock, (struct sockaddr*)sock_addr, sizeof(struct sockaddr_in));
	
	if (status == 0)
	{
		fprintf(stderr, "SUCCESS: server socket bind successfully\n");
	}
	else
	{
		fprintf(stderr, "ERROR: server socket bind failed\n");
		close(*sock);
		exit(EXIT_SUCCESS);
	}
}

void listen_socket(int *sock)
{
	int status = listen(*sock, REQUEST_LIMIT);
	
	if (status == -1)
	{
		fprintf(stderr, "ERROR: failed to listen on server socket\n");
		close(*sock);
		exit(EXIT_SUCCESS);
	}
	else
	{
		fprintf(stderr, "SUCCESS: listen on server socket successfully\n");
	}
}

void accept_client(int *sock)
{
	pthread_t thread;
	int client_socket = accept(*sock, NULL, NULL);
	
	if (client_socket == -1)
	{
		fprintf(stderr, "ERROR: failed to accept incoming connection\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		fprintf(stderr, "SUCCESS: successfully accepted incoming connection\n");
	}
	
	
	pthread_create(&thread, NULL, receive_from_client, (void*)&client_socket);
}

void receive_from_client(void *sock_ptr)
{
	int i;
	
	int *sock = (int*)sock_ptr;
	
	int message_count = 0;
	char buffer[MESSAGE_BUFFER_SIZE];
	
	int status;
	
	for (;;)
	{
		for (i = 0; i < MESSAGE_BUFFER_SIZE; i++)
		{
			buffer[i] = '\0';
		}
		
		status = read(*sock, buffer, MESSAGE_BUFFER_SIZE-1);
		if (status == 0)
		{
			close(*sock);
			fprintf(stderr, "NOTIFICATION: client disconnected\n");
			break;
		}
		message_count++;
		printf("%d: %s\n", message_count, buffer);
		while (buffer[MESSAGE_BUFFER_SIZE-2] != '\0')
		{
			for (i = 0; i < MESSAGE_BUFFER_SIZE; i++)
			{
				buffer[i] = '\0';
			}
			read(*sock, buffer, MESSAGE_BUFFER_SIZE-1);
			if (buffer[0] != '\0')
			{
				printf("%d: %s\n", message_count, buffer);
			}
			else
			{
				break;
			}
		}
	}
}
