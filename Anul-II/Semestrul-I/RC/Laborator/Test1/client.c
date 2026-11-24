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
    char sir[101];
    uint16_t len;

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

    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        close(c);
        return 1;
    }

    printf("Conectat la serverul %s:%d\n", argv[1], port);
    
    printf("Introduceti sirul de caractere: ");
    if (fgets(sir, sizeof(sir), stdin) == NULL) {
        fprintf(stderr, "Nu s-a putut citi sirul\n");
        close(c);
        return 1;
    }
    size_t lungime = strcspn(sir, "\n");
    if (lungime == sizeof(sir) - 1) {
        int urmator = getchar();
        if (urmator != '\n' && urmator != EOF) {
            fprintf(stderr, "Sirul poate avea cel mult 100 de octeti\n");
            close(c);
            return 1;
        }
    }
    sir[lungime] = '\0';

    len = (uint16_t)lungime;
    uint16_t len_retea = htons(len);
    if(send(c, &len_retea, sizeof(uint16_t), 0) != sizeof(uint16_t)) {
        printf("Eroare la trimiterea dimensiunii\n");
        close(c);
        return 1;
    }

    if (len > 0 && send(c, sir, len, 0) != len) {
        printf("Eroare la trimiterea sirului\n");
        close(c);
        return 1;
    }
    
    char sir_oglindit[101];
    if (len > 0 && recv(c, sir_oglindit, len, MSG_WAITALL) != len) {
        printf("Eroare la primirea sirului oglindit\n");
        close(c);
        return 1;
    }
    sir_oglindit[len] = '\0';
    printf("%s\n", sir_oglindit);
    close(c);

    return 0;
}
