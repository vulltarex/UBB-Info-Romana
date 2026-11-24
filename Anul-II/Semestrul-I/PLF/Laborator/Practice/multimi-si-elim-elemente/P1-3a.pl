% member(E - int, L - list) - returneaza true daca E apartine listei
% model de flux: (i, i) determinist, (o, i) nedeterminist
member(E, [E|_]).
member(E, [_|T]):-
    member(E,T).

% invers_aux(L - list, Col - list, Rez - list) - inverseaza lista L
% model de flux: (i, i, o) determinist, (i, i, i) determinist
invers_aux([], Col, Col).
invers_aux([H|T], Col, Rez):-
    invers_aux(T, [H|Col], Rez).

% invers(L - list, Rez - list) - apelul la functia auxiliara pentru
% inversarea listei L
% model de flux: (i, o) - determinist, (i, i) determinist
invers(L, Rez):-
    invers_aux(L, [], Rez).

% transforma_aux(L - list, Col - list, Rez - list) - transforma lista L
% intr o multime, in ordinea primei aparitii
% model de flux: (i, i, o) - determinist, (i, i, i) - determinist
transforma_aux([], Col, Rez):-
    invers(Col, Rez).
transforma_aux([H|T], Col, Rez):-
    not(member(H, Col)), !,
    transforma_aux(T, [H|Col], Rez).

transforma_aux([_|T], Col, R) :-
    transforma_aux(T, Col, R).

% transforma(L - list, R - list) - apelul la functia auxiliara pt
% transformarea listei L in multime
% model de flux: (i, o) - determinist, (i, i) - determinist
transforma(L, R) :-
    transforma_aux(L, [], R).
