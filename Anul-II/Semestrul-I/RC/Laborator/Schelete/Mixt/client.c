// Rulare: ./client 127.0.0.1 5000 127.0.0.1
// Argumente: IP server, port TCP server, IP local accesibil serverului.
// TCP: trimite IP-ul si portul UDP. Apoi: mesaje UDP pana la STOP.
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int c, u, port;
    struct sockaddr_in server, local, server_udp, sursa;
    socklen_t l;
    char mesaj[101];

    if (argc != 4) {
        printf("Utilizare: %s <ip_server> <port_tcp> <ip_local>\n", argv[0]);
        return 1;
    }

    port = atoi(argv[2]);
    if (port < 1 || port > 65535) {
        printf("Port invalid\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(0); // sistemul alege un port UDP liber

    if (inet_pton(AF_INET, argv[1], &server.sin_addr) != 1 ||
        inet_pton(AF_INET, argv[3], &local.sin_addr) != 1) {
        printf("Adresa IP invalida\n");
        return 1;
    }

    // Pregatim UDP INAINTE sa anuntam adresa prin TCP.
    u = socket(AF_INET, SOCK_DGRAM, 0);
    if (u < 0) {
        perror("socket UDP");
        return 1;
    }
    if (bind(u, (struct sockaddr *) &local, sizeof(local)) < 0) {
        perror("bind UDP");
        close(u);
        return 1;
    }
    l = sizeof(local);
    if (getsockname(u, (struct sockaddr *) &local, &l) < 0) {
        perror("getsockname");
        close(u);
        return 1;
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        perror("socket TCP");
        close(u);
        return 1;
    }
    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connect");
        close(c);
        close(u);
        return 1;
    }

    // Protocol TCP: 4 octeti IPv4 + 2 octeti port, deja in network order.
    unsigned char date[6];
    memcpy(date, &local.sin_addr.s_addr, 4);
    memcpy(date + 4, &local.sin_port, 2);
    signal(SIGPIPE, SIG_IGN);
    size_t trimis = 0;
    while (trimis < sizeof(date)) {
        ssize_t n = send(c, date + trimis, sizeof(date) - trimis, 0);
        if (n < 0 && errno == EINTR) continue;
        if (n <= 0) {
            printf("Eroare la trimiterea adresei UDP\n");
            close(c);
            close(u);
            return 1;
        }
        trimis += (size_t)n;
    }
    close(c); // de aici comunicam doar prin UDP

    printf("Portul meu UDP: %hu\n", ntohs(local.sin_port));
    int primul = 1;
    memset(&server_udp, 0, sizeof(server_udp));

    while (1) {
        l = sizeof(sursa);
        ssize_t n = recvfrom(u, mesaj, sizeof(mesaj) - 1, 0,
                            (struct sockaddr *) &sursa, &l);
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("recvfrom");
            break;
        }
        if (sursa.sin_addr.s_addr != server.sin_addr.s_addr) continue;
        if (primul) {
            server_udp = sursa; // primul mesaj ne da portul UDP al fiului
            primul = 0;
        }
        if (sursa.sin_port != server_udp.sin_port) continue;

        mesaj[n] = '\0';
        printf("Server: %s\n", mesaj);
        if (strcmp(mesaj, "STOP") == 0) break;

        // Aici adaptezi logica jocului. Momentan trimitem text de la tastatura.
        printf("Mesaj (STOP pentru iesire): ");
        if (fgets(mesaj, sizeof(mesaj), stdin) == NULL) {
            strcpy(mesaj, "STOP");
        }
        mesaj[strcspn(mesaj, "\n")] = '\0';

        if (sendto(u, mesaj, strlen(mesaj), 0,
                   (struct sockaddr *) &server_udp, sizeof(server_udp)) < 0) {
            perror("sendto");
            break;
        }
        if (strcmp(mesaj, "STOP") == 0) break;
    }

    close(u);
    return 0;
}
