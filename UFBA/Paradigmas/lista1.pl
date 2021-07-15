%questão1
concatenar([], L2, L2) :- !.
concatenar([R|L1], L2, [R|L3]) :-
    concatenar(L1, L2, L3).

%questão 2
concatenarINV(L1, L2, L3) :-
    concatenar(L2, L1, L3).

%questão 3
concatenarLL([], []) :- !.
concatenarLL([[]|L2], L) :-
    concatenarLL(L2, L), !.
concatenarLL([[R|L1]|L2], [R|L]) :-
    concatenarLL([L1|L2], L).

%questão 4
juntar(L1, [], L1) :- !.
juntar([], L2, L2) :- !.
juntar([R|L1], [E|L2], [R, E|L3]) :-
    juntar(L1, L2, L3).

%questão 5
adicionarFinal(Z, [], [Z]) :- !.
adicionarFinal(Z, [R|L1], [R|L2]) :-
    adicionarFinal(Z, L1, L2).

%questão 6
inverter([], []) :- !.
inverter([L1|R1], L4) :-
    inverter(R1, L3),
    adicionarFinal(L1, L3, L4). 

%questão 7
inverterLG([], []) :- !.
inverterLG([L1|R], L3) :-
    is_list(L1),
    inverterLG(L1, L2),
    inverterLG(R, L4),
    adicionarFinal(L2, L4, L3), !.
inverterLG([L1|R], L3) :-
    inverterLG(R, L4),
    adicionarFinal(L1, L4, L3).

%questão 8
parear(_, [], []) :- !.
parear(A, [Head|Tail], [[A, Head]|LL]) :-
    parear(A, Tail, LL).

%questão 9
pares([], []) :- !.
pares([Head|Tail], Final) :-
    parear(Head, Tail, ListPar),
    pares(Tail, Result),
    concatenar(ListPar, Result, Final).

%questão 11


%questão 12
tem(A, [Head|_]) :-
    A==Head, !.
tem(A, [_|Tail]) :-
    tem(A, Tail).

conjunto([]) :- !.
conjunto([Head|Tail]) :-
    tem(Head, Tail),
    conjunto(Tail), !.

remover(X,[H|T],R):- !.