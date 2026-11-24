// Rulare: ./server 5000
// Un proces fiu per client; fiecare fiu are propriul socket UDP.
// Serverul trimite START, apoi raspunde cu mesajul primit (echo).
#define _POSIX_C_SOURCE 200809L
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

void deservire(int c) {
    struct sockaddr_in client, local, sursa;
    socklen_t l;
    char mesaj[101];

    // Primim exact 6 octeti TCP. Un singur recv poate primi mai putin.
    unsigned char date[6];
    size_t primit = 0;
    while (primit < sizeof(date)) {
        ssize_t n = recv(c, date + primit, sizeof(date) - primit, 0);
        if (n < 0 && errno == EINTR) continue;
        if (n <= 0) {
            printf("Client deconectat sau eroare la primirea adresei UDP\n");
            close(c);
            return;
        }
        primit += (size_t)n;
    }
    close(c);

    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    memcpy(&client.sin_addr.s_addr, date, 4);
    memcpy(&client.sin_port, date + 4, 2);
    // IP-ul si portul sunt deja in network order: nu le convertim din nou.
    if (client.sin_port == 0) return;

    int u = socket(AF_INET, SOCK_DGRAM, 0);
    if (u < 0) {
        perror("socket UDP");
        return;
    }

    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = htons(0); // un port UDP liber pentru acest fiu
    if (bind(u, (struct sockaddr *) &local, sizeof(local)) < 0) {
        perror("bind UDP");
        close(u);
        return;
    }

    strcpy(mesaj, "START"); // serverul trimite primul mesaj
    while (1) {
        if (sendto(u, mesaj, strlen(mesaj), 0,
                   (struct sockaddr *) &client, sizeof(client)) < 0) {
            perror("sendto");
            break;
        }
        if (strcmp(mesaj, "STOP") == 0) break;

        ssize_t n;
        // Ignoram mesajele care nu apartin clientului acestui fiu.
        do {
            l = sizeof(sursa);
            n = recvfrom(u, mesaj, sizeof(mesaj) - 1, 0,
                         (struct sockaddr *) &sursa, &l);
        } while ((n < 0 && errno == EINTR) ||
                 (n >= 0 && (sursa.sin_addr.s_addr != client.sin_addr.s_addr ||
                             sursa.sin_port != client.sin_port)));

        if (n < 0) {
            perror("recvfrom");
            break;
        }
        mesaj[n] = '\0';
        if (strcmp(mesaj, "STOP") == 0) break;

        // Prelucrare mesaj / reguli joc.
        // Momentan mesajul ramane identic si este trimis la urmatorul tur.
    }

    close(u);
}

int main(int argc, char *argv[]) {
    int s, c, port;
    struct sockaddr_in server;

    if (argc != 2) {
        printf("Utilizare: %s <port_tcp>\n", argv[0]);
        return 1;
    }
    port = atoi(argv[1]);
    if (port < 1 || port > 65535) {
        printf("Port invalid\n");
        return 1;
    }

    // Sistemul recupereaza automat fiii terminati (fara procese zombie).
    struct sigaction sa = {0};
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = SA_NOCLDWAIT;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGCHLD, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket TCP");
        return 1;
    }
    int opt = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(s);
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind TCP");
        close(s);
        return 1;
    }
    if (listen(s, 5) < 0) {
        perror("listen");
        close(s);
        return 1;
    }

    printf("Se asteapta conexiuni TCP pe portul %d...\n", port);
    while (1) {
        c = accept(s, NULL, NULL);
        if (c < 0) {
            if (errno != EINTR) perror("accept");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            close(c);
            continue;
        }
        if (pid == 0) {
            close(s); // fiul nu mai accepta conexiuni
            deservire(c); // inchide c dupa primirea datelor TCP
            _exit(0);
        }
        close(c); // parintele revine la accept
    }
}
