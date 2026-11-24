%12.
% a. Sa se scrie un predicat care substituie intr-o lista un element prin
% altul.
% b. Sa se construiasca sublista (lm, ..., ln) a listei (l1, ..., lk).
%
% subs(Old: integer, New: integer, L: lista, Rez: lista)
% Old - valoarea pe care o inlocuim
% New - valoarea cu care inlocuim
% L - lista in care inlocuim
% Rez - lista rezultata
% model de flux - (i, i, i, o) - determinist
subs(_, _, [], []).
subs(Old, New, [H|T], Rez):-
    H=Old,
    !,
    subs(Old, New, T, Rest),
    Rez = [New|Rest].
subs(Old, New, [H|T], Rez) :-
    subs(Old, New, T, Rest),
    Rez = [H|Rest].

% sublist(M: integer, N: integer, Cnt: integer, L: lista, Rez: lista)
% M - prima pozitie din sublista
% N - ultima pozitie din sublista
% Cnt - pozitia actuala in lista
% L - lista initiala
% Rez - sublista lm...ln
% model de flux - (i, i, i, i, o) - determinist

sublist(_, _, _, [], []).

sublist(M, N, Cnt, [H|T], Rez) :-
    Cnt>=M, Cnt=<N,
    Cnt1 is Cnt + 1,
    sublist(M, N, Cnt1, T, R),
    Rez = [H|R].

sublist(M, N, Cnt, [_|T], Rez) :-
    Cnt<M, Cnt>N,
    Cnt1 is Cnt+1,
    sublist(M, N, Cnt1, T, Rez).

% sublistmain(M: integer, N: integer, L: lista, Rez: lista)
% M - prima pozitie din sublista
% N - ultima pozitie din sublista
% L - lista initiala
% Rez - sublista lm...ln
% model de flux - (i, i, i, o) - determinist


sublistmain(M, N, L, R) :-
    sublist(M, N, 1, L, R).




