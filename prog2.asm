; This code acquires inputs and uses various nested subroutines such as multiplication, addition, subtraction
; exponentials, and division in order to evaluate a postfix expression through stacks. 
; After evaluating the expression, the final calculation is printed to the screen in hexadecimal format, 
; this code is pulled from my LAB1. 

; partners: elisak2, genel2, mgau2

.ORIG x3000
	

	AND R0, R0, #0
	AND R1, R1, #0 
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0; initialize all registers


;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

	GETC			; get character
	OUT
	
	LD R1, EQUAL 		; load the ascII value of EQUAL into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the input is an equal sign
	BRnp CHECK_SPACE	; if the character is not an equal symbol, check whether it's a space
	LD R3, STACK_START	; load STACK_START to R3
	LD R4, STACK_TOP 	; load STACK_TOP to R4
	ADD R3, R3, #-1
	NOT R4, R4 
	ADD R4, R4, #1
	ADD R3, R4, R3		; Determine stack only has one value if (STACK_START-1) is = to STACK_TOP
	BRz RESULT_LOAD		; if only one value, branch to load
	BRnp INVALID_EXP	; otherwise it is an invalid expression

RESULT_LOAD
	ST R7, SAVE_R7		; store R7
	JSR POP			; pop the last value
	LD R7, SAVE_R7		; load R7 back
	ADD R5, R0, #0;		; store what is in R0 into R5
	ADD R3, R0, #0		; store what is in R0 into R3
	ST R7, SAVE_R72		; store R7
	JSR PRINT_HEX		; call subroutine to print to screen in hex
	LD R7, SAVE_R72		; load R7 back
	HALT			; end code 

CHECK_SPACE
	AND R1, R1, #0		; clear R1
	LD R1, SPACE		; load the ascII value of space into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if input is equal to space
	BRz EVALUATE		; loop back to look for next character


VALID_CHAR
	AND R1, R1, #0		; clear R1 again 
	LD R1, SUBTRACT		; load ascII value of subtraction symbol into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a subtraction sign
	BRz OPERAND_FALSE	; if so, branch to loop for operators
	
	AND R1, R1, #0		; clear R1
	LD R1, ADDIT		; load ascII value of addition symbol into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is an addition sign
	BRz OPERAND_FALSE
	
	AND R1, R1, #0		; clear R1
	LD R1, MPLY		; load ascII value of multiplication symbol into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a multiplication sign
	BRz OPERAND_FALSE

	AND R1, R1, #0		; clear R1
	LD R1, DIVIDE		; load ascII value of division symbol into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a division sign
	BRz OPERAND_FALSE

	AND R1, R1, #0		; clear R1
	LD R1, POWER		; load ascII value of exponential symbol into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is an exponent sign
	BRz OPERAND_FALSE

	AND R1, R1, #0		; clear R1
	LD R1, ZERO		; load ascII value of zero into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a zero 
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, ONE		; load ascII value of one into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 1
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, TWO		; load ascII value of two into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 2
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, THREE		; load ascII value of three into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 3
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, FOUR		; load ascII value of four into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 4
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, FIVE		; load ascII value of five into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 5
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, SIX		; load ascII value of six into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 6
	BRz OPERAND_TRUE
	
	AND R1, R1, #0		; clear R1
	LD R1, SEVEN		; load ascII value of seven into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 7
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, EIGHT		; load ascII value of eight into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 8
	BRz OPERAND_TRUE

	AND R1, R1, #0		; clear R1
	LD R1, NINE		; load ascII value nine into R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		; check if the character is a 9
	BRz OPERAND_TRUE

INVALID_EXP
	LEA R0, INVALID		; store invalid string into R0
	PUTS			; prints out string
	HALT

OPERAND_TRUE
	ST R7, SAVE_R73		; store R7
	LD R2, NUMBER		; set R2 to x0030
	NOT R2, R2
	ADD R2, R2, #1
	ADD R0, R2, R0		; subtract x0030 from input R0
	JSR PUSH		; push value into stack
	LD R7, SAVE_R73		; load R7 back
	BRnzp EVALUATE		; loop back to evaluate to retrieve next character

OPERAND_FALSE

	ST R0, SAVE_R0		; store R0
	ST R7, SAVE_R74		; store R7
	JSR POP 		; pop out one value from stack
	LD R7, SAVE_R74		; load R7 back
	ADD R4, R0, #0		; set popped out value to R4
	ST R7, SAVE_R75		; store R7
	JSR POP			; pop out one value from stack
	LD R7, SAVE_R75		; load R7
	ADD R3, R0, #0		; set popped out value to R3
	LD R0, SAVE_R0		; load R0 back
	
	AND R1, R1, #0		; clear R1
	ADD R1, R1, #1		; set R1=1
	NOT R5, R5
	ADD R5, R5, #1
	ADD R1, R1, R5		; R1-1 in order to check for underflow
	BRz INVALID_EXP		; if zero, then underflow and loop to an invalid expression

	AND R1, R1, #0		; clear R1 again 
	LD R1, SUBTRACT		; load R1 with the ascII value of the subtraction symbol
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		;check if character is a subtraction sign
	BRz CALL_SUB		; if = 0, branch to CALL_SUB
	
	AND R1, R1, #0; clear R1
	LD R1, ADDIT		; load R1 with the ascII value of the addition symbol
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		;check if character is an addition sign
	BRz CALL_ADD		; if = 0, branch to CALL_ADD
	
	AND R1, R1, #0; clear R1
	LD R1, MPLY		; load R1 with the ascII value of the multiplication symbol
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		;check if character is an multiplication sign
	BRz CALL_MULT		; if = 0, branch to CALL_MULT

	AND R1, R1, #0; clear R1
	LD R1, DIVIDE		; load R1 with the ascII value of the division symbol
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		;check if character is a division sign
	BRz CALL_DIV		; if = 0, branch to CALL_DIV

	AND R1, R1, #0; clear R1
	LD R1, POWER		; load R1 with the ascII value of the exponential symbol
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1		;check if character is a power sign
	BRz CALL_POW		; if = 0, branch to CALL_POW
	
CALL_SUB
	ST R7, SAVE_R76		; store R7
	JSR MIN			; jump to MIN subroutine	
	LD R7, SAVE_R76		; load R7 back
	ST R7, SAVE_R77		; store R7
	JSR PUSH		; jump to PUSH subroutine
	LD R7, SAVE_R77		; load R7 back
	BRnzp EVALUATE		; branch back for next character
CALL_ADD
	ST R7, SAVE_R78		; store R7
	JSR PLUS		; jump to PLUS subroutine
	LD R7, SAVE_R78		; load R7 back
	ST R7, SAVE_R79		; store R7
	JSR PUSH		; jump to PUSH subroutine
	LD R7, SAVE_R79		; load R7 back
	BRnzp EVALUATE		; branch back for next character
CALL_MULT
	ST R7, SAVE_R710	; store R7
	JSR MULT		; jump to MULT subroutine
	LD R7, SAVE_R710	; load R7 back
	ST R7, SAVE_R711	; store R7
	JSR PUSH		; jump to PUSH subroutine
	LD R7, SAVE_R711	; load R7 back
	BRnzp EVALUATE		; branch back for next character
CALL_DIV
	ST R7, SAVE_R712	; store R7
	JSR DIV			; jump to DIV subroutine
	LD R7, SAVE_R712	; load R7
	ST R7, SAVE_R713
	JSR PUSH		; jump to PUSH subroutine
	LD R7, SAVE_R713
	BRnzp EVALUATE		; branch back for next character

CALL_POW
	ST R7, SAVE_R714
	JSR EXP 		; jump to EXP subroutine
	LD R7, SAVE_R714
	ST R7, SAVE_R715
	JSR PUSH		; jump to PUSH subroutine
	LD R7, SAVE_R715
	BRnzp EVALUATE		; branch back for next character
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
NUMBER		.FILL x0030	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	; 
STACK_TOP	.FILL x4000	; 
EQUAL 		.FILL x003D	; 
SPACE		.FILL x0020	;
SUBTRACT	.FILL x002D	;
ADDIT		.FILL x002B	; 
MPLY		.FILL x002A	;
DIVIDE		.FILL x002F	;
POWER		.FILL x005E	;
ZERO		.FILL x0030	;
ONE		.FILL x0031	; 
TWO		.FILL x0032	;
THREE		.FILL x0033	;
FOUR		.FILL x0034	;
FIVE		.FILL x0035	;
SIX		.FILL x0036	;
SEVEN		.FILL x0037	;
EIGHT		.FILL x0038	;
NINE		.FILL x0039	;
SAVE_R7		.BLKW #1	; 
SAVE_R0		.BLKW #1	; 
SAVE_R1		.BLKW #1	;
SAVE_R2		.BLKW #1	;
SAVE_R3		.BLKW #1	;
SAVE_R4		.BLKW #1	;
SAVE_R42	.BLKW #1	;
SAVE_R5		.BLKW #1	;
SAVE_R6		.BLKW #1	;
SAVE_R71	.BLKW #1	; 
SAVE_R72	.BLKW #1	;
SAVE_R73	.BLKW #1	;
SAVE_R74	.BLKW #1	;
SAVE_R75	.BLKW #1	;
SAVE_R76	.BLKW #1	;
SAVE_R77	.BLKW #1	;
SAVE_R78	.BLKW #1	;
SAVE_R79	.BLKW #1	;
SAVE_R710	.BLKW #1	;
SAVE_R711	.BLKW #1	; 
SAVE_R712	.BLKW #1	;
SAVE_R713	.BLKW #1	;
SAVE_R714	.BLKW #1	;
SAVE_R715	.BLKW #1	;
SAVE_R716	.BLKW #1	;


INVALID		.STRINGZ "Invalid Expression" 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	ST R3, SAVE_R3
	ST R4, SAVE_R4

	AND R0, R0, #0		; clear R0
	ADD R0, R3, R4		; add R3 and R4 and store into R0

	LD R3, SAVE_R3
	LD R4, SAVE_R4
	RET			; return back 
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	ST R3, SAVE_R3
	ST R4, SAVE_R4

	AND R0, R0, #0		; clear R0
	NOT R4, R4
	ADD R4, R4, #1		; make R4 negative
	ADD R0, R3, R4		; add R3 with negative R4

	LD R3, SAVE_R3
	LD R4, SAVE_R4
	RET			; return back 
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

MULT	
	ST R3, SAVE_R3	; store registers
	ST R4, SAVE_R4
	AND R0, R0, #0	; initialize R0
	ADD R0, R3, #0 	; put the value in R3 into R0
	NOT R0, R0
	ADD R0, R0, #1
	ADD R0, R3, #0	; check if R3 is negative
	BRz NEGATIVE
	AND R0, R0, #0
	
MULTIPLY
	ADD R0, R3, R0	; add the value in R3 into R0 
	ADD R4, R4, #-1	; decrement R4 by one, the counter
	BRp MULTIPLY	; if positive, loop again 
	LD R3, SAVE_R3	; load stored registers back
	LD R4, SAVE_R4
	RET
	

NEGATIVE
	AND R0, R0, #0	; clear R0 
	NOT R3, R3
	ADD R3, R3, #1	; make R3 positive 
	
NEGATIVE_LOOP

	ADD R0, R3, R0	; add the value in R3 into R0 
	ADD R4, R4, #-1	; decrement R4 by one, the counter
	BRp NEGATIVE_LOOP	; if positive, loop again 

	NOT R0, R0
	ADD R0, R0, #1	; Make the output R0 negative
	LD R3, SAVE_R3	; Load stored values back
	LD R4, SAVE_R4
	RET
	;treat R4 as a counter 

	;use counter to loop through
	;check for negative or positive
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
	ST R5, SAVE_R5
	ST R3, SAVE_R3
	ST R4, SAVE_R4
	ST R2, SAVE_R2
	AND R0, R0, #0
	AND R5, R5, #0
	AND R2, R2, #0
	ADD R5, R4, #0	; Put R4 into R5 as counter 
	ADD R2, R3, #0	;add the value in R3 into R0 
	NOT R4, R4
	ADD R4, R4, #1 	;make R4 into a negative 

DIVI
	ADD R2, R4, R2	; subtract R4 from R2
	BRnz FIN
	


	ADD R2, R5, R2	; add R4 back to R2
DIVIDING
	ADD R0, R0, #1	; increment R0 counter 
	ADD R2, R4, R2	; subtract R4 from R2
	BRp DIVIDING	; keep looping if R2 is still positive 


FIN	LD R2, SAVE_R2
	LD R3, SAVE_R3
	LD R4, SAVE_R4	
	LD R5, SAVE_R5	
	RET		; return back 
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	ST R3, SAVE_R3	; store registers
	ST R4, SAVE_R4
	ST R2, SAVE_R2
	AND R0, R0, #0	
	AND R2, R2, #0	
	ADD R5, R3, #0 	; set R5 equal to the value in R3


	ADD R4, R4, #-1	; decrement R4 by 1
	
M_EXP	

	ST R4, SAVE_R42
	AND R4, R4, #0
	ADD R4, R5, #0 	; set R4 equal to R5
	ST R7, SAVE_R71	; save R7
	JSR MULT	; jump to the multiplication subroutine
	LD R7, SAVE_R71	; restore R7
	AND R3, R3, #0	; clear R3
	ADD R3, R0, #0	; add the output of MULT into R3
	LD R4, SAVE_R42	; restore R4
	ADD R4, R4, #-1	; decrement R4
	BRp M_EXP	; if R4 is still positive, loop M_EXP again 
	
FOUND
	LD R3, SAVE_R3	; load registers
	LD R4, SAVE_R4		
	LD R5, SAVE_R5
	RET

	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	ST R0, SAVE_R0		;store registers
	ST R1, SAVE_R1
	ST R2, SAVE_R2
	ST R4, SAVE_R4
	ST R5, SAVE_R5
	ST R6, SAVE_R6
	ST R7, SAVE_R716
	AND R0, R0, #0		; initialize registers 
	AND R1, R1, #0 
	AND R2, R2, #0
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0
CHECK_DIG
	ADD R5, R1, #0		
	ADD R5, R5, #-4		; check if less than 4 digits was printed
	BRzp END		; branch to CHECK if zero or positive
	AND R0, R0, #0		; initialize digit 
	AND R2, R2, #0		; initialize bit counter 
	AND R4, R4, #0

CHECK_BIT
	ADD R4, R2, #0
	ADD R4, R4, #-4		;check if < 4 bits were taken from R3
	BRzp CHECK_VAL		; branch if more than 4 bits was received from R3
	ADD R0, R0, R0		; shift digit to the left
	ADD R3, R3, #0		; check if R3 is negative or positive
	BRzp GREATER_THAN	; if R3 is greater than 0, branch to GREATER_THAN 
	ADD R0, R0, #1		; add 1 to digit
	ADD R3, R3, R3		; shift R3 to the left
	ADD R2, R2, #1		;increment bit counter
	BRnzp CHECK_BIT

GREATER_THAN
	ADD R0, R0, #0		; add 0 to digit
	ADD R3, R3, R3		; shift
	ADD R2, R2, #1		; increment bit counter
	BRnzp CHECK_BIT

CHECK_VAL
	ADD R6, R0, #0
	ADD R6, R6, #-9		; check if digit > 9
	BRnz LOOP		; branch to LOOP if digit > 9 
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #10		; add x0
	BRnzp PRINT

LOOP
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #3		; add 'A' - 10
	BRnzp PRINT		; go to PRINT

PRINT 
	OUT			; print out
	ADD R1, R1, #1		; increment digit counter
	BRnzp CHECK_DIG		; loop back to CHECK_DIG

END
	LD R0, SAVE_R0		;load registers back 
	LD R1, SAVE_R1
	LD R2, SAVE_R2
	LD R4, SAVE_R4
	LD R5, SAVE_R5
	LD R6, SAVE_R6
	LD R7, SAVE_R716
	RET			; return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.END

