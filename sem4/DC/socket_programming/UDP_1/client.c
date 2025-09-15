// Client

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
  char *buffer1 = "hi";
  char buffer2[100];
  ssize_t addr_len;
  socklen_t addr_size;
  int length_of_address;

  struct sockaddr_in server_addr;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0) {
    perror("[-] Socket Creation Failed\n");
    exit(EXIT_FAILURE);
  }
  printf("[+] UDP Socket Created\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(CONNECTION_PORT);
  server_addr.sin_addr.s_addr = inet_addr(ip);
  memset(&server_addr, '\0', sizeof(server_addr));

  socklen_t len = sizeof(server_addr);

  printf("[+] Sending Message to the Server\n");
  int n1 = sendto(sockfd, buffer1, strlen(buffer1), 0, (struct sockaddr *)&server_addr, len);
  printf("Message sent to the Server\n");

  printf("[+] Waiting for Server's Message\n");
  int n2 = recvfrom(sockfd, buffer2, sizeof(buffer2), 0, (struct sockaddr *)&server_addr, &len);
  printf("printing the message\n");
  buffer2[n2] = '\0';
  puts(buffer2);

  return 0;
}
