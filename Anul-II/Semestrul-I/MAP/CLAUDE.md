# MAP: harta materiei

Se încarcă doar când lucrezi în `MAP/`. Pornește de aici în loc să recitești toate PDF-urile.
Paginile se referă la PDF-uri. Progresul pe concepte e în `progress.md`.

## Proiectul de laborator
Un singur proiect, **Rețea de socializare** (`Laborator/Cerinte/Enunt Proiect Lab - Retea de socializare.pdf`), extins lab cu lab:
Lab2 domeniu + memorie → Lab3 fișier + Factory → Lab4 refactorizare Java 8 → Lab5 PostgreSQL/JDBC → Lab6 paginare → Lab7 JavaFX.
Lab1 e separat (numere complexe).

**Codul meu în folder:**
- `Laborator/Lab1/`
- `Laborator/Lab3/` conține proiectul cumulat pentru **Lab2–Lab6**. JDBC e în `src/repository/db/`, paginarea în `src/util/paging/`.
- Lab7 (JavaFX) e de făcut, cu termen în săptămâna 10.

Lab6 a fost generat cu AI, deci e o zonă de recuperat.

**Cod de seminar:** `Seminar/seminar1`, `seminar3`, `seminar4exercitii`, `curs3_handson`, `Seminar6`, `Seminar7-start`, `Seminar8-TODOs`.

## Harta: concept → curs → seminar → laborator

| # | Concepte | Curs | Seminar | Lab |
|---|---|---|---|---|
| 1 | Principii de proiectare, SOLID (SRP, OCP, LSP, ISP, DIP) | `curs1.pdf` p2–8 | Sem 1+2 | Lab1 (readme cu SOLID) |
| 2 | Java de bază: tipuri, tablouri, clase, constructori, `this`, overloading, `static`, wrapper-e | `curs1.pdf` p13–44 | – | Lab1 |
| 3 | Moștenire, `super`, `Object`, overriding, legare dinamică, up/downcast, `final` | `curs1.pdf` p45–57 | Sem 1+2 (Task, MessageTask) | Lab1 |
| 4 | Compunere vs moștenire, asociere/agregare/compoziție | `curs1.pdf` p58–66 | Sem 3 (MyMap: „Favor composition”) | – |
| 5 | Clase abstracte, interfețe (inclusiv `default`) | `curs1.pdf` p67–75, `curs2.pdf` p2 | Sem 1+2 (Container, TaskRunner) | Lab1 |
| 6 | Șabloane: Strategy, Factory Method, Decorator, Extract Superclass | `curs1.pdf` (doar referințe) | Sem 1+2 p1–3 | Lab1, Lab2 (Strategy la validare) |
| 7 | Singleton (eager, lazy) | `Curs3.pdf` p2–4 | Sem 1+2 | – |
| 8 | Generics: clase și metode generice, erasure, bounded, wildcards | `curs2.pdf` p3–25 | Sem 3 (Repository0 generic) | Lab2, Lab3 (`AbstractFileRepository<ID, E>`) |
| 9 | Colecții: `List`, `Set`, `Map`, iteratori, `Collections` | `curs2.pdf` p26–38, p44 | Sem 3 | Lab2 |
| 10 | Contractul `equals`/`hashCode`, `Comparable`, `Comparator` | `curs2.pdf` p37, p39–43 | Sem 3 cerințele 2–5 | Lab3 (Entity, Tuple) |
| 11 | Repository CRUD + contract Javadoc, `InMemoryRepository` | – | Sem 3 cerințele 7–8 | Lab2 |
| 12 | Arhitectură stratificată, DDD, validare (Strategy) | – | Sem 4 (după Lab2) | Lab2 |
| 13 | Excepții: ierarhia `Throwable`, checked/unchecked, `throw`/`throws`, try-catch-finally, propagare, excepții proprii (`ValidatorException`), excepții la overriding | `Curs3.pdf` p5–17 | Sem 4 exerciții | Lab2, Lab3 |
| 14 | I/O: fluxuri pe octeți și pe caractere, try-with-resources, decoratori (`Buffered*`, `Data*`), `BufferedReader`/`BufferedWriter`, `Scanner` | `Curs3.pdf` p18–42 (try-with-resources p25, decoratori p26–30) | Sem 4 exerciții | Lab3 |
| 15 | Serializare: `Serializable`, `serialVersionUID`, `transient` | `Curs3.pdf` p44–47 | – | – |
| 16 | NIO/NIO.2: `Path`, `Paths`, `Files` (+ `Files.lines` cu stream) | `Curs3.pdf` p48–53, `Curs4-5_IF_stream.pdf` p42 | – | Lab3, Lab4 |
| 17 | Template Method (`AbstractFileRepository`), `instanceof`, exception chaining | Curs 3 hands-on (`Seminar/curs3_handson`), nu e în slide-uri | Sem 4 | Lab3 |
| 18 | Simple Factory, `enum`, `config.properties`, `getResourceAsStream` | – | Sem 4 Factory, cerințele 4–6 | Lab3 |
| 19 | Metode `default`/`static` în interfețe, interfețe funcționale | `Curs4-5_IF_stream.pdf` p2–5, `Curs5_InterfeteFunctionale_rezumat.pdf` | Sem 5 încălzire, cerința 7 | Lab4 |
| 20 | Lambda, target type, effectively final, `this` în lambda | `Curs4-5` p10–14 | Sem 5 cerința 7 | Lab4 |
| 21 | Referințe la metode (cele 4 tipuri) | `Curs4-5` p6–9 | Sem 5 cerința 9 întrebarea 4 | Lab4 |
| 22 | `Predicate`, `Function`, `Consumer`, `Supplier`, `UnaryOperator`, `BinaryOperator`, `Comparator.comparing` | `Curs4-5` p15–29 | Sem 5 cerințele 8–10 | Lab4 |
| 23 | `forEach`, `removeIf`, `ConcurrentModificationException` | `Curs4-5` p20–21 | Sem 5 cerința 8 întrebarea 6 | Lab4 |
| 24 | `Optional` | `Curs4-5` p30–32 | Sem 7 (findOne) | Lab4, Lab5 |
| 25 | Stream API: intermediar vs terminal, `filter`, `map`, `flatMap`, `reduce`, `collect`, `groupingBy` | `Curs4-5` p33–41, `Curs5_Streams_rezumat.pdf` | Sem 6 (rapoarte Student/Tema/Nota), Sem 7 cerința 6 | Lab4 |
| 26 | Git | Curs 4 (nu e în folder) | – | Lab4+ (cerință de predare) |
| 27 | JDBC: `Connection`, `PreparedStatement`, `ResultSet`, id generat, SQL injection | `Curs6_PersistentaDB_rezumat_simplu_cod.pdf` p1–3 | Sem 7 (Cinema) | Lab5 (`src/repository/db/`) |
| 28 | Paginare și sortare în SQL (`LIMIT`/`OFFSET`, `count`), `record`, listă albă de coloane | **curs lipsă** | Sem 8 (Movie) | Lab6 (`src/util/paging/`) |
| 29 | JavaFX: FXML, controllere, MVC, Observer | **curs lipsă**, `Seminar/Tutorial_CSS_JavaFX.pdf` | proiect demo de la seminar (lipsă) | Lab7 |

**Lipsesc din folder:** Curs 4 (Git) și cursurile pentru paginare și JavaFX. Dacă un concept depinde de ele, spune-mi.

## Restricții de implementare
Java 8, colecțiile generice, lambda și stream-urile sunt permise în orice exercițiu.
Restricțiile de mai jos rămân pentru exercițiile pe etapa respectivă:
- **Lab3:** fișiere text fără biblioteci externe; căi relative; excepțiile se prind doar în UI, fără `catch (Exception e)`.
- **Lab5:** `PreparedStatement` cu `?`, try-with-resources pentru toate resursele, `SQLException` → `RepositoryException`.
- **Lab6:** paginarea în SQL, nu în Java; UI fără SQL.
- **Lab7:** controllerele apelează doar service-ul; mesajele de eroare prin `MessageAlert`.

## Stilul exercițiilor din materie
- **Seminar:** „Cerința N” cu enunț scurt → *(axa de schimbare: …)* → „Întrebări” de tip „de ce / ce se întâmplă dacă”, cu răspuns. Domenii folosite: TaskRunner, Student/Tema/Nota, figuri (Cerc/Pătrat), Cinema/Film/Movie.
- **Laborator:** cerințe funcționale și non-funcționale cu punctaj, restricții de implementare, „Sugestii și observații” cu capcane, readme cu justificări, demonstrație la predare.
- Codul folosește denumiri în română (`Utilizator`, `Prietenie`, `CriteriiUtilizator`) și Javadoc în engleză.

## Capcane subliniate de materie (bune pentru exerciții)
- `super.save(...)` la încărcarea din fișier; nu apelezi metode suprascrise din constructor (Effective Java, Item 19). (Lab3)
- `split(";", -1)`; `split` primește regex. Prietenia (1,2) = (2,1): normalizezi id-urile. (Lab3)
- `equals` tratează `null` și alt tip; contractul cu `hashCode`. (Sem 3, Lab3)
- Excepțiile doar pentru situații excepționale (Item 57); metoda suprascrisă nu poate arunca excepții checked noi. (`Curs3.pdf` p5, p17)
- Mai multe `catch`, grupate pe tipuri (`Curs3.pdf` p14); ordinea lor, de la specific la general. (Sem 4 exerciții)
- Fluxurile se închid: try-with-resources cere `AutoCloseable`. (`Curs3.pdf` p25)
- Fall-through în `switch`; `default` necesar pentru compilare. (Sem 4)
- `comparingInt(...).reversed()` nu deduce tipul; `(a, b) -> a - b` dă overflow. (Sem 5, Lab4)
- Un stream se consumă o dată; `forEach` cu efecte secundare în loc de `collect`; `Files.lines` în try-with-resources. (Lab4)
- `andThen` nu e comutativ; `Supplier` amână crearea (lazy). (Sem 5)
- `ORDER BY ?` nu merge, numărul de pagini se rotunjește în sus. (Sem 8)
