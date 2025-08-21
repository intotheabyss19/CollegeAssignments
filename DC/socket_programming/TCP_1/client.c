// Client Side

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define CONNECTION_PORT 9090

int multiply(int a, int b) { 
	return a * b;
}

int main() {
	int socket_descriptor;
	int status;
	char *ip = "172.16.8.180";
	socklen_t addr_size;
	int a, b, c;
	int length_of_address;
	struct sockaddr_in server_address;
	struct sockaddr_in connection_address;

	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor < 0) {
		perror("Socket Creation Failed\n");
		exit(EXIT_FAILURE);
	}


	connection_address.sin_family = AF_INET;
	connection_address.sin_port = htons(CONNECTION_PORT);
	connection_address.sin_addr.s_addr = inet_addr(ip);
	memset(&connection_address, '\0', sizeof(connection_address));

	int connect_status = connect(socket_descriptor, (struct sockaddr*)&server_address, sizeof(server_address));
	printf("[+]Connecting to the server.\n");
	
	while(1) {
		printf("Enter a: ");
		scanf("%d", &a);

		printf("Enter b: ");
		scanf("%d", &b);

		send(socket_descriptor, &a, sizeof(int), 0);
		send(socket_descriptor, &b, sizeof(int), 0);

		recv(socket_descriptor, &c, sizeof(int), 0);
	}

	close(socket_descriptor);

	return 0;
}
