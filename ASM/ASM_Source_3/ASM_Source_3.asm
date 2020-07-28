.include <m128def.inc>	// �ҽ����� �߰�

.def NUMBER	=	R16		// �ɺ�����¡.
.def NUM1	=	R17
.def NUM2	=	R18
.def RESULT	=	R19

.dseg					// ���� �����
flag:		.byte 1
cnt:		.byte 1
num_array:	.byte 5		// 5���� Byte�� Array ����

.cseg					// �ڵ� ���׸�Ʈ ����
INIT:					
	LDI	R27, high(flag)	// X�� flag ���� ����
	LDI	R26, low(flag)	
	LDI	NUM1, 0x00;		// NUM1 �ʱ�ȭ
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
	ST	X, NUM1			// flag�� ����
	LDI	NUM2, 0xFA
	ST	Y, NUM2			// cnt = 250

LOOP:
	DEC	NUMBER			// number --
	CLZ					// zero flag clear
	LDS	NUM1, flag		// num1 = flag
	LDI	NUM2, 0x01		// num2 = 1
	SUB	NUM1, NUM2		// num1 = num1 - num2
	BREQ LOOP_Z1		// ���� ����� 0�̸� LOOP_Z1
	BRNE LOOP_Z0		// ���� ����� 0�� �ƴϸ� LOOP_Z0

BR_END:
	LDS	NUM1, cnt		// NUM1�� cnt �� ����
	LDI	NUM2, 0x01		// NUM2�� 1 ����
	ADD NUM1, NUM2		// num1 = num1 + num2
	BRCC CNT_SET		// carry flag�� �߻� ���ϸ� CNT_SET
	BRCS CNT_INIT		// �߻��ϸ� CNT_INIT
CNT_SET:
	STS cnt, NUM1		// cnt = NUM1
	RJMP LOOP			// �ٽ� LOOP������ JMP

LOOP_Z1:
	ST Z+, NUMBER		// DEC�� NUMBER ���� Z�� ����Ű�� ���� ���� �� Z++
	RJMP BR_END			// BR_END�� �̵�

LOOP_Z0:
	ST -Z, NUMBER		// ���ҵ� NUMBER ���� -Z�� ����Ű�� ���� ����
	RJMP BR_END			// BR_END�� �̵�
