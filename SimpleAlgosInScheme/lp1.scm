(define (print data)
    (display data)
    (newline))

;taken from examples

(define listN (iota 29999 1))
;taken from ranges.scm

(define (divisibleBy3or5 num)
  (or (= (modulo num 3) 0) (= (modulo num 5) 0)))

;defined a functio named divisbleBy3or5 that takes in num
;the function does the or operation where it sees if num modulo 3 or 5 is zero

(define divisbleList
  (filter divisibleBy3or5 listN))

;filter is a built in function that takes in a list and a parameter
;in this case filter takes in our listN and uses or previous function
;this creates a new list that contains only values that returned true from divisibleBy3or5

(define (sum lst)
    (if (= 1 (length lst))  
        (car lst) 
        (+ (car lst)
           (sum (cdr lst)))))

;taken directly from learn scheme in under 2 hours video
;defines a funtion sum that takes in lst
;it starts with the base case if the length of the list is 1 return it
;the else case is taking the first value and running sum on the rest of the list
;these segments are then added together to give us our sum

(display "Sum of Multiples of 3 or 5: ")
(print (sum divisbleList))  