.include <m128def.inc>	// �ҽ� ���� �߰�

.def NUMBER = R16		// define �ϴ� �κ�.
.def CNT	= R17
.def SUM	= R18
.def PTR	= R26
 
.cseg					// code segment ����.
	LDI NUMBER, 0x01
	LDI CNT,	0x0a

	LDI PTR,	0x01
	LDI R27,	0x01	// �� Register ���� �ʱ�ȭ

MAIN:
	ST	X+,	NUMBER		// NUMBER -> X�� �ִ´�. X++(��������)
	INC	NUMBER			// NUMBER++
	DEC	CNT				// CNT--
	BRNE MAIN			// if(zero flag == 1)

	LDI	SUM, 0x00		
	LDI	CNT, 0x0a
	LDI PTR, 0x01		// Register ���� �ʱ�ȭ

MAIN2:
	LD NUMBER, X+		// X -> NUMBER, X++
	ADD SUM, NUMBER		// SUM = SUM + NUMBER
	DEC CNT				// CNT--
	BRNE MAIN2			// if(zero flag == 1)

	ST	X, SUM			// SUM -> X
