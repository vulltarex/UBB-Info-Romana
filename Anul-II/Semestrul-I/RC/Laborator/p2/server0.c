#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
  int s;
  struct sockaddr_in server, client;
  int c;
  socklen_t l;

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }

  // permite repornirea rapida a serverului (evita "Address already in use")
  int opt = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  listen(s, 5);

  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while (1) {
    uint16_t len, nr_spatii;
    char *sir;
    int i;

    c = accept(s, (struct sockaddr *) &client, &l);
    if (c < 0) {
      printf("Eroare la accept\n");
      continue;
    }
    printf("S-a conectat un client.\n");

    // deservirea clientului
    // 1. primim lungimea sirului
    if (recv(c, &len, sizeof(len), MSG_WAITALL) != sizeof(len)) {
      printf("Eroare la primirea lungimii\n");
      close(c);
      continue;
    }
    len = ntohs(len);

    // 2. primim sirul de caractere
    sir = (char *) malloc(len + 1);
    if (sir == NULL) {
      printf("Eroare la alocarea memoriei\n");
      close(c);
      continue;
    }
    if (len > 0 && recv(c, sir, len, MSG_WAITALL) != len) {
      printf("Eroare la primirea sirului\n");
      free(sir);
      close(c);
      continue;
    }
    sir[len] = '\0';

    // 3. numaram spatiile
    nr_spatii = 0;
    for (i = 0; i < len; i++) {
      if (sir[i] == ' ') {
        nr_spatii++;
      }
    }
    printf("Sir primit: \"%s\" -> %hu spatii\n", sir, nr_spatii);

    // 4. trimitem rezultatul
    nr_spatii = htons(nr_spatii);
    send(c, &nr_spatii, sizeof(nr_spatii), 0);

    free(sir);
    close(c);
    // sfarsitul deservirii clientului
  }
}
