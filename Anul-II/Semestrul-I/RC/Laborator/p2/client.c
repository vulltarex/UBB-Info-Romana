#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int c;
    struct sockaddr_in server;
    
    c = socket(AF_INET, SOCK_STREAM, 0);

    if(c < 0) {
        perror("Eroare socket");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    
    server.sin_family = AF_INET;
    server.sin_port = 1234;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(c, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Eroare connect");
        close(c);
        return 1;
    }
    
    char sir[1001];
    uint16_t len, nr_spatii;
    pritf("Sirul: ");
    if(fgets(sir,sizeof(sir), stdin) == NULL) {
        perror("Eroare la citirea sirului");
        close(c);
        return 1;
    }

    sir[strcspn(sir,"\n")] = '\0';
    len = strlen(sir);
    len = htons(len);
    send(c, &len, sizeof(len), 0);
    send(c, sir, strlen(sir), 0);

    recv(c, &nr_spatii, sizeof(nr_spatii), MSG_WAITALL);
    nr_spatii = ntohs(nr_spatii);
    printf("Numarul de spatii este %hu\n", nr_spatii);

    close(c);
    return 0;
}
