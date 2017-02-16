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
	LDR R0, =num1
	LDR R1, =num2
	LDR R0, [R0]
	LDR R1, [R1]
	MOV R3, #0
	MOV R4, #0
UP	CMP R1, #0
	BEQ EXIT
	ADDS R4, R0
	SUB R1, #1
	ADCS R3, #0
	B UP
EXIT
	LDR R7, =res
	STR R3, [R7], #4
	STR R4, [R7]
STOP B STOP

num1 DCD 0XF
num2 DCD 0XF
	
	AREA mydata, DATA, READWRITE
res DCD 0, 0
	
	END