% nr_aparitii(E - intreg, L - list, Rez - intreg) - returneaza numarul
% de aparitii al elementului E in lista L
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
nr_aparitii(_, [], 0).
nr_aparitii(E, [E|T], Rez):- !,
    nr_aparitii(E, T, Rez1),
    Rez is Rez1 + 1.
nr_aparitii(E, [_|T], Rez) :-
    nr_aparitii(E, T, Rez).

% elim(L - list, LCopy Rez - list) - prelucreaza lista L si pastreaza
% elementele care apar o singura data in LCopy
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
elim([], _, []).
elim([H|T], L, [H|Rez]):-
    nr_aparitii(H, L, R),
    R =:= 1, !,
    elim(T, L, Rez).
elim([_|T], L, Rez):-
    elim(T, L, Rez).

% elim_main(L, Rez) - elimina elementele care se repeta din L
% model de flux: (i, o) - determinist, (i, i) - determinist
elim_main(L, Rez):-
    elim(L, L, Rez).

% maxim(L - list, Max - intreg, Rez - intreg) - determina valoarea
% maxima din lista L
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
maxim([], Max, Max).
maxim([H|T], Max, Rez) :-
    H > Max, !,
    maxim(T, H, Rez).
maxim([_|T], Max, Rez):-
    maxim(T, Max, Rez).

% elim_elem(L - list, E - int, Rez - list) - elimina toate aparitiile
% unui element din lista L
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
elim_elem([], _, []).
elim_elem([H|T], E, [H|Rez]):-
    H =\= E, !,
    elim_elem(T, E, Rez).
elim_elem([_|T], E, Rez):-
    elim_elem(T, E, Rez).

% elim_max(L - list, Rez - list) - elimina toate aparitiile elementului
% maxim din lista
% model de flux: (i, o) - determinist, (i, i) - determinist
elim_max([], []).
elim_max([H|T], Rez) :-
    maxim([H|T], H, Max),
    elim_elem([H|T], Max, Rez).
