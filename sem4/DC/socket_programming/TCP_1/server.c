// Server Side

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>		// stores data structure for storing IP address
#include <fcntl.h>
#include <arpa/inet.h>

#define CONNECTION_PORT 9090

int multiply(int a, int b) { 
	return a * b;
}

int main() {
	int socket_descriptor;			// server socket
	int client_socket;			// socket created by the bind function
	char *ip = "127.0.0.1";
	int status;
	socklen_t addr_size;
	int a = 0, b = 0, c  = 0;
	int length_of_address;
	struct sockaddr_in server_address;
	struct sockaddr_in connection_address;

	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor < 0) {
		perror("Socket Creation Failed\n");
		exit(EXIT_FAILURE);
	}

	server_address.sin_family = AF_INET;			// Initializing structure elements for the address
	server_address.sin_port = htons(CONNECTION_PORT);	// Convert port to network byte order using htons
	/*server_address.sin_addr.s_addr = INADDR_ANY;		// Any address available*/
	server_address.sin_addr.s_addr = inet_addr(ip);
	memset(&connection_address, '\0', sizeof(connection_address));
	/*server_address.sin_zero[8] = '\0';			// Assigning null character to the last index of the ch..*/

	close(socket_descriptor);
	status = bind(socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr_in));

	if (status < 0) {
		perror("Couldn't bind socket\n");
		exit(EXIT_FAILURE);
	}
	
	listen(socket_descriptor, 1);
	printf("Listening...\n");
	while(1) {
		addr_size = sizeof(connection_address);
		client_socket = accept(client_socket, (struct sockaddr*)&connection_address, &addr_size);

		if (client_socket < 0) {
			perror("[-]Error");
			break;
		}
		printf("Client Connected");
		printf("Client: %d", a);

		recv(client_socket, &a, sizeof(int), 0);
		recv(client_socket, &b, sizeof(int), 0);

		c = multiply(a,b);
		send(socket_descriptor, &c, sizeof(int), 0);
	}
	close(client_socket);
	close(socket_descriptor);

	return 0;
}
