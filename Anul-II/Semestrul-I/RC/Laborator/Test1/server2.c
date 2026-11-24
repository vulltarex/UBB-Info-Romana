#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <unistd.h>

static int deservire_client(int c) {
  char sir[100], sir_oglindit[100];
  uint16_t len_retea;
  if (recv(c, &len_retea, sizeof(len_retea), MSG_WAITALL) != sizeof(len_retea)) {
    printf("Lungime incompleta\n");
    return 1;
  }
  uint16_t len = ntohs(len_retea);
  if (len > sizeof(sir)) {
    printf("Sir prea lung: %hu\n", len);
    return 1;
  }
  if (len > 0 && recv(c, sir, len, MSG_WAITALL) != len) {
    printf("Sir incomplet\n");
    return 1;
  }
  for (size_t i = 0; i < len; i++) {
    sir_oglindit[i] = sir[len - 1 - i];
  }
  if (len > 0 && send(c, sir_oglindit, len, 0) != len) {
    printf("Eroare la trimiterea sirului oglindit\n");
    return 1;
  }
  return 0;
}

int main(void) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare: socket server2\n");
    return 1;
  }

  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare: bind server2\n");
    close(s);
    return 1;
  }
  if (listen(s, 5) < 0) {
    printf("Eroare: listen server2\n");
    close(s);
    return 1;
  }

  while (1) {
    int c = accept(s, NULL, NULL);
    if (c < 0) {
      printf("Eroare la accept\n");
      continue;
    }
    pid_t pid = fork();
    if (pid < 0) {
      printf("Eroare: fork server2\n");
      close(c);
      continue;
    }
    if (pid == 0) {
      close(s);
      printf("S-a conectat un client la server2\n");
      int status = deservire_client(c);
      close(c);
      return status;
    }
    close(c);
  }
}
