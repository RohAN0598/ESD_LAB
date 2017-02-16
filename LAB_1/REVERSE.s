	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0, =num
	LDR R1, =num + (9*4)
	MOV R3, #0
UP	LDR R4, [R0]
	LDR R2, [R1]
	STR R2, [R0], #4
	STR R4, [R1], #-4
	ADD R3, #1
	TEQ R3, #5
	BNE UP
STOP B STOP

	AREA mydata, DATA, READWRITE
num dcd 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	END