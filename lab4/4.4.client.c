#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>

void func(int socket_desc) 
{ 
	char buffer[80]; 
	int n; 
  printf("Welcome!\n");
	printf("Write you message below, type exit to end the session\n");
	for (;;)
        { 
		bzero(buffer, sizeof(buffer)); 
		printf("You : "); 
		n = 0; 
		while ((buffer[n++] = getchar()) != '\n'); 
		write(socket_desc, buffer, sizeof(buffer)); 
		bzero(buffer, sizeof(buffer)); 
		read(socket_desc, buffer, sizeof(buffer)); 
		printf("From Server : %s", buffer); 
		if ((strncmp(buffer, "exit", 4)) == 0)
                { 
			printf("Exiting...\n"); 
			break; 
		} 
	} 
} 

int main() 
{ 
	int socket_desc, connfd; 
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
	server.sin_addr.s_addr = inet_addr("192.168.65.10"); 
	server.sin_port = htons(8888); 

	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) != 0)
        { 
		printf("Unable to established connection with the server\n"); 
		exit(0); 
	} 
	else
		printf("Connection with the server successfull\n"); 

	func(socket_desc); 
	close(socket_desc); 

} 
