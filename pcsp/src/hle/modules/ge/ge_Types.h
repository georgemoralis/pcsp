#pragma once

struct geColor
{
	float r,g,b,a;
};

enum ge_matrix_type
{
	SCE_GE_MTXNO_BONE0,
	SCE_GE_MTXNO_BONE1,
	SCE_GE_MTXNO_BONE2,
	SCE_GE_MTXNO_BONE3,
	SCE_GE_MTXNO_BONE4,
	SCE_GE_MTXNO_BONE5,
	SCE_GE_MTXNO_BONE6,
	SCE_GE_MTXNO_BONE7,
	SCE_GE_MTXNO_WORLD,
	SCE_GE_MTXNO_VIEW,
	SCE_GE_MTXNO_PROJ,
	SCE_GE_MTXNO_TEXGEN
};

typedef struct SceGeContext 
{
	unsigned int buffer[512];
} SceGeContext;

typedef struct SceGeStack 
{
	unsigned int buffer[8];
} SceGeStack;

typedef struct SceGeListOptParam 
{
	unsigned int size; /* the size of SceGeListOptParam */
	SceGeContext * pGeContext;
	int nStackDepth;
	SceGeStack * pStackBuf;
} SceGeListOptParam;

typedef struct SceGeCbParam 
{
	void (*pSignalFunc)(int intrcode, void *cookie, const void *madr);
	void *pSignalCookie;
	void (*pFinishFunc)(int intrcode, void *cookie, const void *madr);
	void *pFinishCookie;
} SceGeCbParam;

typedef struct SceGeBreakParam 
{
	unsigned int buf[4];
} SceGeBreakParam;

#define SCE_ERROR_INVALID_INDEX 0x80000102