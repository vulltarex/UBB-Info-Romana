#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  int s;
  struct sockaddr_in server, client;
  socklen_t l;
  char sir[1000];

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  uint16_t n;

  recvfrom(s, &n, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *) &client, &l);
  n = ntohs(n);
  recvfrom(s, sir, sizeof(char) * n, MSG_WAITALL, (struct sockaddr *) &client, &l);
  
  sir[n] = '\0';
  char sir_oglindit[1000];
  int j = 0;
  for(int i = strlen(sir) - 1; i >= 0; i--) {
      sir_oglindit[j++] = sir[i];
  }
  sir_oglindit[j] = '\0';
  printf("Am primit: %s\n", sir);
  printf("Sirul oglindit: %s\n", sir_oglindit);
  
  close(s);
}
