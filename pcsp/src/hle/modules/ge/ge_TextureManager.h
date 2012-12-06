#pragma once

#include <map>

#include "ge_Constants.h"
#include "ge_Decoder.h"

struct ge_TextureData
{
	u32 texture_base_pointer[8];
	u32 texture_buffer_width[8];
	u32 texture_width[8];
	u32 texture_height[8];
	u32 texture_storage;
	u32 texture_clut_addr;
	u32 texture_clut_mode;
	u32 texture_clut_start;
	u32 texture_clut_shift;
	u32 texture_clut_mask;
	u32 texture_clut_np;
    u32 texture_clut_mipmap_shared;
	u32 texture_mipmap_max;
    u32 palette[32*8];

    u32 Key() const
    {
        u32 result = 0;
        for (u32 *p = (u32 *)this, *e = (u32 *)this + sizeof(ge_TextureData)/sizeof(u32); p < e; ++p)
        {
            result ^= *p;
        }
        for (u32 i = 0; i <= texture_mipmap_max; ++i)
        {
            u32 n = max(texture_buffer_width[i], texture_width[i]) * texture_height[i];
            switch (texture_storage)
            {
            case TPSM_PIXEL_STORAGE_MODE_16BIT_BGR5650:
            case TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR5551:
            case TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR4444:
            case TPSM_PIXEL_STORAGE_MODE_16BIT_INDEXED:
                n /= 2;
                break;
            case TPSM_PIXEL_STORAGE_MODE_32BIT_ABGR8888:
            case TPSM_PIXEL_STORAGE_MODE_32BIT_INDEXED:
                break;
            case TPSM_PIXEL_STORAGE_MODE_DXT1:
                n = ((texture_width[i] + 3) / 4)*((texture_width[i] + 3) / 4)*2;
                break;
            case TPSM_PIXEL_STORAGE_MODE_DXT3:
            case TPSM_PIXEL_STORAGE_MODE_DXT5:
                n = ((texture_width[i] + 3) / 4)*((texture_width[i] + 3) / 4)*4;
                break;
            case TPSM_PIXEL_STORAGE_MODE_4BIT_INDEXED:
                n /= 8;
                break;
            case TPSM_PIXEL_STORAGE_MODE_8BIT_INDEXED:
                n /= 4;
                break;
            }

            u32 d;
            for (d = 1; d*d < n*sizeof(u32); ++d); 
            u32 *p = Memory::addr< u32 >(texture_base_pointer[i]);
            for (u32 *e = p + n; p < e; p += d)
            {
                result ^= *p;
            }
        }
        return result;
    }

    bool operator == (ge_TextureData const &theOther) const
    {
        return 0 == memcmp(this, &theOther, sizeof(ge_TextureData));
    }
};

class ge_DecodedTexture
{
public:
	ge_DecodedTexture()
	{
		TextureByteAlignment = 4;
	}

	void           *Resource; // this cannot be a type since rasterizer can be of any type
	ge_TextureData	Parameters;
	u32				TextureByteAlignment;
};


class ge_TextureManager
{
public:
	ge_TextureManager();
	~ge_TextureManager();

	void SetTexture();

	ge_DecodedTexture *GetTextureFromCache(ge_TextureData *data);

private:
    typedef std::map< u32, ge_DecodedTexture > TextureCache;
    
    TextureCache mTextureCache;
	
	u32	mCacheHits;
	u32	mCacheMisses;
};

extern ge_TextureManager	theTextureManager;


