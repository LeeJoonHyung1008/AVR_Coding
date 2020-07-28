.include <m128def.inc>

.def TEMP_1 =	R16
.def TEMP_2 =	R17
.def TEMP_VAR =	R18
.dseg
var_ref: .byte 1	// 변수명은 자유롭게 a,b,c로 해도 가능
var_val: .byte 1
var_sum: .byte 1

.cseg
	LDI R31, high(var_ref)	// R30, R31은 Z Register, var_ref의 상위주소 저장
	LDI R30, low(var_ref)	// 31, 30 각각 High, Low 주소번지에 넣어준다. var_ref의 하위주소 저장
	LDI TEMP_1, 0x20		// R16에 0x20 저장
	ST	Z+, TEMP_1			// Z가 가리키는 곳에 TEMP_1 저장 후 Z+
	LDI	TEMP_2, 0x02		// R17에 0x02 저장
	STS	var_val, TEMP_2		// val1에 R17 저장
MAIN:
	LDS	TEMP_1, var_ref		// R16에 var_ref 값 저장
	LD	TEMP_2, Z			// R17에 Z가 가리키는 곳의 값 저장

	ADD	TEMP_1, TEMP_2		// TEMP_1 = TEMP_1 + TEMP_2
	STD	Z+1, TEMP_1			// Z+1이 가리키는 곳에 TEMP_1 값 저장

	INC	TEMP_2				
	ST	Z, TEMP_2			// 증가된 TEMP_2를 Z가 가리키는 곳에 저장
	RJMP MAIN				// 다시 Main으로 점프
