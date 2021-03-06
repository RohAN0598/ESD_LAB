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
	LDR R0, =ARRAY
	LDR R1, =NUM
	LDR R1, [R1]
	MOV R2, #0
	MOV R3, #10
UP	CMP R3, #0
	BEQ EXIT
	LDR R4, [R0], #4
	CMP R4, R1
	ADDEQ R2, #1
	BEQ EXIT
	SUB R3, #1
	B UP
EXIT	LDR R0, =RES
	STR R2, [R0]
STOP 	B STOP

ARRAY DCD 0X1, 0X2, 0X3, 0X4, 0X5, 0X6, 0X7, 0X8, 0X9, 0XA
NUM DCD 0X11
	AREA mydata, DATA, READWRITE
RES DCD 0
	END