#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <unistd.h>

static int deservire_client(int sursa, int destinatie) {
  char buffer[4096];
  ssize_t n;
  while ((n = recv(sursa, buffer, sizeof(buffer), 0)) > 0) {
    ssize_t trimis = 0;
    while (trimis < n) {
      ssize_t k = send(destinatie, buffer + trimis, n - trimis, 0);
      if (k <= 0) {
        printf("Eroare la send\n");
        shutdown(sursa, SHUT_RDWR);
        shutdown(destinatie, SHUT_RDWR);
        return 1;
      }
      trimis += k;
    }
  }
  if (n < 0) {
    printf("Eroare la recv\n");
    shutdown(sursa, SHUT_RDWR);
    shutdown(destinatie, SHUT_RDWR);
    return 1;
  }

  // Propaga sfarsitul datelor. Celalalt proces poate transmite in sens invers.
  shutdown(destinatie, SHUT_WR);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    printf("Utilizare: %s [IPv4_server_SSH]\n", argv[0]);
    return 1;
  }
  // Fara argument: oglindire locala. Cu adresa IPv4: serverul SSH din enunt.
  const char *ip_destinatie = argc == 2 ? argv[1] : "127.0.0.1";
  uint16_t port_destinatie = argc == 2 ? 3389 : 1234;
  struct sockaddr_in server1, server2;

  int s1 = socket(AF_INET, SOCK_STREAM, 0);
  if (s1 < 0) {
    printf("Eroare: socket server1\n");
    return 1;
  }

  memset(&server1, 0, sizeof(server1));
  server1.sin_port = htons(2222);
  server1.sin_family = AF_INET;
  server1.sin_addr.s_addr = INADDR_ANY;

  memset(&server2, 0, sizeof(server2));
  server2.sin_port = htons(port_destinatie);
  server2.sin_family = AF_INET;
  if (inet_pton(AF_INET, ip_destinatie, &server2.sin_addr) != 1) {
    printf("Adresa IPv4 a destinatiei este invalida\n");
    close(s1);
    return 1;
  }

  if (bind(s1, (struct sockaddr *) &server1, sizeof(server1)) < 0) {
    printf("Eroare: bind server1\n");
    close(s1);
    return 1;
  }
  if (listen(s1, 5) < 0) {
    printf("Eroare: listen server1\n");
    close(s1);
    return 1;
  }

  while (1) {
    int c = accept(s1, NULL, NULL);
    if (c < 0) {
      printf("Eroare la accept\n");
      continue;
    }
    pid_t pid = fork();
    if (pid < 0) {
      printf("Eroare: fork\n");
      close(c);
      continue;
    }
    if (pid == 0) {
      close(s1);
      int s2 = socket(AF_INET, SOCK_STREAM, 0);
      if (s2 < 0) {
        printf("Eroare: socket pentru server2\n");
        close(c);
        return 1;
      }
      if (connect(s2, (struct sockaddr *) &server2, sizeof(server2)) < 0) {
        printf("Client acceptat, dar conectarea la %s:%hu a esuat\n",
               ip_destinatie, port_destinatie);
        close(s2);
        close(c);
        return 1;
      }

      pid_t sens = fork();
      if (sens < 0) {
        printf("Eroare la fork pentru al doilea sens\n");
        close(s2);
        close(c);
        return 1;
      }
      int status;
      if (sens == 0) {
        status = deservire_client(c, s2);
      } else {
        printf("Client acceptat. Conectat la %s:%hu\n", ip_destinatie, port_destinatie);
        status = deservire_client(s2, c);
      }
      close(s2);
      close(c);
      return status;
    }
    close(c);
  }
}
