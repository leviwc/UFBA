#lang racket
;questão 1
(define (contagem n)
    (cond
        [(<= n 0) '() ]
        [else (append (contagem (- n 1))
            (list n))]
    )
)

;(contagem 1)
;questão 2
(define (contagem+ n som)
   (cond
       [(<= n 0) '() ]
       [else (append (contagem+ (- n 1) som)
       (list (+ n som)))]
    )
)

(define (llncomlista l som)
    (cond
        [(null? (cdr l)) (list (contagem+ (first l) som)) ]
        [else (cons (contagem+ (first l) som) (llncomlista (cdr l) (+ som (first l))))]
    )
)
(define (cria-lln . numeros)
    (cond
        [(null? numeros) empty]
        [else (llncomlista numeros 0)]
    )
)
;(cria-lln 4 4 4 4)

;questão 3
(define (tem-similar l func num)
    (cond
        [(null? l) #f]
        [(func num (first l)) #t]
        [else (tem-similar (cdr l) func num)]
    )
)
(define (remove-similares-final l func l2)
    (cond
        [(null? l) '()]
        [(tem-similar (cdr l) func (first l)) 
            (remove-similares-final (cdr l) func (append (list (first l)) l2))
        ]
        [(tem-similar l2 func (first l))
            (remove-similares-final (cdr l) func (append (list (first l)) l2))
        ]
        [else
           (append (list (first l)) (remove-similares-final (cdr l) func (append (list (first l)) l2)) ) 

        ]
    )

)
(define (remove-similares l [func eq?])
    (remove-similares-final l func '())
)

;questão 4
(define (transforma func lg)
	(cond
		[(null? lg) '()]
		[(list? (first lg))
			(cons (transforma func (first lg)) (transforma func (cdr lg)))
		]
		[else
			(cons (func (first lg)) (transforma func (cdr lg)))
		]
	)

)
(transforma (lambda(x) (* x x)) '(1 (2 3 (4)) ((5)) (6 7)))
;questão 5
(define (merge listas)
	(cond
		[(null? listas) '()]
		[else (append (first listas) (merge (cdr listas)))]
	)
)
(define (xor* . listas)
	(remove-similares 
		(merge listas)
	)
)
;(xor* '(z a m c d) '(d a e c) '(a a))