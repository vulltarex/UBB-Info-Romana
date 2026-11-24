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

int main(int argc, char *argv[]) {
    int s, c;
    struct sockaddr_in server, client;
    socklen_t l;
    int port;
    char ip_client[INET_ADDRSTRLEN];
    uint16_t n, vect[100];
    uint32_t suma = 0;

    if (argc != 2) {
        printf("Utilizare: %s <port>\n", argv[0]);
        return 1;
    }

    port = atoi(argv[1]);
    if (port < 1 || port > 65535) {
        printf("Port invalid: %s (trebuie sa fie intre 1 si 65535)\n", argv[1]);
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la bind (portul %d este ocupat sau nepermis)\n", port);
        close(s);
        return 1;
    }
    
    if(listen(s, 5) < 0) {
        printf("Eroare listen");
        close(s);
        return 1;
    }

    printf("Se asteapta conexiuni pe portul %d...\n", port);

    while (1) {
        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        c = accept(s, (struct sockaddr *) &client, &l);
        if (c < 0) {
            printf("Eroare la accept\n");
            continue;
        }

        if (inet_ntop(AF_INET, &client.sin_addr, ip_client, sizeof(ip_client)) == NULL) {
            printf("Eroare la conversia adresei clientului\n");
        }
        else {
            printf("S-a conectat un client: %s:%hu\n", ip_client, ntohs(client.sin_port));
        }
        suma = 0;
        if(recv(c, &n, sizeof(uint16_t), MSG_WAITALL) != sizeof(uint16_t)) {
            printf("Eroare la primirea lungimii\n");
            close(c);
            continue;
        }
        n = ntohs(n);
        if(n > 100) {
            printf("n trebuie sa fie <= 100!\n");
            close(c);
            continue;
        }

        if(recv(c, vect, sizeof(uint16_t) * n, MSG_WAITALL) != sizeof(uint16_t) * n) {
            printf("Eroare la primirea sirului!\n");
            close(c);
            continue;
        }

        for (int i = 0; i < n; i++) {
            vect[i] = ntohs(vect[i]);
            suma += vect[i];
        }
        
        suma = htonl(suma);

        if(send(c, &suma, sizeof(suma), 0) != sizeof(suma)) {
            printf("Eroare la trimiterea sumei!\n");
            close(c);
            continue;
        }
        close(c);
    }
}
