#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
  int c;
  struct sockaddr_in server;
  char sir[1001];
  uint16_t len, nr_spatii;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  printf("Sirul: ");
  if (fgets(sir, sizeof(sir), stdin) == NULL) {
    printf("Eroare la citirea sirului\n");
    close(c);
    return 1;
  }
  // eliminam newline-ul de la final
  sir[strcspn(sir, "\n")] = '\0';

  len = strlen(sir);
  len = htons(len);
  send(c, &len, sizeof(len), 0);
  send(c, sir, strlen(sir), 0);

  recv(c, &nr_spatii, sizeof(nr_spatii), MSG_WAITALL);
  nr_spatii = ntohs(nr_spatii);
  printf("Numarul de spatii este %hu\n", nr_spatii);

  close(c);
  return 0;
}
