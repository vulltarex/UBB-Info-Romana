#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Definim o structură simplă pentru a trimite atomic datele prin pipe
typedef struct {
    int row;
    int col;
} Position;

int main(int argc, char *argv[]) {
    // 1. Validarea argumentelor
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <M> <N> <X>\n", argv[0]);
        return 1;
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int X = atoi(argv[3]);

    // 2. Alocarea dinamică a matricei (pentru a evita memory leaks, trebuie eliberată)
    int **matrix = malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++) {
        matrix[i] = malloc(N * sizeof(int));
    }

    // 3. Citirea fișierului
    FILE *fin = fopen("matrix.txt", "r");
    if (!fin) {
        perror("Error opening matrix.txt");
        // Eliberăm memoria înainte de a ieși în caz de eroare
        for(int i=0; i<M; i++) free(matrix[i]);
        free(matrix);
        return 1;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fin, "%d", &matrix[i][j]);
        }
    }
    fclose(fin);

    // 4. Crearea Pipe-ului (înainte de fork!)
    int pfd[2];
    if (pipe(pfd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // 5. Crearea a M procese copil
    for (int i = 0; i < M; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0) { // ================= COPIL =================
            // Copilul doar SCRIE în pipe, deci închidem capătul de citire
            close(pfd[0]); 

            // Căutăm valoarea X pe linia 'i' (linia alocată acestui copil)
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] == X) {
                    Position pos = {i, j};
                    // Trimitem structura direct prin pipe
                    write(pfd[1], &pos, sizeof(Position));
                }
            }

            // Foarte important: închidem capătul de scriere când am terminat!
            close(pfd[1]);

            // Copilul are o copie a întregii memorii (inclusiv matricea).
            // Trebuie să o elibereze pentru a nu supăra Valgrind-ul!
            for (int r = 0; r < M; r++) free(matrix[r]);
            free(matrix);
            
            exit(0); // Ieșim din copil. Nu vrem ca acesta să continue execuția!
        }
    }

    // ================= PĂRINTE =================
    
    // Părintele doar CITEȘTE. Trebuie să închidă capătul lui de scriere IMEDIAT.
    // Dacă nu face asta, read() se va bloca la infinit așteptând date (pentru că părintele ține un write deschis).
    close(pfd[1]);

    FILE *fout = fopen("output.txt", "w");
    if (!fout) {
        perror("Error opening output.txt");
        return 1;
    }

    Position current_pos;
    int found_count = 0;

    // read() va returna > 0 atâta timp cât copiii trimit date.
    // Când TOȚI copiii termină și închid pfd[1], read() va returna 0 (EOF) și bucla se va opri.
    while (read(pfd[0], &current_pos, sizeof(Position)) > 0) {
        fprintf(fout, "Found at: %d %d\n", current_pos.row, current_pos.col);
        found_count++;
    }

    // Cerința: dacă nu a fost găsit X deloc
    if (found_count == 0) {
        fprintf(fout, "Value not found\n");
    }

    // Curățenie părinte
    fclose(fout);
    close(pfd[0]); // Închidem capătul de citire

    // Evitarea proceselor Zombie: Așteptăm exact M copii să termine.
    for (int i = 0; i < M; i++) {
        wait(NULL);
    }

    // Eliberăm memoria alocată dinamic în părinte
    for (int i = 0; i < M; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
