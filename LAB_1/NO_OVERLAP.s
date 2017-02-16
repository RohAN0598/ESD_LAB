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
	LDR R0, =SRC
	LDR R1, =DST
	MOV R3, #10
BACK
	LDR R4, [R0], #4
	STR R4, [R1], #4
	SUB R3, #1
	TEQ R3, #0
	BNE BACK
STOP B STOP

	AREA mydata, DATA, READWRITE
SRC DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
DST DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	END