#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "kirk.h"
#include "keys144byte.h"
#include "keys16byte.h"
#include "PrxDec.h"

static TAG_INFO const* GetTagInfo(u32 tagFind) {
	int iTag;

	for (iTag = 0; iTag < sizeof(g_tagInfo)/sizeof(TAG_INFO); iTag++)
		if (g_tagInfo[iTag].tag == tagFind) {
			return &g_tagInfo[iTag];
		}

	return NULL;
}

static TAG_INFO2 *GetTagInfo2(u32 tagFind) {
	int iTag;

	for (iTag = 0; iTag < sizeof(g_tagInfo2) / sizeof(TAG_INFO2); iTag++)
		if (g_tagInfo2[iTag].tag == tagFind) {
			return &g_tagInfo2[iTag];
		}

	return NULL;
}

static int Scramble(u32 *buf, u32 size, u32 code) {
	buf[0] = 5;
	buf[1] = buf[2] = 0;
	buf[3] = code;
	buf[4] = size;

	sceUtilsBufferCopyWithRange(buf, size+0x14, buf, size+0x14, 7);

	return 0;
}

static void ExtraV2Mangle(u8* buffer1, u8 codeExtra) {
	static u8 g_dataTmp[20+0xA0];
	u8* buffer2 = g_dataTmp;

	memcpy(buffer2+20, buffer1, 0xA0);
	u32* pl2 = (u32*)buffer2;
	pl2[0] = 5;
	pl2[1] = pl2[2] = 0;
	pl2[3] = codeExtra;
	pl2[4] = 0xA0;

	sceUtilsBufferCopyWithRange(buffer2, 20+0xA0, buffer2, 20+0xA0, 7);

	memcpy(buffer1, buffer2, 0xA0);
}

static void PatchELFTag(u8* buffer) {
	buffer[0] = 0x7F;
	buffer[1] = 0x45;
	buffer[2] = 0x4C;
	buffer[3] = 0x46;
	buffer[4] = 0x01;
	buffer[5] = 0x01;
	buffer[6] = 0x01;
	buffer[7] = 0x00;
	buffer[8] = 0x00;
	buffer[9] = 0x00;
	buffer[10] = 0x00;
	buffer[11] = 0x00;
	buffer[12] = 0x00;
	buffer[13] = 0x00;
	buffer[14] = 0x00;
	buffer[15] = 0x00;
}

int prx_decrypter::DecryptPRX1(const u8* pbIn, u8* pbOut, int cbTotal, u32 tag) {
	kirk_init();

	TAG_INFO const* pti = GetTagInfo(tag);
	if (pti == NULL) { 
		return -1; 
	}

	memcpy(pbOut, pbIn, cbTotal);
	memset(pbOut, 0, 0x150);
	memset(pbOut, 0x55, 0x40);

	u32* pl = (u32*)(pbOut+0x2C);
	pl[0] = 5;
	pl[1] = pl[2] = 0;
	pl[3] = pti->code;
	pl[4] = 0x70;

	u8 buffer1[0x150];
	memcpy(buffer1+0x00, pbIn+0xD0, 0x80);
	memcpy(buffer1+0x80, pbIn+0x80, 0x50);
	memcpy(buffer1+0xD0, pbIn+0x00, 0x80);

	if (pti->codeExtra != 0) {
		ExtraV2Mangle(buffer1+0x10, pti->codeExtra);
	}
	memcpy(pbOut+0x40, buffer1+0x40, 0x40);

	int iXOR;
	for (iXOR = 0; iXOR < 0x70; iXOR++) {
		pbOut[0x40+iXOR] = pbOut[0x40+iXOR] ^ pti->key[0x14+iXOR];
	}

	sceUtilsBufferCopyWithRange(pbOut+0x2C, 20+0x70, pbOut+0x2C, 20+0x70, 7);

	for (iXOR = 0x6F; iXOR >= 0; iXOR--) {
		pbOut[0x40+iXOR] = pbOut[0x2C+iXOR] ^ pti->key[0x20+iXOR];
	}

	memset(pbOut+0x80, 0, 0x30);
	pbOut[0xA0] = 1;
	memcpy(pbOut+0xB0, pbIn+0xB0, 0x20);
	memcpy(pbOut+0xD0, pbIn+0x00, 0x80);

	sceUtilsBufferCopyWithRange(pbOut, cbTotal, pbOut+0x40, cbTotal-0x40, 0x1);

	memset(pbOut, 0, 0x10);
	PatchELFTag(pbOut);

	return *(u32*)&pbIn[0xB0];
}

int prx_decrypter::DecryptPRX2(const u8 *inbuf, u8 *outbuf, u32 size, u32 tag) {
	kirk_init();

	TAG_INFO2 * pti = GetTagInfo2(tag);
	if (!pti) { 
		return -1;
	}

	int retsize = *(int *)&inbuf[0xB0];
	u8 tmp1[0x150], tmp2[0x90+0x14], tmp3[0x60+0x14];

	memset(tmp1, 0, 0x150);
	memset(tmp2, 0, 0x90+0x14);
	memset(tmp3, 0, 0x60+0x14);

	memcpy(outbuf, inbuf, size);

	memcpy(tmp1, outbuf, 0x150);

	int i, j;
	u8 *p = tmp2+0x14;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 0x10; j++) {
			p[(i << 4) + j] = pti->key[j];
		}
		p[(i << 4)] = i;
	}	

	Scramble((u32 *)tmp2, 0x90, pti->code);

	memcpy(outbuf, tmp1+0xD0, 0x5C);
	memcpy(outbuf+0x5C, tmp1+0x140, 0x10);
	memcpy(outbuf+0x6C, tmp1+0x12C, 0x14);
	memcpy(outbuf+0x80, tmp1+0x080, 0x30);
	memcpy(outbuf+0xB0, tmp1+0x0C0, 0x10);
	memcpy(outbuf+0xC0, tmp1+0x0B0, 0x10);
	memcpy(outbuf+0xD0, tmp1+0x000, 0x80);

	memcpy(tmp3+0x14, outbuf+0x5C, 0x60);	

	Scramble((u32 *)tmp3, 0x60, pti->code);

	memcpy(outbuf+0x5C, tmp3, 0x60);
	memcpy(tmp3, outbuf+0x6C, 0x14);
	memcpy(outbuf+0x70, outbuf+0x5C, 0x10);
	memset(outbuf+0x18, 0, 0x58);
	memcpy(outbuf+0x04, outbuf, 0x04);

	*((u32 *)outbuf) = 0x014C;
	memcpy(outbuf+0x08, tmp2, 0x10);

	sceUtilsBufferCopyWithRange(outbuf, size, outbuf, size, 0x0B);
	
	int iXOR;

	for (iXOR = 0; iXOR < 0x40; iXOR++) {
		tmp3[iXOR+0x14] = outbuf[iXOR+0x80] ^ tmp2[iXOR+0x10];
	}

	Scramble((u32 *)tmp3, 0x40, pti->code);
	
	for (iXOR = 0x3F; iXOR >= 0; iXOR--) {
		outbuf[iXOR+0x40] = tmp3[iXOR] ^ tmp2[iXOR+0x50];
	}

	memset(outbuf+0x80, 0, 0x30);
	*(u32 *)&outbuf[0xA0] = 1;

	memcpy(outbuf+0xB0, outbuf+0xC0, 0x10);
	memset(outbuf+0xC0, 0, 0x10);

	sceUtilsBufferCopyWithRange(outbuf, size, outbuf+0x40, size-0x40, 0x1);

	memset(outbuf, 0, 0x10);
	PatchELFTag(outbuf);

	if (retsize < 0x150) {
		memset(outbuf+retsize, 0, 0x150-retsize);		
	}

	return retsize;
}