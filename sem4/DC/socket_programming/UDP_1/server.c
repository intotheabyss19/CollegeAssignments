// Server

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define CONNECTION_PORT 3110

int main() {
  int sockfd;
  int status;
  char *ip = "127.0.0.1";
  char *buffer1 = "hello from server";
  char buffer2[100];
  ssize_t addr_len;
  socklen_t addr_size;
  int length_of_address;
  struct sockaddr * addr;

  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0) {
    perror("Socket Creation Failed\n");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(CONNECTION_PORT);
  server_addr.sin_addr.s_addr = inet_addr(ip);
  memset(&server_addr, '\0', sizeof(server_addr));

  printf("[+] UDP Socket Created\n");

  status = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (status < 0) {
    perror("Couldn't bind socket\n");
    exit(EXIT_FAILURE);
  }

  printf("[+] Socket Binded Successfully\n");

  socklen_t len = sizeof(client_addr);

  printf("[+] Waiting for Client's Message\n");
  int n1 = recvfrom(sockfd, buffer2, sizeof(buffer2), MSG_CONFIRM, (struct sockaddr *)&client_addr, &len);
  buffer2[n1]='\0';
  puts(buffer2);

  printf("%s\n", buffer2);

  printf("[+] Sending Message to the Client\n");
  int n2 = sendto(sockfd, buffer1, strlen(buffer1), MSG_CONFIRM, (struct sockaddr *)&client_addr, sizeof(client_addr));

  close(sockfd);

  return 0;
}
