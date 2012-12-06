#include "stdafx.h"
#include "ge_TextureManager.h"
#include "ge_Decoder.h"
#include "ge_TextureDecoder.h"
#include "ge_Constants.h"
#include "ge_Context.h"
#include "memory/memory.h"
#include "renderer.h"

ge_TextureManager	theTextureManager;



ge_TextureManager::ge_TextureManager()
{
	mCacheHits		= 0;
	mCacheMisses	= 0;
}

ge_TextureManager::~ge_TextureManager()
{

}

void ge_TextureManager::SetTexture()
{
	if (theGeContext.clear_mode_enable || !theGeContext.texture_mapping_enable) 
    {
        return;
    }
        
    ge_DecodedTexture Texture;
    u32 i = 0;
    for (;i <= theGeContext.texture_num_mip_maps; ++i)
    {
		Texture.Parameters.texture_base_pointer[i] = theGeContext.texture_base_pointer[i] & Memory::address_mask;		
        Texture.Parameters.texture_buffer_width[i] = theGeContext.texture_buffer_width[i];
        Texture.Parameters.texture_width[i]		   = theGeContext.texture_width[i];				
        Texture.Parameters.texture_height[i]	   = theGeContext.texture_height[i];
    }
    for (; i <= 7; ++i)
    {
        Texture.Parameters.texture_base_pointer[i] = 0;		
        Texture.Parameters.texture_buffer_width[i] = 0;
        Texture.Parameters.texture_width[i]		   = 0;				
        Texture.Parameters.texture_height[i]	   = 0;
    }
    Texture.Parameters.texture_storage            = theGeContext.texture_storage;			
    Texture.Parameters.texture_clut_addr          = theGeContext.texture_clut_address;				
    Texture.Parameters.texture_clut_mode          = theGeContext.texture_clut_mode;				
    Texture.Parameters.texture_clut_start         = theGeContext.texture_clut_csa;				
    Texture.Parameters.texture_clut_shift         = theGeContext.texture_clut_sft;				
    Texture.Parameters.texture_clut_mask          = theGeContext.texture_clut_msk;				
    Texture.Parameters.texture_clut_np            = theGeContext.texture_clut_np;		
    Texture.Parameters.texture_clut_mipmap_shared = theGeContext.mipmap_share_clut;
    Texture.Parameters.texture_mipmap_max         = theGeContext.texture_num_mip_maps;		
    if (Texture.Parameters.texture_clut_addr)
    {
        memcpy(Texture.Parameters.palette, Memory::addr< u32 >(Texture.Parameters.texture_clut_addr), 256*sizeof(u32));
    }
    else
    {
        memset(Texture.Parameters.palette, 0, 256*sizeof(u32));
    }

    u32 key = Texture.Parameters.Key();

    TextureCache::iterator entry = mTextureCache.find(key);

    if (entry != mTextureCache.end())
    {
        if (entry->second.Parameters == Texture.Parameters)
        {
            mCacheHits++;

            theRenderer.SetTexture(&entry->second);
            return;
        }

        mCacheMisses++;
        if (entry->second.Resource)
        {
            theRenderer.DeleteTexture(&entry->second);
        }
        mTextureCache.erase(entry);
    }

	// we have to decode
	theTextureDecoder.DecodeTexture(&Texture, Texture.Parameters.texture_base_pointer);
	theRenderer.CreateTexture(&Texture);
	theRenderer.SetTexture(&Texture);
	mTextureCache[Texture.Parameters.Key()] = Texture;
}

ge_DecodedTexture *ge_TextureManager::GetTextureFromCache(ge_TextureData *data)
{
    TextureCache::iterator entry = mTextureCache.find(data->Key());

	if (entry != mTextureCache.end())
	{
        if (entry->second.Parameters == *data)
        {
            mCacheHits++;

            return &entry->second;
        }

        mCacheMisses++;
        if (entry->second.Resource)
        {
            theRenderer.DeleteTexture(&entry->second);
        }
        mTextureCache.erase(entry);
	}

	return 0;
}
