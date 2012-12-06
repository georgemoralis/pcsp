#pragma once

#define V0 context.gpr[ALLEGREX_V0]
#define V1 context.gpr[ALLEGREX_V1]
#define A0 context.gpr[ALLEGREX_A0]
#define A1 context.gpr[ALLEGREX_A1]
#define A2 context.gpr[ALLEGREX_A2]
#define A3 context.gpr[ALLEGREX_A3]
#define T0 context.gpr[ALLEGREX_T0]
#define T1 context.gpr[ALLEGREX_T1]
#define T2 context.gpr[ALLEGREX_T2]
#define T3 context.gpr[ALLEGREX_T3]

#define F0  context.fpr[ALLEGREX_F0]
#define F12 context.fpr[ALLEGREX_F12]
#define F13 context.fpr[ALLEGREX_F13]
#define F14 context.fpr[ALLEGREX_F14]
#define F15 context.fpr[ALLEGREX_F15]
#define F16 context.fpr[ALLEGREX_F16]
#define F17 context.fpr[ALLEGREX_F17]
#define F18 context.fpr[ALLEGREX_F18]
#define F19 context.fpr[ALLEGREX_F19]

#define V1V0 *((u64 *)(context.gpr + ALLEGREX_V0))
#define A1A0 *((u64 *)(context.gpr + ALLEGREX_A0))
#define A3A2 *((u64 *)(context.gpr + ALLEGREX_A2))
#define T1T0 *((u64 *)(context.gpr + ALLEGREX_T0))
#define T3T2 *((u64 *)(context.gpr + ALLEGREX_T2))

