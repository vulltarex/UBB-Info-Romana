% nr_aparitii(E - int, L - list, Rez - int) - determina numarul de
% aparitii al lui E in lista L
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
nr_aparitii(_, [], 0).
nr_aparitii(E, [E|T], Rez) :-
    !,
    nr_aparitii(E, T, Rez1),
    Rez is Rez1 + 1.
nr_aparitii(E, [_|T], Rez) :-
    nr_aparitii(E, T, Rez).

% sterge(L - list, E - int, Rez - list) - sterge toate aparitiile lui E
% din L
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
sterge([], _, []).
sterge([E|T], E, Rez) :- !,
    sterge(T, E, Rez).

sterge([H|T], E, [H|Rez]) :-
    sterge(T, E, Rez).

% perechi(L - list, Col - list, Rez - list) - produce o lista de
% perechi, continand numerele distincte din lista si numarul lor de
% aparitii model de flux: (i, i, o) determinist, (i, i, i) - determinist
perechi([], Col, Col).
perechi([H|T], Col, Rez) :-
    nr_aparitii(H, [H|T], Nr),
    sterge(T, H, L),
    perechi(L, Col1, Rez),
    Col1 = [[H, Nr]|Col].

% perechi_main(L - list, Rez - list) - face apelul catre predicatul perechi
% model de flux: (i, o) - determinist, (i, i) - determinist
perechi_main(L, Rez) :-
    perechi(L, [], Rez).
