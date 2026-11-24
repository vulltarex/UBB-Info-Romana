% len(L - list, Rez - int) - calculeaza lungimea unei liste
% model de flux: (i, o) - determinist, (i, i) - determinist
len([], 0).
len([_|T], Rez):-
    len(T, Rez1),
    Rez is Rez1 + 1.

% member(E - int, L - list) - returneaza true daca E apartine listei
% model de flux: (i, i) determinist, (o, i) nedeterminist
member(E, [E|_]):- !.
member(E, [_|T]):-
    member(E, T).

% verif_elemente(A - list, B - list) - verifica daca toate elementele
% din lista A se gasesc in lista B
% model de flux: (i, i) - determinist
verif_elemente([], _).
verif_elemente([H|T], B) :-
    member(H, B),
    verif_elemente(T, B).

% verif_multimi(A - list, B - list) - verifica egalitatea a doua multimi
% model de flux: (i, i) - determinist
verif_multimi(A, B) :-
    len(A, L1),
    len(B, L2),
    L1 =:= L2,
    verif_elemente(A, B).
