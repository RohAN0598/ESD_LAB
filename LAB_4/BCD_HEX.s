	AREA RESET ,  DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R0, =NUM1
	LDR R0, [R0]
	MOV R8, #0
	MOV R6, #1
	MOV R11, #0X0A
	AND R1, R0, #0x0F
	LSR R0, #4
	MUL R1, R6
	ADD R8, R1
	MUL R0, R11
	ADD R8, R1
	
	LDR R0, =HEX
	STR R8, [R0]
STOP B STOP
		
NUM1 DCD 0X31267

	AREA mydata, DATA, READWRITE
HEX DCD 0

	END
