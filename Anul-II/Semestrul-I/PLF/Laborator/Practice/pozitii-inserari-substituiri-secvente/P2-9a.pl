% sterge_secv(L - list, R - rez) - sterge toate secventele crescatoare
% din lista L
% model de flux: (i, i, o) - determinist
sterge_secv([], []).
sterge_secv([H1, H2, H3 | T], Rez) :-
    H3 =:= H2 + 1,
    H2 =:= H1 + 1, !,
    sterge_secv(T, Rez).
sterge_secv([H1, H2 | T], Rez) :-
    H2 =:= H1 + 1, !,
    sterge_secv(T, Rez).
sterge_secv([H|T], [H|Rez]):-
    sterge_secv(T, Rez).
