%questão 1
rem1(E, [E|L], L).
rem1(E, [H|L], [H|LR]) :-
    rem1(E, L, LR), !.

%questão 2
tem(A, [A|_]).
tem(A, [_|T]) :-
    tem(A, T).
uniao([], L, L).
uniao([H|T], L, LR) :-
    tem(H, L),
    uniao(T, L, LR), !.
uniao([H|T], L, [H|LR]) :-
    uniao(T, L, LR).

uniaoll([], []) :- !.
uniaoll([L|T], LR) :-
    uniaoll(T, LR2),
    uniao(L, LR2, LR).
%questão 3
xor([], L, L) :- !.
xor([H|T], L, LR) :-
    rem1(H, L, L2),
    xor(T, L2, LR), !.
xor([H|T], L, [H|LR]) :-
    xor(T, L, LR).

%questão 4
filtra(_, [], []).
filtra(P, [H|T], [H|R]) :-
    call(P, H),
    filtra(P, T, R), !.
filtra(P, [_|T], R) :-
    filtra(P, T, R).

%questão 5
solve([], _, LG, LG).
solve([[]|T], LB, LG, LR) :-
    solve(T, LB, LG, LR), !.
solve([[H|L]|T], LB, LG, LR) :-
    rem1(H, LB, _),
    solve([L|T], LB, LG, LR), !.
solve([[H|L]|T], LB, LG, LR) :-
    rem1(H, LG, LG2),
    solve([L|T], [H|LB], LG2, LR), !.
solve([[H|L]|T], LB, LG, LR) :-
    solve([L|T], LB, [H|LG], LR).
xorll(LL, LR) :-
    solve(LL, [], [], LR), !.

remove_todos(_, [], 1, []).
remove_todos(E, [E|L], _, LR) :-
    remove_todos(E, L, 1, LR), !.
remove_todos(E, [H|L], B, [H|LR]) :-
    remove_todos(E, L, B, LR). 