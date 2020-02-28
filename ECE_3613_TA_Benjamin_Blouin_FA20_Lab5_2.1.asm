start:

	;; Activity 2, part 1
	;;
  ldi r16, 0xff
	out ddra, r16 ; led as output
	out portb, r16 ; pull-up resistors enabled on switches

ACTIVITY_1:
	in r3, pinb
	out pina, r3
	rjmp ACTIVITY_1

	rjmp start
