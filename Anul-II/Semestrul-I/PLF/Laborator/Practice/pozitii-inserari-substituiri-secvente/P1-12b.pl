% sublista(L - list, M - int, N - int, Idx - int, Rez - list) -
% contruieste sublista lm...ln a listei L
% model de flux: (i, i, i, i, o) - determinist
sublista([], _, _, _, []).
sublista([H|T], M, N, Idx, [H|Rez]) :-
    Idx >= M,
    Idx =< N, !,
    Idx1 is Idx + 1,
    sublista(T, M, N, Idx1, Rez).
sublista([_|T], M, N, Idx, Rez) :-
    Idx1 is Idx + 1,
    sublista(T, M, N, Idx1, Rez).

% len(L - list, Rez - int) - calculeaza lungimea listei L
% model de flux: (i, o) - determinist, (i, i) - determinist
len([], 0).
len([_|T], Rez):-
    len(T, Rez1),
    Rez is Rez1 + 1.

% sublista_main(L - list, M - int, N - int, Rez - list) - apelul la
% predicatul auxiliar cu verificarile indicilor si Idx initializat
% model de flux: (i, i, i, o) - determinist, (i, i, i, i) - determinist
sublista_main(L, M, N, Rez) :-
    M >= 1,
    M =< N,
    len(L, Len),
    N =< Len,
    sublista(L, M, N, 1, Rez).
