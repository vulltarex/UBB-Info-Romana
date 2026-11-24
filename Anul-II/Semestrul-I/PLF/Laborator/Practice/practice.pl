% numara_pare(L - list, R - int)
% Numara numerele pare din L
% model de flux: (i, i), (i, o)
numara_pare([],0).

numara_pare([H|T],R):-
    H mod 2 =:= 0,!,
    numara_pare(T, Rez),
    R is Rez+1.

numara_pare([_|T],R):-
    numara_pare(T,R).

% transforma(L - list, R - list)
% lista de intrare contine subliste, care in rezultat vor fi inlocuite
% cu numarul de elemente pare din aceasta
% model de flux: (i, i), (i, o)

transforma([], []).

transforma([H|T], R):-
    is_list(H), !,
    transforma(T, Rez),
    numara_pare(H, Nr),
    R = [Nr|Rez].

transforma([H|T], R):-
    transforma(T, Rez),
    R = [H|Rez].

% sum(A - int, B - int, S - int)
% returneaza suma dintre A si B
% model de flux: (i, i, i), (i, i, o)
sum(A,B,S):-
    S is A+B.

% suma_coada(L - lista, S - int)
% Calculeaza suma elementelor unei liste de numere intregi folosind
% recursivitate de coada
% model de flux: (i, i), (i, o)
suma_coada([], 0).
suma_coada([H|T], S):-
    sum(H,S1,Sum),
    S = S1,
    suma_coada(T, Sum).
