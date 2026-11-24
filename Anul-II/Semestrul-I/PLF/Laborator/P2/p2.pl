%7.
% a) Definiti un predicat care determina produsul unui numar reprezentat
% cifra cu cifra intr-o lista cu o anumita cifra. De ex: [1 9 3 5 9 9] *
% 2
% => [3 8 7 1 9 8]

% b) Se da o lista eterogena, formata din numere intregi si maximum 9 liste de
% numere intregi. Sa se inlocuiasca fiecare sublista cu rezultatul
% inmultirii sublistei cu numarul de ordine al sublistei (prima sublista
% cu 1, a 2-a cu 2, etc.). De ex: [1, [2, 3], [4, 1, 4], 3, 6, [7, 5, 1,
% 3, 9], 5, [1, 1, 1], 7] => [1, [2, 3], [8, 2, 8], 3, 6, [2, 2, 5, 4,
% 1, 7], 5, [4, 4, 4], 7]

% convert_numar(N - int, Acc - lista, R - lista)
% transforma N intr o lista formata din cifrele sale
% model de flux: (i, i, i), (i, i, o)
convert_numar(0, Acc, Acc).
convert_numar(N, Acc, R):-
    N \= 0,
    C is N mod 10,
    N1 is N // 10,
    Acc1 = [C|Acc],
    convert_numar(N1, Acc1, R).

% convert_lista(L - lista, Acc - int, R - int)
% transforma o lista intr un numar format din elementele listei (cifre)
% model de flux: (i, i, i), (i, i, o)

convert_lista([], Acc, Acc).
convert_lista([H|T], Acc, R):-
    Acc1 is Acc * 10 + H,
    convert_lista(T, Acc1, R).

% rez_cifre(N - int, R - lista)
% previne cazul de lista vida pentru rezultatul 0
% model de flux: (i, i), (i, o)
rez_cifre(0, [0]).
rez_cifre(N, R):-
    N > 0,
    convert_numar(N, [], R).
% produs(L - lista, F - int, R - lista)
% Calculeaza produsul numarului reprezentat cifra cu cifra in L inmultit
% cu factorul F, in lista R
% model de flux: (i, i, i), (i, i, o)
produs([], _, []).
produs([H|T], F, R):-
    convert_lista([H|T], 0, Nr),
    Rez is Nr * F,
    rez_cifre(Rez, R).

% produs_poz_aux(L - lista, Cnt - int, R - lista)
% Cerinta b
% model de flux(i, i, i), (i, i, o)

produs_poz_aux([], _, []).
produs_poz_aux([H|T], C, R):-
    is_list(H), !,
    produs(H, C, Rez),
    C1 is C+1,
    produs_poz_aux(T, C1, ListRez),
    R = [Rez|ListRez].

produs_poz_aux([H|T], C, R):-
    produs_poz_aux(T, C, Rez),
    R = [H|Rez].

% produs_poz(L - lista, R - lista)
% apelul cu contor initializat pentru produs_poz_aux
% model de flux: (i, i), (i, o)
produs_poz(L, R):-
    produs_poz_aux(L, 1, R).
