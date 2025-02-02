;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

;Introduction: 

; This program iterates over all 27 bins of the histogram. 
; The program goes to each bin address to get the content, then takes the hexadecimal value and prints it to the monitor as an ASCII character. 
; partners: none

; R0 stores the OUT character
; R1 points to the current location in the histogram 
; R2 bit counter for hexadecimal value
; R3 frequency value of the char is the histogram 
; R4 digit that is being converted into hexadecimal 
; R5 digit counter
; R6 bin counter iteration


	AND R6, R6, #0		; initialize all the registers
	AND R0, R0, #0
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0
	AND R5, R5, #0
	ADD R6, R6, #-15
	ADD R6, R6, #-12

	
BIN_LOOP
	ADD R6, R6, #15
	ADD R6, R6, #12		; add back 27 to get the increment 
	LD R0, AT_SYM 		; load register with the @ symbol 
	ADD R0, R0, R6		; Add the increment into R0
	OUT			; print R0

SPACE
	AND R0, R0, #0 		; initialize R0 again
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #2		; put space into R0
	OUT			; print R0

HISTO
	LD R1, HIST_ADDR 	; Load the starting address of the histogram into R1
	ADD R1, R1, R6		; Add the value of the increment to the address to find the next address
	LDR R3, R1, #0 		; load the memory of R1 into R3

CHECK_DIG 

	ADD R5, R5, #-4 	; check if less than 4 digits was printed
	BRzp CHECK 		; branch to CHECK if zero or positive
	ADD R5, R5, #4 		; restore R5 to what it previously was 
	AND R0, R0, #0 		; initialize digit
	AND R2, R2, #0		; initialize bit counter


CHECK_BIT

	ADD R2, R2, #-4 	; check if < 4 bits were taken from R3
	BRzp CHECK_VAL 		; branch if more than 4 bits was received from R3
	ADD R2, R2, #4 		; restore R2 to its previous value 
	ADD R0, R0, R0 		; shift digit to the left
	ADD R3, R3, #0 		; check if R3 is negative or positive
	BRzp GREATER_THAN 	; if R3 is greater than 0, branch to GREATER_THAN 
	ADD R0, R0, #1 		; add 1 to digit
	ADD R3, R3, R3 		; shift R3 to the left
	ADD R2, R2, #1 		; increment bit counter
	BRnzp CHECK_BIT 	; loop back to get next bit 

GREATER_THAN 
	ADD R0, R0, #0 		; Add 0 to digit
	ADD R3, R3, R3 		; shift 
	ADD R2, R2, #1 		; increment bit counter
	BRnzp CHECK_BIT 	; loop back to check_bit

CHECK_VAL
	ADD R2, R2, #4		; restore R2 to its previous value 
	ADD R0, R0, #-9 	; check if digit > 9
	BRnz LOOP 		; branch to LOOP if digit > 9
	ADD R0, R0, #9
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #10		; add x0
	BRnzp PRINT 		; go to PRINT
LOOP
	ADD R0, R0, #9
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #3		; add 'A' - 10
	BRnzp PRINT 		; go to PRINT 

PRINT 
	OUT
	ADD R5, R5, #1 		; increment digit counter
	BRnzp CHECK_DIG 	; go to CHECK_DIG
		


CHECK 
	AND R0, R0, #0 		; initialize/clear R0
	ADD R0, R0, x000A 	; make a newline 
	OUT
	ADD R6, R6, #1 		; increment R6 by 1
	ADD R6, R6, #-15
	ADD R6, R6, #-12
	BRn BIN_LOOP 		; check if all 27 bins have went through 
	BRnzp DONE

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
AT_SYM		.FILL #64

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
