REȚEA DE SOCIALIZARE - LABORATORUL 5
===================================

1. PORNIRE ȘI CONFIGURARE

Proiectul suportă rulare atât prin Gradle (build.gradle.kts), cât și din IntelliJ IDEA.
Driverul JDBC PostgreSQL este org.postgresql:postgresql:42.7.7.

Configurația se află în src/main/resources/config.properties:
- repository.type=DATABASE (sau FILE, MEMORY)
- db.url=jdbc:postgresql://localhost:5432/socialnetwork
- db.user=postgres
- db.password=parola_ta

Pentru securitate, config.properties (conținând parola reală) este inclus în .gitignore,
iar config.example.properties este furnizat ca șablon.

Scriptul de inițializare a tabelelor se află în schema.sql:
    users (id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY, first_name VARCHAR NOT NULL, last_name VARCHAR NOT NULL)
    friendships (id1 BIGINT, id2 BIGINT, friends_from TIMESTAMP NOT NULL, PRIMARY KEY(id1, id2), CHECK(id1 < id2), FK cascade)

Comenzi rapide:
    ./gradlew run     (sau rulare Main din IntelliJ)
    sh scripts/javadoc.sh (generare Javadoc în docs/javadoc/)


2. JUSTIFICARE: ON DELETE CASCADE vs. ȘTERGERE EXPLICITĂ ÎN SERVICE (0.5p)

În schema bazei de date PostgreSQL, tabelele folosesc:
    CONSTRAINT fk_friendship_user1 FOREIGN KEY (id1) REFERENCES users(id) ON DELETE CASCADE,
    CONSTRAINT fk_friendship_user2 FOREIGN KEY (id2) REFERENCES users(id) ON DELETE CASCADE

Justificarea acestei alegeri:
1. Integritate referențială la nivel de stocare (Database-Level Integrity):
   Definirea ON DELETE CASCADE în baza de date garantează că indiferent de sursa comenzii de ștergere
   (aplicația Java, scripturi SQL externe, pgAdmin sau viitoare microservicii), baza de date nu va
   rămâne niciodată cu înregistrări orfane în friendships și nu va genera erori de constrângere
   foreign key. Operațiunea este executată atomic de către motorul PostgreSQL.

2. Păstrarea decuplării în Service (Service-Level Fallback):
   În UserServiceImpl.deleteUser s-a păstrat ștergerea prieteniilor asociate înainte de ștergerea
   utilizatorului. Această abordare permite ca același Service să funcționeze identic și corect
   indiferent de backend-ul configurat în config.properties (pentru MEMORY și FILE, unde nu există
   un motor relațional cu suport pentru CASCADE). Astfel, arhitectura rămâne agnostic la persistență.


3. GENERAREA AUTOMATĂ A ID-ULUI (1p)

- Generarea ID-urilor este acum responsabilitatea stocării, nu a Service-ului.
- PostgreSQL generează automat cheia primară prin GENERATED ALWAYS AS IDENTITY.
- În UserDbRepository.save(entity), inserarea se realizează cu Statement.RETURN_GENERATED_KEYS.
  ID-ul generat de baza de date este extras din ResultSet (rs.getLong(1)) și setat pe entitate
  (entity.setId(...)).
- În modurile MEMORY și FILE, repository-urile concrete generează ID-ul următor la salvare
  dacă entity.getID() este null.
- În consolă (ConsoleUI, opțiunea 1), după adăugarea utilizatorului se afișează ID-ul primit
  de la baza de date ("Utilizator adaugat cu ID-ul: ...").


4. IMPLEMENTAREA REPOSITORY-URILOR JDBC (4p)

UserDbRepository și FriendshipDbRepository implementează contractele Repository<ID, E>:
- Conexiunea se obține prin DriverManager.getConnection(url, user, password).
- Connection, PreparedStatement și ResultSet sunt gestionate strict în blocuri try-with-resources.
- Toate comenzile folosesc PreparedStatement cu parametri ? (fără concatenare SQL).
- Respectarea strictă a contractului Repository:
  * findOne(id) întoarce entitatea sau null dacă lipsește; argument null -> IllegalArgumentException.
  * findAll() returnează un Iterable cu toate entitățile din tabel.
  * save(entity) validează entitatea înainte de inserare; returnează null la salvare reușită
    sau entitatea dacă exista deja.
  * delete(id) returnează entitatea ștearsă (sau null dacă nu exista); argument null -> IllegalArgumentException.
  * update(entity) validează entitatea înainte de actualizare; dacă ID-ul este inexistent
    (executeUpdate() întoarce 0 rânduri afectate), returnează entitatea primită;
    dacă actualizarea a reușit, returnează null.


5. TRATAREA EXCEPȚIILOR (1.5p)

- SQLException este interceptată în DbExceptionHelper și împachetată în RepositoryException.
- Se analizează codurile SQLState și mesajele de eroare:
  * SQLState 08xxx sau Connection Refused -> "Serverul bazei de date este oprit sau inaccesibil."
  * SQLState 23xxx (23505 unique_violation, 23503 foreign_key, 23514 check) ->
    "Constrangere de integritate incalcata in baza de date (date duplicate sau invalide)."
  * SQLState 28xxx -> "Autentificarea la baza de date a esuat (utilizator sau parola incorecta)."
- În UI (ConsoleUI):
  * Fără e.printStackTrace() / fără stack trace afișat utilizatorului.
  * Fără blocuri catch goale.
  * Fără catch generic (Exception e). UI prinde explicit excepțiile așteptate
    (ValidationException | ServiceException | RepositoryException | IllegalArgumentException | UnsupportedOperationException).


6. DEMONSTRAȚIE LA PREDARE (1p)

1. CRUD în pgAdmin:
   Se adaugă, listează, modifică și șterg utilizatori și prietenii din consolă;
   se verifică sincronizarea în tabelele users și friendships din pgAdmin.
2. ID generat automat:
   La adăugarea unui utilizator (opțiunea 1), aplicația afișează ID-ul generat de PostgreSQL.
3. Persistența la repornire:
   Datele adăugate rămân în PostgreSQL după oprirea și repornirea aplicației.
4. Schimbarea repository.type:
   Comutarea între DATABASE, FILE și MEMORY se realizează modificând doar repository.type
   în config.properties, fără recompilare sau modificare de cod.
5. Server PostgreSQL oprit:
   Se oprește serviciul PostgreSQL și se pornește / execută o operație în aplicație.
   Aplicația raportează curat: "Serverul bazei de date este oprit sau inaccesibil." fără stack trace.
6. Test SQL Injection:
   La adăugarea unui utilizator cu prenumele:
       '); DROP TABLE users; --
   și orice nume de familie, aplicația salvează valoarea ca text simplu în baza de date.
   Tabela users NU este ștearsă datorită utilizării PreparedStatement cu parametri.
