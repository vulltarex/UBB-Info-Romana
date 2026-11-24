LABORATOR 1 - MAP
README - Principii de proiectare si sabloane folosite

==================================================
1. PREZENTAREA GENERALA A PROIECTARII
==================================================
Programul primeste in linia de comanda numere complexe de forma a + b*i,
separate prin spatiu, intercalate cu un operator (+, -, *, /). Programul:
  1) verifica daca argumentele formeaza o expresie de forma n1 op n2 op ... op nk;
  2) daca da, calculeaza si afiseaza rezultatul (evaluare de la stanga la dreapta).

Clasele si interfetele din diagrama UML:
  - ComplexNumber          : modeleaza un numar complex (real + imaginar).
  - Operation (interfata)  : contractul unei operatii intre doua numere complexe.
  - AddOperation, SubtractOperation, MultiplyOperation, DivideOperation :
                             implementarile concrete ale operatiilor.
  - OperationFactory       : creeaza operatia potrivita pornind de la simbolul operatorului.
  - ComplexNumberParser (interfata) : contractul pentru transformarea unui sir in numar complex.
  - StandardComplexParser  : implementarea parsarii pentru forma a + b*i.
  - ExpressionValidator    : verifica daca argumentele reprezinta o expresie valida.
  - ExpressionEvaluator    : calculeaza valoarea expresiei.
  - Main                   : punctul de intrare, doar coordoneaza celelalte clase.

==================================================
2. PRINCIPII SOLID
==================================================

S - Single Responsibility Principle
  Fiecare clasa are un singur motiv de schimbare:
  - ComplexNumber doar retine datele numarului complex;
  - StandardComplexParser doar parseaza siruri;
  - ExpressionValidator doar valideaza expresia;
  - ExpressionEvaluator doar calculeaza expresia;
  - fiecare *Operation implementeaza o singura operatie;
  - OperationFactory doar creeaza operatii;
  - Main doar leaga componentele intre ele.
  In diagrama: fiecare clasa este separata si are metode putine, coerente.

O - Open/Closed Principle
  Pentru a adauga o operatie noua (ex. ridicarea la putere) se adauga o clasa noua
  care implementeaza Operation si o linie in OperationFactory. ExpressionEvaluator,
  ExpressionValidator, parserul si celelalte operatii NU se modifica.
  Similar, un alt tip de parsare se adauga printr-o noua implementare a
  ComplexNumberParser.
  In diagrama: sagetile de realizare (implementare) catre interfetele Operation si
  ComplexNumberParser arata punctele de extindere.

L - Liskov Substitution Principle
  Orice implementare a Operation poate inlocui oricare alta in ExpressionEvaluator,
  fara ca acesta sa isi schimbe comportamentul sau sa stie tipul concret. Acelasi
  lucru este valabil pentru implementarile ComplexNumberParser.
  In diagrama: ExpressionEvaluator este asociat doar cu interfetele, nu cu clasele concrete.

I - Interface Segregation Principle
  Interfetele sunt mici si specializate: Operation are o singura metoda (apply),
  iar ComplexNumberParser are doar metodele legate de parsare (isValid, parse).
  Nicio clasa nu este fortata sa implementeze metode de care nu are nevoie.

D - Dependency Inversion Principle
  Clasele de nivel inalt (ExpressionEvaluator, ExpressionValidator) depind de
  abstractii (Operation, ComplexNumberParser), nu de clasele concrete. Dependentele
  sunt primite prin constructor (injectare de dependente), iar crearea obiectelor
  concrete se face in Main si in OperationFactory.
  In diagrama: asocierile ExpressionEvaluator -> Operation si
  ExpressionEvaluator/ExpressionValidator -> ComplexNumberParser.

==================================================
3. SABLOANE DE PROIECTARE
==================================================

a) Strategy
  Operation este interfata strategiei, iar AddOperation, SubtractOperation,
  MultiplyOperation si DivideOperation sunt strategiile concrete. ExpressionEvaluator
  este contextul: foloseste o operatie fara sa-i cunoasca tipul concret, iar operatia
  se alege la rulare in functie de operatorul primit.
  In diagrama: interfata Operation, cele 4 clase care o realizeaza si asocierea
  dintre ExpressionEvaluator si Operation.

b) Factory (Simple Factory / Factory Method)
  OperationFactory ascunde logica de creare a obiectelor: primeste simbolul
  (+, -, *, /) si returneaza instanta potrivita de Operation. Astfel, codul client
  (Main, ExpressionEvaluator) nu foloseste direct "new AddOperation()" etc. si nu
  depinde de clasele concrete.
  In diagrama: dependenta OperationFactory -> Operation si relatiile de creare
  catre cele 4 operatii.

c) Dependency Injection (tehnica asociata principiului D)
  Parserul si operatia sunt transmise prin constructor catre validator/evaluator,
  ceea ce usureaza inlocuirea lor si testarea.
