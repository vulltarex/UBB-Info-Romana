% member(E - int, L - list) - returneaza true daca E apartine listei
% model de flux: (i, i) determinist, (o, i) nedeterminist
member(E, [E|_]).
member(E, [_|T]) :-
    member(E, T).

% diferenta(L1 - list, L2 - list, R - list) - returneza diferenta a
% celor doua multimi (elementele din L2 care nu apartin L1)
% model de flux: (i, i, o) determinist, (i, i, i) determinist

diferenta(_, [], []).
diferenta(L, [H|T], R) :-
    not(member(H, L)), !,
    diferenta(L, T, Rez),
    R = [H|Rez].
diferenta(L, [_|T], R):-
    diferenta(L, T, R).
