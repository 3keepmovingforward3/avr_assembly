;
; ECE_3613_TA_Benjamin_Blouin_FA20_Lab6.asm
;
; Created: 3/9/2020 8:16:16 AM
; Author : Benjamin Blouin
;


; Replace with your application code
main:
    call boardSetup
	in r16, pinb
	cpi r16, 0
	breq caseZero
	cpi r16, 1
	breq caseOne
	cpi r16, 2
	breq caseTwo
	cpi r16, 3
	breq caseThree

    rjmp main

boardSetup:
	ldi r16, $FF
	out ddra, r16
	out portb, r16
	ret

quarterSecDelay:
		; Delay 4 000 000 cycles
		; 250ms at 16.0 MHz

		ldi  r18, 21
		ldi  r19, 75
		ldi  r20, 191
	L1: dec  r20
		brne L1
		dec  r19
		brne L1
		dec  r18
		brne L1
		nop
		ret

caseZero:
	ldi r16, $25
	out porta, r16
	
	call quarterSecDelay
	out porta, r0
	call quarterSecDelay
	call quarterSecDelay
	rjmp main

caseOne:
	ldi r16, $51
	out porta, r16

	call quarterSecDelay
	call quarterSecDelay
	out porta, r0
	call quarterSecDelay
	call quarterSecDelay
	rjmp main

caseTwo:
	ldi r16, $75
	out porta, r16

	call quarterSecDelay
	call quarterSecDelay
	call quarterSecDelay
	out porta, r0
	call quarterSecDelay
	rjmp main

caseThree:
	ldi r16, $51
	out porta, r16

	call quarterSecDelay
	call quarterSecDelay
	call quarterSecDelay
	call quarterSecDelay
	out porta, r0
	call quarterSecDelay
	call quarterSecDelay
	call quarterSecDelay
	call quarterSecDelay
	rjmp main
