(define (print data)
    (display data)
    (newline))

;taken from examples & lp1

(define (sumEvenFibonacci num)
  (if (< num 2)
      (+ num 1)
      (let loop ((i 2) (n1 1) (n2 2))
        (if (= i num)
            (+ n1 n2)
            (loop (+ i 1) n2 (+ n1 n2))))))

;defined a function named sumEvenFibonaci that takes in a value num
;if num is 0 or 1 (the special cases of fib) than num gets incremented by 1 and returned
;defined a loop that starts at 2 and sets n1 and n2 to 1 and 2 respectively (F_0 = 1 & F_1 = 2)
;if num is equal to our index then just add the values of n1 and n2 (F_3 => F_1 + F_2 => 2 + 3 = 5)
;else increment our index, set n1 to n2 & n2 to n1 + n2 (n1 in this addition is n1 prior to being set to n2)

(display "Sum of Even Fibonacci Numbers: ")
(print (sumEvenFibonacci 42))
;according to my code 42 is the highest possible number who's value is less then 1 billion

