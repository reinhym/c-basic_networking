#include "client.h"

int main(void)
{
	int sock;
	struct sockaddr_in sock_addr;
	
	initialize_socket(&sock);
	initialize_sockaddr(&sock_addr);
	connect_socket_sockaddr(&sock, &sock_addr);
	x_write(&sock);
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
	sock_addr->sin_addr.s_addr = inet_addr(CHAT_CLIENT_ADDRESS);
	sock_addr->sin_port = htons(CHAT_PORT);
}

void connect_socket_sockaddr(int *sock, struct sockaddr_in *sock_addr)
{
	int status = connect(*sock, (struct sockaddr*)sock_addr,
		sizeof(struct sockaddr_in));
	
	if (status == 0)
	{
		fprintf(stderr, "SUCCESS: client connected to server successfully\n");
	}
	else
	{
		fprintf(stderr, "ERROR: client failed to connect to server\n");
		close(*sock);
		exit(EXIT_SUCCESS);
	}
}

void x_write(int *sock)
{
	int i;
	char buffer[MESSAGE_BUFFER_SIZE];
	
	for (;;)
	{
		for (i = 0; i < MESSAGE_BUFFER_SIZE; i++)
		{
			buffer[i] = '\0';
		}
		
		fgets(buffer, MESSAGE_BUFFER_SIZE, stdin);
		buffer[strlen(buffer)-1] = '\0';
		write(*sock, buffer, strlen(buffer)+1);
	}
}

















