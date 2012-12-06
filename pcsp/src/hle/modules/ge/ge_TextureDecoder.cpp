#include "stdafx.h"

#include "common_base.h"
#include "ge_TextureDecoder.h"
#include "ge_Constants.h"
#include "ge_Context.h"
#include "memory/memory.h"
#include "log.h"
#include "ge_DisplayListInterpreter.h"

ge_TextureDecoder	theTextureDecoder;

u8 	tempTexture[8][MAXTEXTURESIZE];
u8  tempTextureSwizzle[MAXTEXTURESIZE];

__forceinline u32 clut_index(u32 index, u32 csa, u32 sft, u32 msk)
{
    return ((index >> sft) & msk) | (csa << 4);
}

ge_TextureDecoder::ge_TextureDecoder()
{

}

ge_TextureDecoder::~ge_TextureDecoder()
{

}

static __forceinline void unswizzle_fast(u8 const *out, u8 const *in, s32 const width, s32 const height)
{
    s32 blockx, blocky;
    s32 j;

    s32 width_blocks = (width / 16);
    s32 height_blocks = (height / 8);

    s32 dst_pitch = (width-16)/4;
    s32 dst_row = width * 8;

    u32 *src  = (u32 *)in;
    u8  *ydst = (u8  *)out;
    for (blocky = 0; blocky < height_blocks; ++blocky)
    {
        u8 *xdst = ydst;
        for (blockx = 0; blockx < width_blocks; ++blockx)
        {
            u32 *dst = (u32 *)xdst;
            for (j = 0; j < 8; ++j)
            {
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                dst += dst_pitch;
            }
            xdst += 16;
        }
        ydst += dst_row;
    }
}

template< int bitsPerPixel >
__forceinline void ge_TextureDecoder::UnswizzleTexture(ge_DecodedTexture* outDecodedTexture, void* buffer, u32 level)
{
    switch (bitsPerPixel)
    {
    case  4: unswizzle_fast((u8 const *)buffer, (u8 const *)Memory::addr< char >(outDecodedTexture->Parameters.texture_base_pointer[level]), outDecodedTexture->Parameters.texture_buffer_width[level]/2, outDecodedTexture->Parameters.texture_height[level]); break;
    case  8: unswizzle_fast((u8 const *)buffer, (u8 const *)Memory::addr< char >(outDecodedTexture->Parameters.texture_base_pointer[level]), outDecodedTexture->Parameters.texture_buffer_width[level]*1, outDecodedTexture->Parameters.texture_height[level]); break;
    case 16: unswizzle_fast((u8 const *)buffer, (u8 const *)Memory::addr< char >(outDecodedTexture->Parameters.texture_base_pointer[level]), outDecodedTexture->Parameters.texture_buffer_width[level]*2, outDecodedTexture->Parameters.texture_height[level]); break;
    case 32: unswizzle_fast((u8 const *)buffer, (u8 const *)Memory::addr< char >(outDecodedTexture->Parameters.texture_base_pointer[level]), outDecodedTexture->Parameters.texture_buffer_width[level]*4, outDecodedTexture->Parameters.texture_height[level]); break;
    }
}

void ge_TextureDecoder::DecodeTexture(ge_DecodedTexture* outDecodedTexture, u32 inTextureAddress[8])
{
    switch (theGeContext.texture_storage) 
    {
    case TPSM_PIXEL_STORAGE_MODE_4BIT_INDEXED: 
        {
            u32 csa = theGeContext.texture_clut_csa;
            u32 sft = theGeContext.texture_clut_sft;
            u32 msk = theGeContext.texture_clut_msk;

            switch (theGeContext.texture_clut_mode) 
            {
            case CMODE_FORMAT_16BIT_BGR5650:
            case CMODE_FORMAT_16BIT_ABGR5551:
            case CMODE_FORMAT_16BIT_ABGR4444: 
                {
                    outDecodedTexture->TextureByteAlignment = 2;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                        {
                            return;
                        }

                        u8  *ip;
                        u16 *cp = GetClut16();
                        u16 *op = (u16 *)outpointer;

                        if (theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 4 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip        = tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u8 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i += 2)
                        {
                            u8 index = *ip++;
                            *op++ = cp[clut_index((index >> 0) & 0xF, pal, sft, msk)];
                            *op++ = cp[clut_index((index >> 4) & 0xF, pal, sft, msk)];
                        }
                        break;
                    }
                }
                break;

            case CMODE_FORMAT_32BIT_ABGR8888: 
                {
                    outDecodedTexture->TextureByteAlignment = 4;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                        {
                            return;
                        }

                        u8  *ip;
                        u32 *cp = GetClut32();
                        u32 *op = (u32 *)outpointer;

                        if(theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 4 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip        = tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u8 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i += 2)
                        {
                            u8 index = *ip++;

                            *op++ = cp[clut_index((index >> 0) & 0xF, pal, sft, msk)];
                            *op++ = cp[clut_index((index >> 4) & 0xF, pal, sft, msk)];
                        }
                    }
                }
                break;
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_8BIT_INDEXED: 
        {
            u32 csa = theGeContext.texture_clut_csa;
            u32 sft = theGeContext.texture_clut_sft;
            u32 msk = theGeContext.texture_clut_msk;

            switch (theGeContext.texture_clut_mode) 
            {
            case CMODE_FORMAT_16BIT_BGR5650:
            case CMODE_FORMAT_16BIT_ABGR5551:
            case CMODE_FORMAT_16BIT_ABGR4444: 
                {
                    outDecodedTexture->TextureByteAlignment = 2;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                            return;

                        u8  *ip;
                        u16 *cp = GetClut16();
                        u16 *op = (u16 *)outpointer;

                        if (theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 8 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip        = tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u8 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i++)
                        {
                            u8 index = *ip++;

                            *op++ = cp[clut_index(index, pal, sft, msk)];
                        }
                    }
                }
                break;

            case CMODE_FORMAT_32BIT_ABGR8888: 
                {
                    outDecodedTexture->TextureByteAlignment = 4;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                        {
                            return;
                        }

                        u8  *ip;
                        u32 *cp = GetClut32();
                        u32 *op = (u32 *)outpointer;

                        if (theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 8 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip        = tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u8 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i++)
                        {
                            u8 index = *ip++;

                            *op++ = cp[clut_index(index, pal, sft, msk)];
                        }
                    }
                }
                break;
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_16BIT_INDEXED: 
        {
            u32 csa = theGeContext.texture_clut_csa;
            u32 sft = theGeContext.texture_clut_sft;
            u32 msk = theGeContext.texture_clut_msk;

            switch (theGeContext.texture_clut_mode) 
            {
            case CMODE_FORMAT_16BIT_BGR5650:
            case CMODE_FORMAT_16BIT_ABGR5551:
            case CMODE_FORMAT_16BIT_ABGR4444: 
                {
                    outDecodedTexture->TextureByteAlignment = 2;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                        {
                            return;
                        }

                        u16 *ip;
                        u16 *cp = GetClut16();
                        u16 *op = (u16 *)outpointer;

                        if(theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 16 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip = (u16 *)tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u16 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i++)
                        {
                            u16 index = *ip++;

                            *op++ = cp[clut_index(index, pal, sft, msk)];
                        }
                    }
                }
                break;

            case CMODE_FORMAT_32BIT_ABGR8888: 
                {
                    outDecodedTexture->TextureByteAlignment = 4;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                        {
                            return;
                        }

                        u16 *ip;
                        u32 *cp = GetClut32();
                        u32 *op = (u32 *)outpointer;

                        if (theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 16 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip = (u16 *)tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u16 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i++)
                        {
                            u16 index = *ip++;

                            *op++ = cp[clut_index(index, pal, sft, msk)];
                        }
                    }
                }
                break;
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_32BIT_INDEXED: 
        {
            u32 csa = theGeContext.texture_clut_csa;
            u32 sft = theGeContext.texture_clut_sft;
            u32 msk = theGeContext.texture_clut_msk;

            switch (theGeContext.texture_clut_mode) 
            {
            case CMODE_FORMAT_16BIT_BGR5650:
            case CMODE_FORMAT_16BIT_ABGR5551:
            case CMODE_FORMAT_16BIT_ABGR4444: 
                {
                    outDecodedTexture->TextureByteAlignment = 2;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                        {
                            return;
                        }

                        u32 *ip;
                        u16 *cp = GetClut16();
                        u16 *op = (u16 *)outpointer;

                        if (theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 32 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip = (u32 *)tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u32 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i++)
                        {
                            u32 index = *ip++;

                            *op++ = cp[clut_index(index, pal, sft, msk)];
                        }
                    }
                }
                break;

            case CMODE_FORMAT_32BIT_ABGR8888: 
                {
                    outDecodedTexture->TextureByteAlignment = 4;

                    for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
                    {
                        void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                        void *outpointer = tempTexture[level];

                        if (theGeContext.texture_clut_address == 0)
                        {
                            return;
                        }

                        u32 *ip;
                        u32 *cp = GetClut32();
                        u32 *op = (u32 *)outpointer;

                        if (theGeContext.texture_swizzle)
                        {
                            UnswizzleTexture< 32 >(outDecodedTexture, tempTextureSwizzle, level);
                            inpointer = tempTextureSwizzle;
                            ip = (u32 *)tempTextureSwizzle;
                        }
                        else
                        {
                            ip = (u32 *)inpointer;
                        }

                        int length = theGeContext.texture_buffer_width[level]*theGeContext.texture_height[level];

                        u32 pal = csa + (theGeContext.mipmap_share_clut ? 0 : level);

                        for (int i = 0; i < length; i++)
                        {
                            u32 index = *ip++;

                            *op++ = cp[clut_index(index, pal, sft, msk)];
                        }
                    }
                }
                break;
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_16BIT_BGR5650:
    case TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR5551:
    case TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR4444: 
        {
            outDecodedTexture->TextureByteAlignment = 2;

            for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
            {
                void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                void *outpointer = tempTexture[level];

                if (!theGeContext.texture_swizzle) 
                {
                    int length = max(theGeContext.texture_buffer_width[level], theGeContext.texture_width[level]) * theGeContext.texture_height[level];
                    int size = length * sizeof(u32);
                    memcpy(outpointer, inpointer, size);
                }
                else
                {
                    UnswizzleTexture< 16 >(outDecodedTexture, outpointer, level);
                }
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_32BIT_ABGR8888:
        {
            outDecodedTexture->TextureByteAlignment = 4;

            for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
            {
                void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                void *outpointer = tempTexture[level];

                if (!theGeContext.texture_swizzle) 
                {
                    int length = max(theGeContext.texture_buffer_width[level], theGeContext.texture_width[level]) * theGeContext.texture_height[level];
                    int size = length * sizeof(u32);
                    memcpy(outpointer, inpointer, size);
                }
                else
                {
                    UnswizzleTexture< 32 >(outDecodedTexture, outpointer, level);
                }
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_DXT1:
        {
            outDecodedTexture->TextureByteAlignment = 4;

            for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
            {
                void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                void *outpointer = tempTexture[level];

                u32 *ip = (u32 *)inpointer;
                u32 *op = (u32 *)outpointer;

                for (u32 y = 0; y < outDecodedTexture->Parameters.texture_height[level]; y += 4)
                {
                    u32 x = 0;

                    for (; x < outDecodedTexture->Parameters.texture_buffer_width[level]; x += 4, ip += 2)
                    {
                        *op++ = ip[1];
                        *op++ = ip[0];
                    }
                    for (; x < outDecodedTexture->Parameters.texture_width[level]; x += 4)
                    {
                        *op++ = 0;
                        *op++ = 0;
                    }
                }
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_DXT3:
        {
            outDecodedTexture->TextureByteAlignment = 2;

            for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
            {
                void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                void *outpointer = tempTexture[level];

                u32 *ip = (u32 *)inpointer;
                u32 *op = (u32 *)outpointer;

                for (u32 y = 0; y < outDecodedTexture->Parameters.texture_height[level]; y += 4)
                {
                    u32 x = 0;

                    for (; x < outDecodedTexture->Parameters.texture_buffer_width[level]; x += 4, ip += 4)
                    {
                        *op++ = ip[2];
                        *op++ = ip[3];
                        *op++ = ip[1];
                        *op++ = ip[0];
                    }
                    for (; x < outDecodedTexture->Parameters.texture_width[level]; x += 4)
                    {
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                    }
                }
            }
        }
        break;

    case TPSM_PIXEL_STORAGE_MODE_DXT5:
        {
            outDecodedTexture->TextureByteAlignment = 2;

            for (u32 level = 0; level <= theGeContext.texture_num_mip_maps; ++level) 
            {
                void *inpointer  = Memory::addr< void >(inTextureAddress[level]);
                void *outpointer = tempTexture[level];

                u16 *ip = (u16 *)inpointer;
                u16 *op = (u16 *)outpointer;

                for (u32 y = 0; y < outDecodedTexture->Parameters.texture_height[level]; y += 4)
                {
                    u32 x = 0;

                    for (; x < outDecodedTexture->Parameters.texture_buffer_width[level]; x += 4, ip += 8)
                    {
                        *op++ = ip[7];
                        *op++ = ip[4];
                        *op++ = ip[5];
                        *op++ = ip[6];
                        *op++ = ip[2];
                        *op++ = ip[3];
                        *op++ = ip[0];
                        *op++ = ip[1];
                    }
                    for (; x < outDecodedTexture->Parameters.texture_width[level]; x += 4)
                    {
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                        *op++ = 0;
                    }
                }

            }
        }
        break;

    default: 
        {
            Panic();
            break;
        }
	}
}

void ge_TextureDecoder::LoadClut()
{
    if (!theGeContext.texture_clut_is_dirty)
    {
        return;
    }
    if (theGeContext.texture_storage >= TPSM_PIXEL_STORAGE_MODE_4BIT_INDEXED && theGeContext.texture_storage <= TPSM_PIXEL_STORAGE_MODE_32BIT_INDEXED) 
    {
        if (theGeContext.texture_clut_mode == CMODE_FORMAT_32BIT_ABGR8888) 
        {
            GetClut32();
        }
        else
        {
            GetClut16();
        }
    }
}

u16 *ge_TextureDecoder::GetClut16()
{
    return Memory::addr< u16 >(theGeContext.texture_clut_address);
}

u32 *ge_TextureDecoder::GetClut32()
{
    return Memory::addr< u32 >(theGeContext.texture_clut_address);
}
