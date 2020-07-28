.include <m128def.inc>	// 소스 파일 추가

.def NUMBER = R16		// define 하는 부분.
.def CNT	= R17
.def SUM	= R18
.def PTR	= R26
 
.cseg					// code segment 시작.
	LDI NUMBER, 0x01
	LDI CNT,	0x0a

	LDI PTR,	0x01
	LDI R27,	0x01	// 각 Register 값을 초기화

MAIN:
	ST	X+,	NUMBER		// NUMBER -> X를 넣는다. X++(후위연산)
	INC	NUMBER			// NUMBER++
	DEC	CNT				// CNT--
	BRNE MAIN			// if(zero flag == 1)

	LDI	SUM, 0x00		
	LDI	CNT, 0x0a
	LDI PTR, 0x01		// Register 값을 초기화

MAIN2:
	LD NUMBER, X+		// X -> NUMBER, X++
	ADD SUM, NUMBER		// SUM = SUM + NUMBER
	DEC CNT				// CNT--
	BRNE MAIN2			// if(zero flag == 1)

	ST	X, SUM			// SUM -> X
