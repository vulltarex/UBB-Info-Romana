LABORATOR 1 - MAP: EXPRESII CU NUMERE COMPLEXE

1. Scop si functionare
Programul primeste prin argumentele liniei de comanda o expresie de forma
n1 op n2 op ... op nk, cu minimum doua numere complexe si acelasi operator
(+, -, *, /). Numerele au forma a+b*i; sunt acceptate zecimale si formele
a+i, a-i. Dupa validare, expresia se calculeaza de la stanga la dreapta.
Se afiseaza rezultatul sau mesajul "Expresie incorecta!".
Se folosesc tablouri simple, fara colectii generice, lambda sau stream-uri.
Limitare asumata a versiunii curente: numarul complex zero este respins la
intrare, desi cerinta nu impune aceasta restrictie; rezultatul poate fi zero.

2. Organizarea proiectului
- ComplexNumber: pastreaza partile reala si imaginara (double, final) si
  asigura afisarea numarului.
- ComplexNumberParser / StandardComplexParser: contractul si implementarea
  validarii si transformarii textului intr-un numar complex.
- Operation: contractul apply(a, b); AddOperation, SubtractOperation,
  MultiplyOperation si DivideOperation implementeaza calculele.
- OperationFactory: creeaza operatia corespunzatoare simbolului primit.
- ExpressionValidator: verifica numarul argumentelor, alternanta dintre
  numere si operatori, validitatea numerelor si identitatea operatorilor.
- ExpressionEvaluator: aplica succesiv operatia asupra numerelor parsate.
- Main: creeaza componentele, solicita validarea si afiseaza rezultatul.

3. Principii SOLID si reflectarea lor in UML
- SRP (responsabilitate unica): reprezentarea datelor, parsarea, validarea
  expresiei, calculul si crearea operatiilor sunt separate in clase distincte.
  UML evidentiaza aceste responsabilitati prin clasele si metodele lor.
- OCP (deschis pentru extindere, inchis pentru modificare): evaluatorul poate
  folosi alte implementari Operation si ComplexNumberParser fara modificari.
  Extinderea listei de operatori necesita totusi actualizarea fabricii si a
  validatorului; principiul nu este aplicat integral la nivelul aplicatiei.
  In UML, interfetele si relatiile de realizare indica punctele de extindere.
- LSP (substitutie): implementarile sunt utilizabile prin interfetele lor,
  respectand contractele acestora. Evaluatorul apeleaza apply fara sa cunoasca
  clasa concreta. UML arata realizarile interfetelor.
- ISP (interfete specializate): Operation contine doar apply, iar
  ComplexNumberParser contine isValid si parse. Aceste contracte mici sunt
  vizibile in compartimentele de operatii ale interfetelor UML.
- DIP (dependenta de abstractii): evaluatorul si validatorul depind de
  interfete, primite prin constructor. UML arata asocierile lor catre
  Operation si ComplexNumberParser, nu catre implementarile concrete.

4. Sabloane si tehnici de proiectare
- Strategy: Operation defineste strategia de calcul; cele patru operatii sunt
  strategiile concrete, iar ExpressionEvaluator este contextul. In UML apar
  realizarile interfetei si asocierea evaluatorului catre Operation.
- Simple Factory: OperationFactory.create selecteaza si construieste operatia
  dupa simbol. In UML, dependentele fabricii exprima folosirea interfetei si
  crearea claselor concrete. Nu este sablonul GoF Factory Method.
- Dependency Injection: parserul si operatia sunt transmise prin constructor,
  permitand inlocuirea componentelor. Este o tehnica ce sustine DIP.

5. Compilare si rulare din folderul proiectului
  javac -d out src/*.java
  java -cp out Main "2+3*i" "+" "5-6*i" "+" "-2+i"
Rezultat: 5 - 2 * i
Ghilimelele protejeaza caracterul * si pastreaza eventualele spatii dintr-un
numar complex intr-un singur argument.

Livrabile: sursele din src/, diagrama StarUML lab1.mdj si acest readme.txt.
