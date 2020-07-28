.include <m128def.inc>	// 소스파일 추가

.def NUMBER	=	R16		// 심볼라이징.
.def NUM1	=	R17
.def NUM2	=	R18
.def RESULT	=	R19

.dseg					// 변수 선언부
flag:		.byte 1
cnt:		.byte 1
num_array:	.byte 5		// 5개의 Byte의 Array 형태

.cseg					// 코드 세그먼트 시작
INIT:					
	LDI	R27, high(flag)	// X에 flag 변수 지정
	LDI	R26, low(flag)	
	LDI	NUM1, 0x00;		// NUM1 초기화
	ST	X, NUM1			// flag = NUM1

	LDI	R29, high(cnt)	// Y = CNT
	LDI	R28, low(cnt)

	LDI	R31, high(num_array)	// Z = num_array
	LDI	R30, low(num_array)

	LDI	NUMBER, 0x0A	// NUMBER = 0x0A

CNT_INIT:
	LD	NUM1, X			// NUM1 = flag
	LDI	NUM2, 0x01		// NUM2 = 1
	EOR	NUM1, NUM2		// NUM1 = NUM1 ^ NUM2
	ST	X, NUM1			// flag에 저장
	LDI	NUM2, 0xFA
	ST	Y, NUM2			// cnt = 250

LOOP:
	DEC	NUMBER			// number --
	CLZ					// zero flag clear
	LDS	NUM1, flag		// num1 = flag
	LDI	NUM2, 0x01		// num2 = 1
	SUB	NUM1, NUM2		// num1 = num1 - num2
	BREQ LOOP_Z1		// 연산 결과가 0이면 LOOP_Z1
	BRNE LOOP_Z0		// 연산 결과가 0이 아니면 LOOP_Z0

BR_END:
	LDS	NUM1, cnt		// NUM1에 cnt 값 저장
	LDI	NUM2, 0x01		// NUM2에 1 저장
	ADD NUM1, NUM2		// num1 = num1 + num2
	BRCC CNT_SET		// carry flag가 발생 안하면 CNT_SET
	BRCS CNT_INIT		// 발생하면 CNT_INIT
CNT_SET:
	STS cnt, NUM1		// cnt = NUM1
	RJMP LOOP			// 다시 LOOP문으로 JMP

LOOP_Z1:
	ST Z+, NUMBER		// DEC된 NUMBER 값을 Z가 가리키는 곳에 저장 후 Z++
	RJMP BR_END			// BR_END로 이동

LOOP_Z0:
	ST -Z, NUMBER		// 감소된 NUMBER 값을 -Z가 가리키는 곳에 저장
	RJMP BR_END			// BR_END로 이동
