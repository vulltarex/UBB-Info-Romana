% subs_elem(L - list, E - int, L1 - list, Rez - list) - substituie toate
% aparitiile lui E in L cu L1
% model de flux: (i, i, i, o) - determinist, (i, i, i, i) - determinist
subs_elem([], _, _, []).
subs_elem([E|T], E, L1, [L1|Rez]) :-
    !, subs_elem(T, E, L1, Rez).
subs_elem([H|T], E, L1, [H|Rez]) :-
    subs_elem(T, E, L1, Rez).
