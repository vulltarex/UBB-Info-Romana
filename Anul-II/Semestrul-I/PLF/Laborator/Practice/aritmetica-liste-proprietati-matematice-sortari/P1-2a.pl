% cmmdc(A - int, B - int, Rez - int) - calculeaza cmmdc a doua numere
% intregi model de flux: (i, i, o) - determinist
cmmdc(A, 0, A) :- !.
cmmdc(A, B, Rez) :-
    R is A mod B,
    cmmdc(B, R, Rez).

% cmmdc_list(L - list, Cmmdc - int, Rez - int) - calculeaza cmmdc intr o lista
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
cmmdc_list([], Rez, Rez).
cmmdc_list([H|T], Cmmdc, Rez):-
    cmmdc(H, Cmmdc, R),
    cmmdc_list(T, R, Rez).

% prod_list(L - list, P - int) - calculeaza produsul elem. unei liste
% m.f.: i i det, i o det
prod_list([], 1).
prod_list([H|T], Rez) :-
    prod_list(T, P),
    Rez is H * P.

% cmmmc_list(L - list, Rez - int) - calculeaza cmmmc intr o lista
% model de flux: (i, o) - determinist, (i, i) - determinist
cmmmc_list([H|T], Rez) :-
    prod_list([H|T], P),
    cmmdc_list(T, H, C),
    Rez is P div C.
