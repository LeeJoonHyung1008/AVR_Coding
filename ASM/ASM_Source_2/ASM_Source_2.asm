.include <m128def.inc>

.def TEMP_1 =	R16
.def TEMP_2 =	R17
.def TEMP_VAR =	R18
.dseg
var_ref: .byte 1	// �������� �����Ӱ� a,b,c�� �ص� ����
var_val: .byte 1
var_sum: .byte 1

.cseg
	LDI R31, high(var_ref)	// R30, R31�� Z Register, var_ref�� �����ּ� ����
	LDI R30, low(var_ref)	// 31, 30 ���� High, Low �ּҹ����� �־��ش�. var_ref�� �����ּ� ����
	LDI TEMP_1, 0x20		// R16�� 0x20 ����
	ST	Z+, TEMP_1			// Z�� ����Ű�� ���� TEMP_1 ���� �� Z+
	LDI	TEMP_2, 0x02		// R17�� 0x02 ����
	STS	var_val, TEMP_2		// val1�� R17 ����
MAIN:
	LDS	TEMP_1, var_ref		// R16�� var_ref �� ����
	LD	TEMP_2, Z			// R17�� Z�� ����Ű�� ���� �� ����

	ADD	TEMP_1, TEMP_2		// TEMP_1 = TEMP_1 + TEMP_2
	STD	Z+1, TEMP_1			// Z+1�� ����Ű�� ���� TEMP_1 �� ����

	INC	TEMP_2				
	ST	Z, TEMP_2			// ������ TEMP_2�� Z�� ����Ű�� ���� ����
	RJMP MAIN				// �ٽ� Main���� ����
