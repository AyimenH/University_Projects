(define (print data)
    (display data)
    (newline))

; Recursive function to compute Fibonacci numbers
(define (fibonacci n)
    (if (< n 2)
        (+ n 1)  ; Adjust base cases to start from F0 = 1, F1 = 2
        (+ (fibonacci (- n 1)) (fibonacci (- n 2)))))

(define (sum n)
    (if (= n 0)
        (fibonacciNums 0)
        (+ (fibonacciNums n) (sum (- n 1)))))

(print (sum 5))
