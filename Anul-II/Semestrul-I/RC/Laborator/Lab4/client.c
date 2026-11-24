#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

int main(void) {
  int c;
  struct sockaddr_in server;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("192.168.40.220");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    close(c);
    return 1;
  }
  char username[1001];

  printf("introduceti username: ");
  if (scanf("%1000s", username) != 1) {
    printf("Eroare la citirea username-ului\n");
    close(c);
    return 1;
  }

  // Codul 0 pe un octet indica faptul ca trimitem un username.
  uint8_t tip = 0;
  if (send(c, &tip, sizeof(tip), 0) != sizeof(tip)) {
    printf("Eroare la trimiterea tipului\n");
    close(c);
    return 1;
  }

  uint16_t l;
  l = strlen(username);
  l = htons(l);
  // Trimitem lungimea pe 2 octeti, in ordinea de retea.
  if (send(c, &l, sizeof(l), 0) != sizeof(l)) {
    printf("Eroare la trimiterea lungimii\n");
    close(c);
    return 1;
  }

  // Trimitem username-ul fara caracterul terminator '\0'.
  size_t trimis = 0;
  size_t lungime = strlen(username);
  while (trimis < lungime) {
    ssize_t n = send(c, username + trimis, lungime - trimis, 0);
    if (n <= 0) {
      printf("Eroare la trimiterea username-ului\n");
      close(c);
      return 1;
    }
    trimis += (size_t)n;
  }

  close(c);
  return 0;
}
