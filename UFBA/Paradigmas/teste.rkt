#lang racket
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
(xor* '(z a m c d) '(d a e c) '(a m))