#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    struct sockaddr_in server;
    char s1[256], s2[256], rez[512];
    uint16_t len1, len2, len_rez;

    // Verificam daca utilizatorul a introdus adresa IP la pornire
    if (argc != 2) {
        printf("Utilizare: %s <Adresa_IP_Server>\n", argv[0]);
        return 1;
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    
    // Setam adresa IP pe baza argumentului primit din terminal
    server.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la serverul %s\n", argv[1]);
        return 1;
    }

    printf("Introduceti primul sir ordonat: ");
    scanf("%255s", s1);
    len1 = strlen(s1);

    printf("Introduceti al doilea sir ordonat: ");
    scanf("%255s", s2);
    len2 = strlen(s2);

    uint16_t len1_net = htons(len1);
    send(c, &len1_net, sizeof(len1_net), 0);
    send(c, s1, len1, 0);

    uint16_t len2_net = htons(len2);
    send(c, &len2_net, sizeof(len2_net), 0);
    send(c, s2, len2, 0);

    recv(c, &len_rez, sizeof(len_rez), MSG_WAITALL);
    len_rez = ntohs(len_rez);
    recv(c, rez, len_rez, MSG_WAITALL);
    rez[len_rez] = '\0';

    printf("Sirul interclasat primit de la server este: %s\n", rez);

    close(c);
    return 0;
}
