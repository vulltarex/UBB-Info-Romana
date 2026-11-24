% elim_3ap(L - list, E - int, Cnt - int, Rez - list) - elimina primele
% trei aparitii ale lui E din L
% model de flux: (i, i, i, o) - determinist
elim_3ap([], _, _, []).
elim_3ap([E|T], E, Cnt, Rez) :-
    Cnt < 3, !,
    Cnt1 is Cnt + 1,
    elim_3ap(T, E, Cnt1, Rez).
elim_3ap([H|T], E, Cnt, [H|Rez]):-
    elim_3ap(T, E, Cnt, Rez).

% elim_3ap_main(L - list, E - int, Rez - list) - apel la functia
% auxiliara cu contorul initializat
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
elim_3ap_main(L, E, Rez) :-
    elim_3ap(L, E, 0, Rez).
