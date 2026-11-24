# MAP: Metode avansate de programare

Anul II, semestrul 1 · **Java, Gradle, PostgreSQL (JDBC)**

## Proiectul de laborator

Un singur proiect, **Rețea de socializare**, extins de la un laborator la altul:

Lab2 domeniu și memorie → Lab3 fișiere și Factory → Lab4 refactorizare Java 8 → Lab5 PostgreSQL/JDBC → Lab6 paginare → Lab7 JavaFX

## Conținut

| Folder | Ce găsești |
|---|---|
| `Laborator/Lab1` | numere complexe (separat de proiect), cu diagramă UML |
| `Laborator/Lab3` | proiectul cumulat, Lab2–Lab6: JDBC în `src/repository/db/`, paginare în `src/util/paging/` |
| `Seminar/seminar1`, `seminar3`, `seminar4exercitii` | Task/MessageTask, colecții și generics, excepții și I/O |
| `Seminar/curs3_handson` | exemplul de la curs 3: Template Method, Factory |
| `Seminar/Seminar6` | Stream API |
| `Seminar/Seminar7-start`, `Seminar8-TODOs` | JDBC și paginare (Cinema/Movie) |

## Rulare (Lab3)

1. Copiază `config.example.properties` în `config.properties` și completează datele de conectare. Fișierul `config.properties` nu se publică.
2. Creează baza de date cu `schema.sql`.
3. Rulează:

```bash
./gradlew run
```
