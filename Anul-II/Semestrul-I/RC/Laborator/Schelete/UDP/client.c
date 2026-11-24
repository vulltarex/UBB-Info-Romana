#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int c;
    struct sockaddr_in server;
    int port;
    char mesaj[101];

    if (argc != 3) {
        printf("Utilizare: %s <ip_server> <port_server>\n", argv[0]);
        return 1;
    }

    port = atoi(argv[2]);
    if (port < 1 || port > 65535) {
        printf("Port invalid\n");
        return 1;
    }

    c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        perror("socket");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, argv[1], &server.sin_addr) != 1) {
        printf("Adresa IP invalida\n");
        close(c);
        return 1;
    }

    printf("Mesaj: ");
    if (fgets(mesaj, sizeof(mesaj), stdin) == NULL) {
        close(c);
        return 1;
    }

    mesaj[strcspn(mesaj, "\n")] = '\0';

    if (sendto(c, mesaj, strlen(mesaj), 0,
               (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("sendto");
        close(c);
        return 1;
    }

    ssize_t n = recvfrom(c, mesaj, sizeof(mesaj) - 1, 0, NULL, NULL);

    if (n < 0) {
        perror("recvfrom");
        close(c);
        return 1;
    }

    mesaj[n] = '\0';
    printf("Raspuns: %s\n", mesaj);

    close(c);
    return 0;
}
