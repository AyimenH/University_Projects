(define (print data)
    (display data)
    (display "\n")
)

(define (input prompt)
    (display prompt)
    (read)
)

(define x (input "Provide first number: "))
(define y (input "Provide second number: "))
(display x)
(display " + ")
(display y)
(display " = ")
(print (+ x y))