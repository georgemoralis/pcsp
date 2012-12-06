#include "stdafx.h"
#if 0
#include "interruptman.h"
#include "memory/memory.h"

#include "hle/kernel/object.h"
#include "hle/kernel/partition.h"

typedef struct InterruptInfo
{
	int unk_0;
	int unk_4;
	int unk_8;
	int unk_C;
	int unk_10;
	int unk_14;
	int unk_18;
	int unk_1C;
	int unk_20;
	int unk_24;
	int unk_28; //heap
	int unk_2C; //sub-intr
	int unk_30; //attr
	int unk_34;
} InterruptInfo;

InterruptInfo interrupts[67];

///////////////////////////////////////////////////////////////////

namespace InterruptManager
{
	extern int sceKernelRegisterSubIntrHandler();
	extern int sceKernelReleaseSubIntrHandler();
	extern int sceKernelEnableSubIntr();
	extern int sceKernelDisableSubIntr();
	extern int sceKernelSuspendSubIntr();
	extern int sceKernelResumeSubIntr();
	extern int sceKernelIsSubInterruptOccurred();
	extern int QueryIntrHandlerInfo();
	extern int sceKernelRegisterUserSpaceIntrStack();
}

int hleKernelRegisterUserSpaceIntrStack(int base, int size)
{
	int result = 0;

	int state = sceKernelCpuSuspendIntr();

	int ustack_base = *((int *) 0x00003ABC);

	if (!ustack_base)
	{
		if (!(base < 0))
		{
			*((int *) 0x00003AC0) = size;
			*((int *) 0x00003ABC) = base;
		}
		else
		{
			result = 0x8002006C;
		}
	}
	else
	{
		result = 0x8002006D;
	}

	sceKernelCpuResumeIntr(state);

	return result;
}

void hleKernelCallSubIntrHandler(int a0, int a1, int a2, int a3)
{
	t2 /* @1 */ = ((a0 << 0x00000003) - a0) << 0x00000003;
	s3 /* @2 */ = a2;
	s4 /* @3 */ = a3;
	t0 /* @4 */ = ((int *) (t2 /* @1 */ + 0x00003AE4))[10];
	s0 /* @5 */ = ((int *) ((a1 << 0x00000002) + t0 /* @4 */))[0];
	t0 /* @6 */ = ((int *) s0 /* @5 */)[0];
	if (t0 /* @6 */ == 0x00000000)
	{

label4:
		a0 /* @19 */ = 0x80020068;
	}
	else
	{
		if ((t0 /* @6 */ & 0x00000003) == 0x00000003)
			goto label4;
		t5 /* @7 */ = ((int *) s0 /* @5 */)[3];
		s1 /* @8 */ = t0 /* @6 */ & 0xFFFFFFFC;
		a3 /* @9 */ = t5 /* @7 */ + 0x00000001;
		((int *) s0 /* @5 */)[3] = a3 /* @9 */;
		s2 /* @10 */ = gp;
		a2 /* @11 */ = ((int *) s0 /* @5 */)[1];
		gp = a2 /* @11 */;
		__asm__ ("ctc1       $zr, $31;");
		t0 /* @12 */ = 0x00000E00;
		__asm__ ("ctc1       $t0, $31;"
			: 
		: "=r"(0x00000E00));
		if (s1 /* @8 */ >= 0)
		{
			v0 /* @27 */ = sceKernelGetUserIntrStack ();
			a1 /* @28 */ = ((int *) s0 /* @5 */)[2];
			v0 /* @16 */ = sceKernelCallUserIntrHandler (s3 /* @2 */, a1 /* @28 */, s4 /* @3 */, 0x00000000, s1 /* @8 */, v0 /* @27 */);
		}
		else
		{
			a1 /* @13 */ = ((int *) s0 /* @5 */)[2];
			v0 /* @16 */ v1 /* @17 */ = (*UNK) (s3 /* @2 */, a1 /* @13 */, s4 /* @3 */, a3 /* @9 */, 0x00000E00, 0x00003AE4, t2 /* @1 */, 0x00000000);
		}
		gp = s2 /* @10 */;
		__asm__ ("ctc1       $zr, $31;");
		t0 /* @18 */ = 0x00000E00;
		__asm__ ("ctc1       $t0, $31;"
			: 
		: "=r"(0x00000E00));
		a0 /* @19 */ = v0 /* @16 */;
	}
	ra = ((int *) sp)[5];
	s4 /* @20 */ = ((int *) sp)[4];
	s3 /* @21 */ = ((int *) sp)[3];
	s2 /* @22 */ = ((int *) sp)[2];
	s1 /* @23 */ = ((int *) sp)[1];
	s0 /* @24 */ = ((int *) sp)[0];
	sp = sp + 0x00000020;
	return;
}

/**
* Subroutine at address 0x00000E94
*/
int sceKernelGetUserIntrStack ()
{
	a0 /* @1 */ = *((int *) 0x00003AC4);
	if (a0 /* @1 */ != 0x00000000)
	{
		__asm__ ("cfc0       $a2, $14;"
			: "=r"(a2 /* @5 */));
		v0 /* @4 */ = ((int *) a2 /* @5 */)[29];
	}
	else
	{
		a1 /* @2 */ = *((int *) 0x00003AC0);
		a0 /* @3 */ = *((int *) 0x00003ABC);
		v0 /* @4 */ = a0 /* @3 */ + a1 /* @2 */;
	}
	return v0 /* @4 */;
}

/**
* Subroutine at address 0x00000EC4
*/
int sceKernelCallUserIntrHandler (int a0, int a1, int a2, int a3, int t0, int t1)
{
	0x00000EC4: 0x27BDFEA0 '...'' - addiu      $sp, $sp, -352
		0x00000EC8: 0xAFB7014C 'L...' - sw         $s7, 332($sp)
		0x00000ECC: 0xAFB60148 'H...' - sw         $s6, 328($sp)
		0x00000ED0: 0x0100B021 '!...' - move       $s6, $t0
		0x00000ED4: 0xAFB50144 'D...' - sw         $s5, 324($sp)
		0x00000ED8: 0x00E0A821 '!...' - move       $s5, $a3
		0x00000EDC: 0xAFB40140 '@...' - sw         $s4, 320($sp)
		0x00000EE0: 0x00C0A021 '!...' - move       $s4, $a2
		0x00000EE4: 0xAFB3013C '<...' - sw         $s3, 316($sp)
		0x00000EE8: 0x00A09821 '!...' - move       $s3, $a1
		0x00000EEC: 0xAFB20138 '8...' - sw         $s2, 312($sp)
		0x00000EF0: 0x00809021 '!...' - move       $s2, $a0
		0x00000EF4: 0xAFB10134 '4...' - sw         $s1, 308($sp)
		0x00000EF8: 0x01208821 '!. .' - move       $s1, $t1
		0x00000EFC: 0xAFBF0150 'P...' - sw         $ra, 336($sp)
		0x00000F00: 0x0C000C33 '3...' - jal        0x000030CC
		0x00000F04: 0xAFB00130 '0...' - sw         $s0, 304($sp)
		0x00000F08: 0x0040B821 '!.@.' - move       $s7, $v0
		0x00000F0C: 0x40477800 '.xG@' - cfc0       $a3, $15
		0x00000F10: 0xAFA70000 '....' - sw         $a3, 0($sp)
		0x00000F14: 0x8FA30000 '....' - lw         $v1, 0($sp)
		0x00000F18: 0x40437000 '.pC@' - cfc0       $v1, $14
		0x00000F1C: 0xAFA30004 '....' - sw         $v1, 4($sp)
		0x00000F20: 0x27A60010 '...'' - addiu      $a2, $sp, 16
		0x00000F24: 0x8FA20004 '....' - lw         $v0, 4($sp)
		0x00000F28: 0x40C67000 '.p.@' - ctc0       $a2, $14
		0x00000F2C: 0x3C100000 '...<' - lui        $s0, 0x0000
		0x00000F30: 0x26023910 '.9.&' - addiu      $v0, $s0, 14608
		0x00000F34: 0x8C4501AC '..E.' - lw         $a1, 428($v0)
		0x00000F38: 0x2631FFE0 '..1&' - addiu      $s1, $s1, -32
		0x00000F3C: 0x24A40240 '@..$' - addiu      $a0, $a1, 576
		0x00000F40: 0x0224182B '+.$.' - sltu       $v1, $s1, $a0
		0x00000F44: 0x50600006 '..`P' - beqzl      $v1, 0x00000F60
		0x00000F48: 0x26103910 '.9.&' - addiu      $s0, $s0, 14608
		0x00000F4C: 0x0003FFCD '....' - break      0x00FFF
		0x00000F50: 0x0003FFCD '....' - break      0x00FFF
		0x00000F54: 0x0003FFCD '....' - break      0x00FFF
		0x00000F58: 0x080003D3 '....' - j          0x00000F4C
		0x00000F5C: 0x00000000 '....' - nop
		0x00000F60: 0x8E0D01B4 '....' - lw         $t5, 436($s0)
		0x00000F64: 0x02402021 '! @.' - move       $a0, $s2
		0x00000F68: 0x02204821 '!H .' - move       $t1, $s1
		0x00000F6C: 0x25AC0001 '...%' - addiu      $t4, $t5, 1
		0x00000F70: 0xAE0C01B4 '....' - sw         $t4, 436($s0)
		0x00000F74: 0x02602821 '!(`.' - move       $a1, $s3
		0x00000F78: 0x02803021 '!0..' - move       $a2, $s4
		0x00000F7C: 0x02A03821 '!8..' - move       $a3, $s5
		0x00000F80: 0x0C000BFC '....' - jal        0x00002FF0
		0x00000F84: 0x02C04021 '!@..' - move       $t0, $s6
		0x00000F88: 0x8E0B01B4 '....' - lw         $t3, 436($s0)
		0x00000F8C: 0x00409021 '!.@.' - move       $s2, $v0
		0x00000F90: 0x8FA90000 '....' - lw         $t1, 0($sp)
		0x00000F94: 0x256AFFFF '..j%' - addiu      $t2, $t3, -1
		0x00000F98: 0xAE0A01B4 '....' - sw         $t2, 436($s0)
		0x00000F9C: 0x40C97800 '.x.@' - ctc0       $t1, $15
		0x00000FA0: 0x8FA80004 '....' - lw         $t0, 4($sp)
		0x00000FA4: 0x40C87000 '.p.@' - ctc0       $t0, $14
		0x00000FA8: 0x0C000C3E '>...' - jal        0x000030F8
		0x00000FAC: 0x02E02021 '! ..' - move       $a0, $s7
		0x00000FB0: 0x02401021 '!.@.' - move       $v0, $s2
		0x00000FB4: 0x8FBF0150 'P...' - lw         $ra, 336($sp)
		0x00000FB8: 0x8FB7014C 'L...' - lw         $s7, 332($sp)
		0x00000FBC: 0x8FB60148 'H...' - lw         $s6, 328($sp)
		0x00000FC0: 0x8FB50144 'D...' - lw         $s5, 324($sp)
		0x00000FC4: 0x8FB40140 '@...' - lw         $s4, 320($sp)
		0x00000FC8: 0x8FB3013C '<...' - lw         $s3, 316($sp)
		0x00000FCC: 0x8FB20138 '8...' - lw         $s2, 312($sp)
		0x00000FD0: 0x8FB10134 '4...' - lw         $s1, 308($sp)
		0x00000FD4: 0x8FB00130 '0...' - lw         $s0, 304($sp)
		0x00000FD8: 0x03E00008 '....' - jr         $ra
		0x00000FDC: 0x27BD0160 '`..'' - addiu      $sp, $sp, 352
}

void hleKernelRegisterSubIntrHandler(u32 intr, u32 subintr, int (*handler)(), void *a3)
{
	int result /* a0 $6 */ = 0x80020065;

	int s0 /* $1 */ = intr;
	int s3 /* $2 */ = subintr;
	int s6 /* $3 */ = a3;
	int s5 /* $4 */ = a1;
	int s4 /* $5 */ = ((handler >> 0x0000001F) < 0x00000001);
	
	s1 /* $7 */ = 0x00000000;

	if (a0 < 67)
	{
		int state = 0; //sceKernelCpuSuspendIntr();

		int t0 /* $12 */ = a0 << 3;
		
		InterruptInfo &interrupt /* $13 */ = interrupts[intr];

		int $11 = v0 /* $11 */;

		$14 = interrupt[0];
		
		if ($14 != 0x00000000)
		{
			if (s4 /* $5 */ == 0x00000000)
			{
				{
					if (subintr < 0)
					{
label40:
						return 0x80020065;
					}
					else
					{
						if (u32(interrupt[12]) <= subintr))
						{
							return 0x80020065;
						}
						else
						{
							int *$30 = (int *)interrupt.heap;
							int *$31 = $30[subintr];
							int  $32 = *$31;
							if ($32 == 0x00000000)
							{
								if (s4 /* $5 */ == 0x00000000)
								{
									v0 /* $34 */ = ((int *) s2 /* $13 */)[11];

label21:
									a2 /* $35 */ = s3 /* $2 */ | 0x00000002;
									
									if (v0 /* $34 */ == 0x00000000)
									{

label27:
										((int *) fp /* $31 */)[0] = a2 /* $35 */;
										v0 /* $39 */ = sceKernelFindModuleByAddress (s3 /* $2 */);
										v1 /* $40 */ = 0x00000000;
										if (!(v0 /* $39 */ == 0x00000000))
										{
											v1 /* $40 */ = ((int *) v0 /* $39 */)[26];
										}
										((char *) fp /* $31 */)[48] = 0x00000000;
										t1 /* $41 */ = ((int *) fp /* $31 */)[12];
										((int *) fp /* $31 */)[1] = v1 /* $40 */;
										t0 /* $42 */ = t1 /* $41 */ & 0xFFFFFEFF;
										((int *) fp /* $31 */)[12] = (t0 /* $42 */ | 0x00001600);
										v0 /* $43 */ = ((int *) s2 /* $13 */)[11];
										((int *) fp /* $31 */)[2] = s6 /* $3 */;
										if (!(v0 /* $43 */ == 0x00000000))
										{
											v0 /* $44 */ = ((int *) v0 /* $43 */)[3];
											if (v0 /* $44 */ != 0x00000000)
											{
												v0 /* $47 */ v1 /* $48 */ = (*UNK) (s0 /* $1 */, s5 /* $4 */, s3 /* $2 */, s6 /* $3 */, t0 /* $42 */, t1 /* $41 */);
												s1 /* $7 */ = v0 /* $47 */;
											}
										}
										if (s1 /* $7 */ != 0x00000000)
										{
											((int *) fp /* $31 */)[0] = 0x00000000;
										}
										else
										{
										}
									}
									else
									{
										v0 /* $36 */ = ((int *) v0 /* $34 */)[2];
										if (!(v0 /* $36 */ != 0x00000000))
											goto label27;
										v0 /* $51 */ v1 /* $52 */ = (*UNK) (s0 /* $1 */, s5 /* $4 */, s3 /* $2 */, s6 /* $3 */, t0 /* $12 */, 0x80020000, t2 /* $27 */, 0x80020000);
										s1 /* $7 */ = v0 /* $51 */;
										if (!(v0 /* $51 */ != 0x00000000))
										{
											a2 /* $35 */ = s3 /* $2 */ | 0x00000002;
											goto label27;
										}
									}
								}
								else
								{
									a1 /* $33 */ = ((int *) fp /* $31 */)[12];
									if (((a1 /* $33 */ >> 11) & 0x00000001) != 0x00000000)
									{
										v0 /* $34 */ = ((int *) s2 /* $13 */)[11];
										goto label21;
									}
									else
									{
										goto label40;
									}
								}
							}
							else
							{
								s1 /* $7 */ = 0x80020067;
							}
						}
					}
				}

label44:
				a0 /* $15 */ = ((int *) sp)[0];
				sceKernelCpuResumeIntr (a0 /* $15 */);
				k1 = s7 /* $8 */;
				a0 /* $6 */ = s1 /* $7 */;
			}
			else
			{
				t2 /* $27 */ = *((int *) 0x00003ABC);
				a0 /* $6 */ = 0x80020065;
				if (!(t2 /* $27 */ == 0x00000000))
				{
					t5 /* $28 */ = ((int *) s2 /* $13 */)[12];
					if (((t5 /* $28 */ >> 13) & 0x00000001) != 0x00000000)
						goto label12;
					s1 /* $7 */ = 0x80020065;
					goto label44;
				}
			}
		}
		else
		{
			s1 /* $7 */ = 0x80020068;
			goto label44;
		}
	}

	return result;
}

/**
* Subroutine at address 0x00001204
*/
void sceKernelReleaseSubIntrHandler (int a0, int a1)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[0] = s0;
	s0 /* $1 */ = a0;
	((int *) sp)[3] = s3;
	v1 /* $2 */ = 0x80020065;
	s3 /* $3 */ = a1;
	((int *) sp)[2] = s2;
	s2 /* $4 */ = 0x00000000;
	((int *) sp)[7] = ra;
	((int *) sp)[6] = s6;
	((int *) sp)[5] = s5;
	((int *) sp)[4] = s4;
	((int *) sp)[1] = s1;
	if (!(((a0 < 0x00000043)) == 0x00000000))
	{
		s4 /* $5 */ = k1;
		k1 = k1 >> 0x00000010;
		v0 /* $8 */ = sceKernelCpuSuspendIntr ();
		t0 /* $9 */ = s0 /* $1 */ << 0x00000003;
		a3 /* $10 */ = t0 /* $9 */ - s0 /* $1 */;
		s1 /* $11 */ = (a3 /* $10 */ << 0x00000003) + 0x00003AE4;
		v1 /* $12 */ = ((int *) s1 /* $11 */)[0];
		if (v1 /* $12 */ == 0x00000000)
		{

label31:

label32:
			s2 /* $4 */ = 0x80020068;
		}
		else
		{
			if (s3 /* $3 */ < 0)
			{

label34:
				s2 /* $4 */ = 0x80020065;
			}
			else
			{
				t2 /* $13 */ = ((unsigned char *) s1 /* $11 */)[48];
				t1 /* $14 */ = (s3 /* $3 */ < t2 /* $13 */);
				if (t1 /* $14 */ != 0x00000000)
				{
					t6 /* $24 */ = ((int *) s1 /* $11 */)[10];
					s5 /* $25 */ = ((int *) ((s3 /* $3 */ << 0x00000002) + t6 /* $24 */))[0];
					v0 /* $26 */ = ((int *) s5 /* $25 */)[0];
					if (v0 /* $26 */ == 0x00000000)
					{
						goto label32;
					}
					else
					{
						if (v0 /* $26 */ >= 0)
						{
							v0 /* $28 */ = ((int *) s1 /* $11 */)[11];

label15:
							if (v0 /* $28 */ == 0x00000000)
							{
								v0 /* $30 */ = ((int *) s1 /* $11 */)[11];

label23:
								s1 /* $31 */ = ((int *) s5 /* $25 */)[0];
								((int *) s5 /* $25 */)[0] = 0x00000000;
								if (!(v0 /* $30 */ == 0x00000000))
								{
									v0 /* $32 */ = ((int *) v0 /* $30 */)[5];
									if (v0 /* $32 */ != 0x00000000)
									{
										v0 /* $35 */ v1 /* $36 */ = (*UNK) (s0 /* $1 */, s3 /* $3 */, 0x00000000, a3 /* $10 */, t0 /* $9 */, t1 /* $14 */, t2 /* $13 */, 0x80020000);
										s2 /* $4 */ = v0 /* $35 */;
									}
								}
								if (s2 /* $4 */ != 0x00000000)
								{
									((int *) s5 /* $25 */)[0] = s1 /* $31 */;
								}
								else
								{
								}
							}
							else
							{
								v0 /* $29 */ = ((int *) v0 /* $28 */)[4];
								if (v0 /* $29 */ != 0x00000000)
								{
									v0 /* $39 */ v1 /* $40 */ = (*UNK) (s0 /* $1 */, s3 /* $3 */, 0x00000000, a3 /* $10 */, t0 /* $9 */, t1 /* $14 */, t2 /* $13 */, 0x80020000);
									s2 /* $4 */ = v0 /* $39 */;
									if (!(v0 /* $39 */ != 0x00000000))
									{
										v0 /* $30 */ = ((int *) s1 /* $11 */)[11];
										goto label23;
									}
								}
								else
								{
									v0 /* $30 */ = ((int *) s1 /* $11 */)[11];
									goto label23;
								}
							}
						}
						else
						{
							t7 /* $27 */ = k1 & 0x00000018;
							if (!(t7 /* $27 */ == 0x00000000))
								goto label31;
							v0 /* $28 */ = ((int *) s1 /* $11 */)[11];
							goto label15;
						}
					}
				}
				else
				{
					goto label34;
				}
			}
		}
		sceKernelCpuResumeIntr (v0 /* $8 */);
		k1 = s4 /* $5 */;
		v1 /* $2 */ = s2 /* $4 */;
	}
	ra = ((int *) sp)[7];
	s6 /* $17 */ = ((int *) sp)[6];
	s5 /* $18 */ = ((int *) sp)[5];
	s4 /* $19 */ = ((int *) sp)[4];
	s3 /* $20 */ = ((int *) sp)[3];
	s2 /* $21 */ = ((int *) sp)[2];
	s1 /* $22 */ = ((int *) sp)[1];
	s0 /* $23 */ = ((int *) sp)[0];
	sp = sp + 0x00000020;
	return;
}

/**
* Subroutine at address 0x00001374
*/
void sceKernelSuspendSubIntr (int a0, int a1, int a2)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[0] = s0;
	s0 /* $1 */ = a0;
	((int *) sp)[2] = s2;
	v1 /* $2 */ = 0x80020065;
	s2 /* $3 */ = a2;
	((int *) sp)[1] = s1;
	s1 /* $4 */ = a1;
	((int *) sp)[4] = ra;
	((int *) sp)[3] = s3;
	if (!(((a0 < 0x00000043)) == 0x00000000))
	{
		v0 /* $7 */ = sceKernelCpuSuspendIntr ();
		t0 /* $8 */ = s0 /* $1 */ << 0x00000003;
		a3 /* $9 */ = t0 /* $8 */ - s0 /* $1 */;
		v1 /* $10 */ = (a3 /* $9 */ << 0x00000003) + 0x00003AE4;
		if (s1 /* $4 */ < 0)
		{

label16:
			s0 /* $13 */ = 0x80020065;
		}
		else
		{
			t2 /* $11 */ = ((unsigned char *) v1 /* $10 */)[48];
			t1 /* $12 */ = (s1 /* $4 */ < t2 /* $11 */);
			if (!(t1 /* $12 */ != 0x00000000))
				goto label16;
			t3 /* $20 */ = ((int *) v1 /* $10 */)[0];
			if (t3 /* $20 */ == 0x00000000)
			{

label14:
				s0 /* $13 */ = 0x80020068;
				if (!(s2 /* $3 */ == 0x00000000))
				{
					((int *) s2 /* $3 */)[0] = 0x00000000;
				}
			}
			else
			{
				v0 /* $21 */ = ((int *) v1 /* $10 */)[11];
				if (v0 /* $21 */ == 0x00000000)
					goto label14;
				v0 /* $22 */ = ((int *) v0 /* $21 */)[8];
				if (!(v0 /* $22 */ != 0x00000000))
					goto label14;
				v0 /* $25 */ v1 /* $26 */ = (*UNK) (s0 /* $1 */, s1 /* $4 */, s2 /* $3 */, a3 /* $9 */, t0 /* $8 */, t1 /* $12 */, t2 /* $11 */, t3 /* $20 */);
				s0 /* $13 */ = v0 /* $25 */;
			}
		}
		sceKernelCpuResumeIntr (v0 /* $7 */);
		v1 /* $2 */ = s0 /* $13 */;
	}
	ra = ((int *) sp)[4];
	s3 /* $16 */ = ((int *) sp)[3];
	s2 /* $17 */ = ((int *) sp)[2];
	s1 /* $18 */ = ((int *) sp)[1];
	s0 /* $19 */ = ((int *) sp)[0];
	sp = sp + 0x00000020;
	return;
}

/**
* Subroutine at address 0x00001458
*/
void QueryIntrHandlerInfo (int a0, int a1, int a2)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[3] = s3;
	s3 /* $1 */ = a1;
	((int *) sp)[2] = s2;
	s2 /* $2 */ = a0;
	a0 /* $3 */ = 0x80020065;
	((int *) sp)[1] = s1;
	s1 /* $4 */ = a2;
	((int *) sp)[5] = ra;
	((int *) sp)[4] = s4;
	((int *) sp)[0] = s0;
	if (!(((a0 < 0x00000043)) == 0x00000000))
	{
		a2 /* $5 */ = ((int *) a2)[0];
		a0 /* $3 */ = 0x8002006B;
		if (!(a2 /* $5 */ != 0x00000038))
		{
			v0 /* $8 */ = sceKernelCpuSuspendIntr ();
			s0 /* $9 */ = (((s2 /* $2 */ << 0x00000003) - s2 /* $2 */) << 0x00000003) + 0x00003AE4;
			s4 /* $10 */ = v0 /* $8 */;
			v0 /* $11 */ = ((unsigned char *) s0 /* $9 */)[48];
			if (v0 /* $11 */ == 0x00000000)
			{
				a3 /* $13 */ = ((int *) s0 /* $9 */)[2];

label16:
				v1 /* $14 */ = ((int *) s0 /* $9 */)[0];
				((short *) s1 /* $4 */)[8] = s2 /* $2 */;
				((int *) s1 /* $4 */)[2] = a3 /* $13 */;
				a2 /* $15 */ = ((int *) s0 /* $9 */)[1];
				((int *) s1 /* $4 */)[1] = v1 /* $14 */;
				((int *) s1 /* $4 */)[3] = a2 /* $15 */;
				a1 /* $16 */ = ((int *) s0 /* $9 */)[12];
				((short *) s1 /* $4 */)[10] = ((a1 /* $16 */ >> 9) & 0x00000003);
				v0 /* $19 */ = sub_000016FC (s2 /* $2 */);
				((short *) s1 /* $4 */)[11] = v0 /* $19 */;
				v0 /* $20 */ = ((int *) s0 /* $9 */)[8];
				v1 /* $21 */ = ((int *) s0 /* $9 */)[9];
				s3 /* $22 */ = ((unsigned char *) s0 /* $9 */)[48];
				t7 /* $23 */ = ((int *) s0 /* $9 */)[3];
				((int *) s1 /* $4 */)[8] = v0 /* $20 */;
				((int *) s1 /* $4 */)[9] = v1 /* $21 */;
				t8 /* $24 */ = ((int *) s0 /* $9 */)[4];
				t9 /* $25 */ = ((int *) s0 /* $9 */)[5];
				((short *) s1 /* $4 */)[9] = s3 /* $22 */;
				((int *) s1 /* $4 */)[10] = t8 /* $24 */;
				((int *) s1 /* $4 */)[11] = t9 /* $25 */;
				s2 /* $26 */ = ((int *) s0 /* $9 */)[6];
				s3 /* $27 */ = ((int *) s0 /* $9 */)[7];
				((int *) s1 /* $4 */)[6] = t7 /* $23 */;
				((int *) s1 /* $4 */)[12] = s2 /* $26 */;
				((int *) s1 /* $4 */)[13] = s3 /* $27 */;
				sceKernelCpuResumeIntr (s4 /* $10 */);
				a0 /* $3 */ = 0x00000000;
			}
			else
			{
				if (s3 /* $1 */ < 0)
				{

label10:
					if (s3 /* $1 */ == 0xFFFFFFFF)
					{

label15:
						a3 /* $13 */ = ((int *) s0 /* $9 */)[2];
						goto label16;
					}
					else
					{
						sceKernelCpuResumeIntr (s4 /* $10 */);
						a0 /* $3 */ = 0x80020065;
					}
				}
				else
				{
					if (((s3 /* $1 */ < v0 /* $11 */)) == 0x00000000)
						goto label10;
					t4 /* $12 */ = ((int *) s0 /* $9 */)[10];
					s0 /* $9 */ = ((int *) ((s3 /* $1 */ << 0x00000002) + t4 /* $12 */))[0];
					goto label15;
				}
			}
		}
	}
	ra = ((int *) sp)[5];
	s4 /* $30 */ = ((int *) sp)[4];
	s3 /* $31 */ = ((int *) sp)[3];
	s2 /* $32 */ = ((int *) sp)[2];
	s1 /* $33 */ = ((int *) sp)[1];
	s0 /* $34 */ = ((int *) sp)[0];
	sp = sp + 0x00000020;
	return;
}

#endif