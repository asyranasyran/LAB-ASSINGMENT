#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

void func(int socket_desc) 
{ 
	char buffer[80]; 
	int n; 
    printf("Welcome!\n");
	printf("Write you message below, type exit to end the session\n");
	for (;;)
        { 
		bzero(buffer, 80); 

		read(socket_desc, buffer, sizeof(buffer)); 

		printf("Message : %s\t You : ", buffer); 
		bzero(buffer, 80);
		n = 0; 

		while ((buffer[n++] = getchar()) != '\n') 
			; 

		write(socket_desc, buffer, sizeof(buffer)); 

		if (strncmp("exit", buffer, 4) == 0) { 
			printf("Exiting...\n"); 
			break; 
		} 
	} 
} 

int main(int argc , char *argv[]) 
{ 
	int socket_desc, connfd, len; 
	struct sockaddr_in server, client; 

	socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
	if (socket_desc == -1) { 
		printf("Unable to create socket\n"); 
		exit(0); 
	} 
	else
		printf("Socket created\n"); 
	bzero(&server, sizeof(server)); 

	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = htonl(INADDR_ANY); 
	server.sin_port = htons(8888); 

	if ((bind(socket_desc, (struct sockaddr *)&server , sizeof(server))) != 0) { 
		printf("Binding failed\n"); 
		exit(0); 
	} 
	else
		printf("Binding successfull\n"); 

	if ((listen(socket_desc, 5)) != 0) { 
		printf("Unable to detect client connection\n"); 
		exit(0); 
	} 
	else
		printf("Waiting for client to connect\n"); 
	len = sizeof(client); 

	connfd = accept(socket_desc, (struct sockaddr *)&client, &len); 
	if (connfd < 0) { 
		printf("Unable to connect to the client\n"); 
		exit(0); 
	} 
	else
		printf("Connection with the client successfully\n"); 

	func(connfd); 
	close(socket_desc); 
} 
