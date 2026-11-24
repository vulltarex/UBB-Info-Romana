% inversare(L - list, Col - list, R - list) - inverseaza lista L
% model de flux: i i o determinist, i i i determinist
inversare([], Col, Col).
inversare([H|T], Col, Rez) :- inversare(T, [H|Col], Rez).

% secv_max_pare_aux(L - lista, LenMax - int, SecvMax - list, Len - int, Secv - int, Rez - list)
% returneaza secventa de lungime maxima de numere pare consecutive dintr o lista
% model de flux: (i, i, i, i, i, o) - determinist
secv_max_pare_aux([], LenMax, _, Len, Secv, Rez) :-
    Len > LenMax, !,
    inversare(Secv, [], Rez).

secv_max_pare_aux([], _, SecvMax, _, _, Rez) :-
    inversare(SecvMax, [], Rez).

secv_max_pare_aux([H|T], LenMax, SecvMax, Len, Secv, Rez) :-
    H mod 2 =:= 0, !,
    Len1 is Len + 1,
    secv_max_pare_aux(T, LenMax, SecvMax, Len1, [H|Secv], Rez).

secv_max_pare_aux([_|T], LenMax, _, Len, Secv, Rez) :-
    Len > LenMax, !,
    secv_max_pare_aux(T, Len, Secv, 0, [], Rez).

secv_max_pare_aux([_|T], LenMax, SecvMax, _, _, Rez) :-
    secv_max_pare_aux(T, LenMax, SecvMax, 0, [], Rez).


% secv_max_pare(L - list, Rez - list) - determina cea mai lunga secventa
% de numere pare din L
% model de flux: (i, i) - determinist, (i, o) - determinist
% secv_max_pare([], []).
secv_max_pare(L, Rez) :-
    secv_max_pare_aux(L, 0, [], 0, [], Rez).
