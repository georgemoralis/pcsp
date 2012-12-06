#pragma once

#include "types.h"

#include "ge_TextureManager.h"

#define MAXTEXTURESIZE 512*512*4

extern u8 	tempTexture[8][MAXTEXTURESIZE];

class ge_DecodedTexture;
class ge_TextureDecoder
{
public:
	ge_TextureDecoder();
	~ge_TextureDecoder();

	void	LoadClut();
    u16    *GetClut16();
    u32    *GetClut32();
	void	DecodeTexture(ge_DecodedTexture* outDecodedTexture, u32 inTextureAddress[8]);

private:
    template< int bitsPerPixel >
    void    UnswizzleTexture(ge_DecodedTexture* outDecodedTexture, void* out_buffer, u32 level);
};

extern	ge_TextureDecoder	theTextureDecoder;