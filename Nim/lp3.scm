(define (print data)
  (display data)
  (newline))
;from example

(define (nim-win h1 h2 h3)
  (if (= (logxor h1 h2 h3) 0)
      0
      1
  )
)
;nim-win takes in the three heaps as arguements and performs XOR on them
;i'm still not fully sure why this works but according to GFGs
;if the current position XOR value is non-zero then the current player is winning
;nim-win is assigning 0 to the losing position and any non-zero value to 1

(define (countPlayerWins)
  (define (go n maxNumber count)
    (if (> n maxNumber)
        count 

        (let ((h1 n)(h2 (* 2 n))(h3 (* 3 n)))

          (if (= (nim-win h1 h2 h3) 1)
              (go (+ n 1) maxNumber (+ count 1))

              (go (+ n 1) maxNumber count))))
  )
  (go 1 (expt 2 30) 0)
)
;countPlayerWins contains go (shoutout Computerphile) that takes in n =< 2^30 where n is postive and our accumulator count
;let is used to bind our heaps to values of n, 2n, and 3n that are then used in our XOR function
;count is only incremented if nim-win returns a non zero number (a winning position)

(display "Number of Nim Heap Configurations Where Current Player Wins: ")
(print (countPlayerWins))