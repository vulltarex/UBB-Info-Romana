% nr_aparitii(L - list, E - int, Rez - int) - numara aparitiile lui E in
% lista L
% model de flux: (i, i, o) det, (i, i, i) det
nr_aparitii([], _, 0):- !.
nr_aparitii([E|T], E, Rez) :- !,
    nr_aparitii(T, E, Rez1),
    Rez is Rez1 + 1.
nr_aparitii([_|T], E, Rez) :-
    nr_aparitii(T, E, Rez).

% sterge_elem(L - list, E - int, Rez - list) - sterge toate aparitiile
% lui E din L
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
sterge_elem([], _, []).
sterge_elem([E|T], E, Rez) :-
    !, sterge_elem(T, E, Rez).
sterge_elem([H|T], E, [H|Rez]) :-
    sterge_elem(T, E, Rez).

% lista_perechi(L - list, Rez - list) - cerinta 5b din P1
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
lista_perechi([], []).
lista_perechi([H|T], Rez) :-
    nr_aparitii([H|T], H, Nr),
    sterge_elem(T, H, L),
    Rez = [[H,Nr]|Rez1],
    lista_perechi(L, Rez1).

