```
;
; AssemblerApplication1.asm
;
; Created: 28FEB2020 12:13:36 PM
; Author : Benjamin Blouin
;

// Assembler directives
//

// EQU - Set a symbol equal to an expression
// The EQU directive assigns a value to a label. 
// This label can then be used in later expressions. 
// A label assigned to a value by the EQU directive is immutable
//
// Syntax:.EQU Label=Expression
//
.equ all_led = $08
.equ zeroVar = $00
.equ oneVar = $01
.equ twoVar = $02
.equ threeVar = $03
.equ divideVar = $80

// SET - Set a symbol equal to an expression
// Mutable version of .equ

// DEF - Set a symbolic name on a register
// The DEF directive allows the registers to be referred to 
// through symbols. A defined symbol can be used in the rest of 
// the program to refer to the register it is assigned to. 
// A register can have several symbolic names attached to it. 
// A symbol can be redefined later in the program.
//
// Syntax:.DEF Symbol=Register
//
.def zero_reg = r15 
.def temp_local_scope = r16
.def extInput = r17
.def counter = r18
.def loop1 = r19
.def loop2 = r20
.def loop3 = r21
.def shift_register = r22
.def divide_register = r23

// i.e. int main(){}
//
main:
	// Initialize board
    //
	call boardSetup
switch_case:
	// 
	in extInput, pinb // gpio input
	cpi extInput, zeroVar // compare with immediate - Rd - K
	breq reset // conditional relative branch (function call) tests the zero flag (Z)
	cpi extInput, oneVar
	breq multiply           
	cpi extInput, twoVar    
	breq divide             ; pc=8
	cpi extInput, threeVar  
	breq reset              

	// do-while
    //
	brne pc-7

    rjmp main


/*
	Functions
*/


// Delay 8E6 cycles
// 500ms at 16.0 MHz
// Nested do-whiles
// 20*200*200 = 1/2 * 16.0 MHz
delay_half_s:

    ldi  loop3, 20
    ldi  loop2, 200
    ldi  loop1, 200

L1: 
    dec  loop1  
    brne L1     
    dec  loop2  
    brne L1     
    dec  loop3  
    brne L1     
    ret         
}

// Initialize board GPIO
//
boardSetup:
	
    ldi temp_local_scope, $FF
    out ddra, temp_local_scope 
    out portb, temp_local_scope 

	ldi counter, all_led 
	ret

// Reset state
// 
reset:

	ldi temp_local_scope, zeroVar
	out porta, temp_local_scope
    
    rjmp switch_case

// Logical shift left register
// do-while
//
multiply:
    ldi shift_register, oneVar
    ldi counter, all_led
    
    out porta, shift_register
    lsl shift_register
    call delay_half_s
    dec counter
    brne pc-5

    out porta, counter
	rjmp main

// Logical shift right register
// do while
//
divide:
    ldi divide_register, divideVar

    out porta, divide_register
	ror divide_register
    call delay_half_s 
	dec counter
	brne pc-5

    out porta, counter
	rjmp main
```
