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
    int s;
    struct sockaddr_in server, client;
    socklen_t l;
    int port;
    char mesaj[101];

    if (argc != 2) {
        printf("Utilizare: %s <port>\n", argv[0]);
        return 1;
    }

    port = atoi(argv[1]);
    if (port < 1 || port > 65535) {
        printf("Port invalid\n");
        return 1;
    }

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind");
        close(s);
        return 1;
    }

    printf("Se asteapta mesaje pe portul %d...\n", port);

    while (1) {
        l = sizeof(client);

        ssize_t n = recvfrom(s, mesaj, sizeof(mesaj) - 1, 0,
                            (struct sockaddr *) &client, &l);

        if (n < 0) {
            perror("recvfrom");
            continue;
        }

        mesaj[n] = '\0';
        printf("Primit: %s\n", mesaj);

        // prelucrare mesaj

        if (sendto(s, mesaj, n, 0,
                   (struct sockaddr *) &client, l) < 0) {
            perror("sendto");
        }
    }
}
