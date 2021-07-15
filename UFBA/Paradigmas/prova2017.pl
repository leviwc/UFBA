%questão 1
oculte(_, [], []) :- !.
oculte(PALAVRA, [LISTA|RESTO], [xxxx|RESULTANTE]) :-
    LISTA==PALAVRA,
    oculte(PALAVRA, RESTO, RESULTANTE), !.
oculte(PALAVRA, [LISTA|RESTO], [LISTA|RESULTANTE]) :-
    oculte(PALAVRA, RESTO, RESULTANTE).
%questão 2
isInList(WORD, [LIST|_]) :-
    LIST==WORD, !.
isInList(WORD, [_|REST]) :-
    isInList(WORD, REST).

oculteConj(_, [], []) :- !.
oculteConj(LIST, [FRASE|RESTO], [xxxx|RESULTANTE]) :-
    isInList(FRASE, LIST),
    oculteConj(LIST, RESTO, RESULTANTE), !.
oculteConj(LIST, [FRASE|RESTO], [FRASE|RESULTANTE]) :-
    oculteConj(LIST, RESTO, RESULTANTE).

%questão 3
intercala(_, _, 0, []) :- !.
intercala(NOME1, _, 1, [NOME1]) :- !.
intercala(NOME1, NOME2, QUANTIDADE, [NOME1, NOME2|RESULTANTE]) :-
    QUANTIDADE2 is QUANTIDADE-2,
    intercala(NOME1, NOME2, QUANTIDADE2, RESULTANTE).

%questão 4
conta(_, [], 0) :- !.
conta(A, [Head|Tail], Sum2) :-
    A==Head,
    conta(A, Tail, Sum),
    Sum2 is Sum+1, !.
conta(A, [_|Tail], Sum) :-
    conta(A, Tail, Sum).

apaga(_, [], []).
apaga(A, [Head|Tail], List) :-
    A==Head,
    apaga(A, Tail, List), !.
apaga(A, [Head|Tail], [Head|List]) :-
    apaga(A, Tail, List). 

sumarize([], [], []) :- !.
sumarize([Head|List], [Head|L1], [Sum|L2]) :-
    conta(Head, List, SumT),
    Sum is SumT+1,
    apaga(Head, List, ListP),
    sumarize(ListP, L1, L2).

%questão 5
getEqualConseq(_, [], []) :- !.
getEqualConseq(A, [Head|Tail], [A|List]) :-
    A==Head,
    getEqualConseq(A, Tail, List), !.
getEqualConseq(_, _, []).

nextDifferent(_, [], _, []) :- !.
nextDifferent(A, [Head|Tail], 0, List) :-
    A==Head,
    nextDifferent(A, Tail, 0, List), !.
nextDifferent(_, [Head|Tail], 1, [Head|List]) :-
    nextDifferent(Head, Tail, 1, List), !.
nextDifferent(_, [Head|Tail], 0, [Head|List]) :-
    nextDifferent(Head, Tail, 1, List), !.

empacote([], []).
empacote([Head|Tail], [[Head|List2]|List]) :-
    getEqualConseq(Head, Tail, List2),
    nextDifferent(Head, Tail, 0, List3),
    empacote(List3, List).




