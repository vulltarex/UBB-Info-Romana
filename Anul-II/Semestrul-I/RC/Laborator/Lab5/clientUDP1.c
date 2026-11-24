#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t n;
  char sir[1000];
  
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  printf("Introduceti sirul: ");
  fgets(sir, 999, stdin);

  sir[strcspn(sir, "\n")] = '\0';
  n = strlen(sir);
  n = htons(n);
  sendto(c, &n, sizeof(uint16_t), 0, (struct sockaddr *) &server, sizeof(server));
  sendto(c, sir, sizeof(char) * n, 0, (struct sockaddr *) &server, sizeof(server));
  
  close(c);
}

