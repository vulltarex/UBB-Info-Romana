#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int s, c;
    struct sockaddr_in server, client;
    socklen_t l;

    s = socket(AF_INET, SOCK_STREAM, 0);

    if(s < 0) {
        perror("Eroare socket");
        return 1;
    }

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = 1234;
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Eroare bind");
        close(s);
        return 1;
    }

    if(listen(s,5) < 0) {
        perror("Eroare listen");
        close(s);
        return 1;
    }

    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    printf("Server pornit pe portul 1234\n");

    while(1) {
        c = accept(s, (struct sockaddr*)&client, &l);

        if (c < 0) {
            perror("Eroare accept");
            continue;
        }

        printf("S-a conectat un client");
        
        uint16_t len, nr_spatii;
        char* sir;
        int i;

        if(recv(c, &len, sizeof(len), MSG_WAITALL) != sizeof(len)) {
            perror("Eroare la primirea lungimii");
            close(c);
            continue;
        }

        len = ntohs(len);

        sir = (char*)malloc(len+1);
        if(sir == NULL) {
            perror("eroare la alocarea sirului");
            close(c);
            continue;
        }

        if(len > 0 && recv(c, sir, len, MSG_WAITALL) != len) {
            perror("eroare la primirea sirului\n");
            free(sir);
            close(c);
            continue;
        }

        sir[len] = '\0';

        nr_spatii = 0;
        for (i = 0; i < len; i++) {
            if(sir[i] == ' ') {
                nr_spatii++;
            }
        }
        printf("Sir primit: \"%s\" -> %hu spatii\n", sir, nr_spatii);

        nr_spatii = htons(nr_spatii);
        send(c, &nr_spatii, sizeof(nr_spatii), 0);

        free(sir);
        close(c);
    }
}
        
