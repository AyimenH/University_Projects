(load "deck.scm")
;from class example

(define (cardValue card)
  (let* ((cardRank (substring card 0 (- (string-length card) 1)))
         (value (cond ((or (string=? cardRank "K") (string=? cardRank "Q") (string=? cardRank "J") (string=? cardRank "T")) 10)
         ((string=? cardRank "A") 1)
         (else (string->number cardRank)))))
    value))
;cardValue takes a card and splits up the card so it can grab the rank
;if the rank is a non number like a face card or ace then they get assigned their respective value(making 10 T stumped me for so long)
;else the number of the card is the rank thats grabbed

(define (handValue hand)
  (define (go hand total)
    (if (null? hand)
        total

        (let ((card (car hand)))
          (let ((value (cardValue card)))
            (go (cdr hand) (+ total value))))))
  (go hand 0))
;handValue has a helper function go that sums up the rank of each card in a hand

(define (playHand dealerHand initialPlayerHand initialDeck)
  (let loop ((currentPlayerHand initialPlayerHand) (remainingDeck initialDeck))
    (let ((playerValue (handValue currentPlayerHand)))

      (if (> playerValue 21)
          (list 'bust playerValue)

          (if (or (>= playerValue 17) (null? remainingDeck))
              (let* ((dealerValue (handValue dealerHand))
                     (result (cond ((> dealerValue 21) 'win) ((> playerValue dealerValue) 'win) ((= playerValue dealerValue) 'tie) (else 'lose))))
                
                (list result playerValue dealerValue))
              (loop (append currentPlayerHand (list (car remainingDeck))) (cdr remainingDeck)))))))
;playHand is where my 'brilliant' algorithim is implemented
;playHand takes in the dealer's and player's cards and the deck which it loops through under these conditions
;the return case is a bust where the player's card rank total goes over 21
;else if the rank total is less then or equal to 17 then start comparing to the dealers rank total

;if the dealer busts or is less then the player's rank total then the player wins
;if the dealer is equal then no one gets a win
;else the dealer wins

;a list stores the result, player rank, and dealer rank (check playAllHands to see it be used)
;the algorithim is from reading that in casinos dealers are told to keep hitting until they reach 17

(define (processDeck deck)
  (define (playAllHands hands wins total)
    (if (null? hands)
        (begin (display "Number of blackjack hands where current player wins: ")
        (display wins) (display "/") (display total)
        (newline))

        (let* ((hand (car hands)))
          (if (null? hand)
              (begin (playAllHands (cdr hands) wins total))

              (let* ((dealerHand (car hand))
                     (playerHand (list (cadr hand) (caddr hand)))
                     (deck (cdddr hand))
                     (result (playHand dealerHand playerHand deck)))

                (let ((playerValue (cadr result))
                      (dealerValue (if (> (length result) 2) (caddr result) 0))
                      (outcome (case (car result) ((win) "Player wins!") ((lose) "Player loses.") ((bust) "Player busts.") (else ""))))

                  (display "Player’s Hand: ") (display playerValue)
                  (newline)
                  (display "Dealer’s Hand: ") (display dealerValue)
                  (newline)
                  (display outcome) 
                  (newline))

                (case (car result)
                  ((win) (playAllHands (cdr hands) (+ wins 1) (+ total 1)))
                  ((lose) (playAllHands (cdr hands) wins (+ total 1)))
                  ((bust) (playAllHands (cdr hands) wins (+ total 1)))
                  (else (playAllHands (cdr hands) wins (+ total 1)))))))))

  (playAllHands deck 0 0))
;playAllHands starts by utilizing the brilliant algorithim to grab the result of a hand
;then goes through the playHand list to bind those variables to the values from playHand
;based on said values the outcome of the game is printed
;finally, from the result the case updates the current hand, wins, and total for each outcome

(processDeck deck)
