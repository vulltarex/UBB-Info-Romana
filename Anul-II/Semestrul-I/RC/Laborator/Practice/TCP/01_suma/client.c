#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int c;
    struct sockaddr_in server;
    int port;
    uint16_t n, vect[100];
    uint32_t suma;

    if(argc != 3) {
        printf("Utilizare: %s <ip_server> <port_server>\n", argv[0]);
        return 1;
    }

    port = atoi(argv[2]);
    if(port < 1 || port > 65535) {
        printf("Port invalid: %s (trebuie sa fie intre 1 si 65535)\n", argv[2]);
        return 1;
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if(c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;

    if(inet_pton(AF_INET, argv[1], &server.sin_addr) != 1) {
        printf("Adresa IP invalida: %s", argv[1]);
        close(c);
        return 1;
    }
    
    printf("Introduceti numarul de elemente: ");
    scanf("%hu", &n);
    for (int i = 0; i < n; i++) {
        printf("Introduceti elementul %d: ", i);
        scanf("%hu", &vect[i]);
        vect[i] = htons(vect[i]);
    }
    uint16_t n_retea = htons(n);
    


    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        close(c);
        return 1;
    }

    printf("Conectat la serverul %s:%d\n", argv[1], port);
    if(send(c, &n_retea, sizeof(n), 0) != sizeof(n)) {
        printf("Eroare la trimiterea lungimii!\n");
        close(c);
        return 1;
    }
    if(send(c, vect, sizeof(uint16_t) * n, 0) != sizeof(uint16_t) * n) {
        printf("Eroare la trimiterea sirului!\n");
        close(c);
        return 1;
    }
    
    if(recv(c, &suma, sizeof(uint32_t), 0) != sizeof(uint32_t)) {
        printf("Eroare la primirea sumei!\n");
        close(c);
        return 1;
    }

    suma = ntohl(suma);
    printf("Suma sirului este: %u\n", suma);
    

    close(c);
}
