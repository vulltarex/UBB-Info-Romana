USE CubingDB;
GO

-- 1. Concurentii nascuti incepand cu 1 ianuarie 2000.

SELECT nume, prenume, data_nasterii
FROM Concurent
WHERE data_nasterii >= '2000-01-01';


-- 2. Orasele in care exista locatii pentru competitii.

SELECT DISTINCT oras
FROM Locatie;


-- 3. Competitiile la care este inscris Feliks Zemdegs.
-- relatii m:n intre concurent si competitie prin inscriere

SELECT C.nume, C.prenume, CO.denumire, I.data_inscrierii
FROM Concurent C
INNER JOIN Inscriere I ON C.id_concurent = I.id_concurent
INNER JOIN Competitie CO ON I.id_comp = CO.id_comp
WHERE C.nume = 'Zemdegs' AND C.prenume = 'Feliks';


-- 4. Probele organizate la Bucharest Cube Open 2025.
-- relatie m:n prin proba si competitie prin ProbaCompetitie

SELECT CO.denumire AS competitie, P.denumire AS proba
FROM Competitie CO
INNER JOIN ProbaCompetitie PC ON CO.id_comp = PC.id_comp
INNER JOIN Proba P ON PC.id_proba = P.id_proba
WHERE CO.denumire = 'Bucharest Cube Open 2025';


-- 5. Orasele competitiilor la care este inscris Feliks.

SELECT DISTINCT L.oras
FROM Concurent C
INNER JOIN Inscriere I ON C.id_concurent = I.id_concurent
INNER JOIN Competitie CO ON I.id_comp = CO.id_comp
INNER JOIN Locatie L ON CO.id_locatie = L.id_locatie
WHERE C.nume = 'Zemdegs' AND C.prenume = 'Feliks';


-- 6. Rundele finale, impreuna cu proba si competitia.

SELECT CO.denumire AS competitie,
       P.denumire AS proba,
       R.nr_runda,
       R.denumire AS runda
FROM Competitie CO
INNER JOIN ProbaCompetitie PC ON CO.id_comp = PC.id_comp
INNER JOIN Proba P ON PC.id_proba = P.id_proba
INNER JOIN Runda R ON PC.id_proba_comp = R.id_proba_comp
WHERE R.denumire = 'Finala';


-- 7. Competitiile cu cel putin 5 concurenti inscrisi.

SELECT CO.denumire, COUNT(C.id_concurent) AS numar_concurenti
FROM Competitie CO
INNER JOIN Inscriere I ON CO.id_comp = I.id_comp
INNER JOIN Concurent C ON I.id_concurent = C.id_concurent
GROUP BY CO.id_comp, CO.denumire
HAVING COUNT(C.id_concurent) >= 5;


-- 8. Concurentii inscrisi la cel putin doua competitii.

SELECT C.nume, C.prenume, COUNT(CO.id_comp) AS numar_competitii
FROM Concurent C
INNER JOIN Inscriere I ON C.id_concurent = I.id_concurent
INNER JOIN Competitie CO ON I.id_comp = CO.id_comp
GROUP BY C.id_concurent, C.nume, C.prenume
HAVING COUNT(CO.id_comp) >= 2;


-- 9. Cel mai bun timp inregistrat la fiecare tip de proba, luand in calcul toate competitiile si rundele.

SELECT P.denumire AS proba,
       MIN(IC.timp_ms) / 1000.0 AS timp_minim_secunde
FROM Proba P
INNER JOIN ProbaCompetitie PC ON P.id_proba = PC.id_proba
INNER JOIN ParticipareProba PP ON PC.id_proba_comp = PP.id_proba_comp
INNER JOIN Incercare IC ON PP.id_participare = IC.id_participare
GROUP BY P.id_proba, P.denumire;


-- 10. Incercarile sub 6 secunde la proba 3x3x3 Speed.

SELECT C.nume,
       C.prenume,
       P.denumire AS proba,
       IC.nr_incercare,
       IC.timp_ms / 1000.0 AS timp_secunde
FROM Concurent C
INNER JOIN Inscriere I ON C.id_concurent = I.id_concurent
INNER JOIN ParticipareProba PP ON I.id_inscriere = PP.id_inscriere
INNER JOIN ProbaCompetitie PC ON PP.id_proba_comp = PC.id_proba_comp
INNER JOIN Proba P ON PC.id_proba = P.id_proba
INNER JOIN Incercare IC ON PP.id_participare = IC.id_participare
WHERE P.denumire = '3x3x3 Speed' AND IC.timp_ms < 6000;