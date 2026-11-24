% adauga_elem(L - list, E - elem, Idx - int, Pow - int, Rez - list) -
% adauga elementul E dupa primul, al 2lea, al 4lea ... element din L
% model de flux: (i, i, i, i, o) - determinist
adauga_elem([], E, Idx, Pow, [E]):-
    Idx =:= Pow + 1, !.
adauga_elem([], _, _, _, []) :- !.
adauga_elem(L, E, Idx, Pow, [E|Rez]) :-
    Idx =:= Pow + 1, !,
    Pow1 is Pow * 2,
    adauga_elem(L, E, Idx, Pow1, Rez).
adauga_elem([H|T], E, Idx, Pow, [H|Rez]) :-
    Idx1 is Idx + 1,
    adauga_elem(T, E, Idx1, Pow, Rez).
