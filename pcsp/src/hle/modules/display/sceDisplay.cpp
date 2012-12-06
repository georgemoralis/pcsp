#include "stdafx.h"
#include "sceDisplay.h"
#include "hle/types.h"
#include "log.h"
#include "renderer.h"
#include "kernel/kernel_types.h"
#include "kernel/kernel_vsync.h"
#include "common/common_timer.h"
#include "../ge/sceGe_user.h"
#include "../ge/ge_Context.h"

extern volatile int vsync_limiter;



namespace sceDisplay
{
	int sizeOfTextureType[] = {
		2, // TPSM_PIXEL_STORAGE_MODE_16BIT_BGR5650
		2, // TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR5551
		2, // TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR4444
		4, // TPSM_PIXEL_STORAGE_MODE_32BIT_ABGR8888
		0, // TPSM_PIXEL_STORAGE_MODE_4BIT_INDEXED
        1, // TPSM_PIXEL_STORAGE_MODE_8BIT_INDEXED
        2, // TPSM_PIXEL_STORAGE_MODE_16BIT_INDEXED
        4, // TPSM_PIXEL_STORAGE_MODE_32BIT_INDEXED
        0, // TPSM_PIXEL_STORAGE_MODE_DXT1
        0, // TPSM_PIXEL_STORAGE_MODE_DXT3
        0, // TPSM_PIXEL_STORAGE_MODE_DXT5
        2, // RE_PIXEL_STORAGE_16BIT_INDEXED_BGR5650
        2, // RE_PIXEL_STORAGE_16BIT_INDEXED_ABGR5651
        2, // RE_PIXEL_STORAGE_16BIT_INDEXED_ABGR4444
        4  // RE_PIXEL_STORAGE_32BIT_INDEXED_ABGR8888
	};

	inline static int makePow2(int n) 
	{
         --n;
         n = (n >>  1) | n;
         n = (n >>  2) | n;
         n = (n >>  4) | n;
         n = (n >>  8) | n;
         n = (n >> 16) | n;
         return ++n;	
	}

    Timer timer;

    static bool sceDisplay_ready = false;

    bool Reboot()
    {
        ShutDown();
        sceDisplay_ready = true;
        return true;
    }

    bool ShutDown()
    {
        if (sceDisplay_ready)
        {
            sceDisplay_ready = false;
        }
        return true;
    }

	Timer theTimer;
	u64	 display_current_time;
	u64	 display_start_time;

    u32 mode;
    u32 width;
    u32 height;
	
	u32 bottomaddrFb;
	u32 topaddrFb;
	u32 bufferwidthFb;
    u32 pixelformatFb;
	
	u32 *pixelsFb;
	u32 sizeof_pixelsFb;
	u32 sync;

	float texS;
	float texT;

	bool detailsDirty;
	bool isFbShowing;
	bool gotBadFbBufParams;
	bool createTex;

    int hleGetVCount() 
    {
        // Vcount increases by 60 units per second
        display_current_time = theTimer.Get();
        return(int) ((display_current_time - display_start_time) * 60 / 1000000);
    }

	void Initialize()
	{
		display_start_time = theTimer.Get();

		detailsDirty = false;
		isFbShowing = false;
		gotBadFbBufParams = false;
		createTex = false;

		mode = 0;
		width = 0;
		height = 0;
		
		bottomaddrFb = 0;
		topaddrFb = 0;
		bufferwidthFb = 0;
		pixelformatFb  = 0;
		
		pixelsFb = 0;
		sizeof_pixelsFb = 0;
		

		sync = 0;

		texS = 0;
		texT = 0;
	}

    /// Mode functions

    int sceDisplaySetMode(u32 a0, u32 a1, u32 a2)
    {
        u32 mode   = int(a0);
        u32 width  = int(a1);
        u32 height = int(a2);
 
		/*
		TODO: add check that it cannot be called from interupt handler
		*/

		if (width <= 0 || height <= 0 )
		{
			return -1;
		} 
		else
		{
			sceDisplay::mode = mode;
			sceDisplay::width = width;
			sceDisplay::height = height;

            bottomaddrFb = topaddrFb + bufferwidthFb * height * sizeOfTextureType[pixelformatFb];
			detailsDirty = true;

            if (mode != 0) 
			{
				errorf(sceDisplay, "UNIMPLEMENTED sceDisplaySetMode mode=%d", mode);
            }

			return 0;
		}
    }

    int sceDisplayGetMode(u32 a0, u32 a1, u32 a2)
    {
        u32 modeAddr = a0;
        u32 widthAddr = a1;
        u32 heightAddr = a2;

        if (!Memory::IsAddressValid(modeAddr) || !Memory::IsAddressValid(widthAddr) || !Memory::IsAddressValid(heightAddr))
        {
            return -1;
        } 
		else 
		{
			(*Memory::addrw(modeAddr)) = mode;
			(*Memory::addrw(widthAddr)) = width;			
			(*Memory::addrw(heightAddr)) = height;
			return 0;
        }
    }

    int sceDisplaySetHoldMode(u32 a0)
    {
		debugf(sceDisplay, "Ignoring sceDisplaySetHoldMode");
		return 0;
    }

    int sceDisplaySetResumeMode()
    {
        //debugf(sceDisplay, "Ignoring sceDisplaySetHoldMode");
		errorf(sceDisplay,"UNIMPLEMENTED sceDisplaySetResumeMode instruction");
        return 0;
    }

    int sceDisplayGetResumeMode()
    {
        //TODO implement me
        errorf(sceDisplay,"UNIMPLEMENTED sceDisplayGetResumeMode instruction");
        return 0;
    }

    /// FrameBuffer functions

    int sceDisplaySetFrameBuf(u32 a0, u32 a1, u32 a2, u32 a3)
    {
        u32 topaddr = a0;
        u32 bufferwidth = a1;
        u32 pixelformat = a2;
        u32 syncType = a3;

		topaddr &= 0x3FFFFFFF; // mask the address;
		
        if ((bufferwidth < 0 || (bufferwidth & (bufferwidth - 1)) != 0) || ((bufferwidth == 0) && (topaddr != 0))) 
		{
            warnf(sceDisplay,"sceDisplaySetFrameBuf(topaddr=%h, bufferwidth=%h, pixelformat=%h, syncType=%h)  bad bufferwidth"
				, topaddr, bufferwidth, pixelformat, syncType);
            isFbShowing = false;
            gotBadFbBufParams = true;
			return SCE_ERROR_INVALID_SIZE;
        }
		else if (pixelformat < 0 || pixelformat > 3) 
		{
            warnf(sceDisplay,"sceDisplaySetFrameBuf(topaddr=%h, bufferwidth=%h, pixelformat=%h, syncType=%h)  bad pixelformat"
				, topaddr, bufferwidth, pixelformat, syncType);

            isFbShowing = false;
            gotBadFbBufParams = true;
            return -1;
        } 
		else if (syncType < 0 || syncType > 1) 
		{
            warnf(sceDisplay,"sceDisplaySetFrameBuf(topaddr=%h, bufferwidth=%h, pixelformat=%h, syncType=%h)  bad syncType"
				, topaddr, bufferwidth, pixelformat, syncType);

            isFbShowing = false;
            gotBadFbBufParams = true;
            return SCE_ERROR_INVALID_MODE;
        } 
		else if ((topaddr == 0)) 
		{
            // If topaddr is NULL, the PSP's screen will be displayed as fully black
            // as the output is blocked. Under these circumstances, bufferwidth can be 0.
            warnf(sceDisplay,"sceDisplaySetFrameBuf(topaddr=%h, bufferwidth=%h, pixelformat=%h, syncType=%h)  blocking displayoutput"
				, topaddr, bufferwidth, pixelformat, syncType);
            isFbShowing = false;
            gotBadFbBufParams = true;
            return 0;
        } 
		else if (Memory::IsAddressValid(topaddr))
		{
			if(topaddr < sceGe_user::START_VRAM || topaddr >= sceGe_user::END_VRAM) {
                warnf(sceDisplay, "sceDisplaySetFrameBuf (topaddr=0x%h is using main memory.", topaddr);
            }

            if (gotBadFbBufParams) 
			{
                gotBadFbBufParams = false;
            infof(sceDisplay,"sceDisplaySetFrameBuf(topaddr=%h, bufferwidth=%h, pixelformat=%h, syncType=%h)  ok"
				, topaddr, bufferwidth, pixelformat, syncType);
            }
			
            if (pixelformat != pixelformatFb || bufferwidth != bufferwidthFb || makePow2(height) != makePow2(height)) 
			{
                createTex = true;
            }

            topaddrFb     = topaddr;
            bufferwidthFb = bufferwidth;
            pixelformatFb = pixelformat;
            sync          = syncType;

            bottomaddrFb = topaddr + bufferwidthFb * height * sizeOfTextureType[pixelformatFb];
			pixelsFb = Memory::addrw(topaddr);
			sizeof_pixelsFb =  bottomaddrFb - topaddr;

            texS = (float)width / (float)bufferwidth;
            texT = (float)height / (float)makePow2(height);

            detailsDirty = true;

            isFbShowing = true;
			
			// make ge render my display buffer
    		if (theGeContext.fbp != topaddr || theGeContext.fbw != bufferwidth || theGeContext.psm != pixelformat) 
			{
    			theGeContext.fbp = topaddr;
    			theGeContext.fbw = bufferwidth;
    			theGeContext.psm = pixelformat;
				sceGe_user::geBufChanged = true;
    		}
		}
		
		// not yet sure where to swap buffers so this is the location until i know ... :)
        if (vsync_limiter)
        {
            KernelVsync::NextFrame();
        }
        theRenderer.Swap();
        static u64 prev_time = 0ULL;
        u64        last_time = timer.Get();
        u64        delta     = last_time - prev_time;
        tracef(sceAudio, "sceDisplaySetFrameBuf: %f", f32(delta) / 1000.0f);
        prev_time = last_time;
        return SCE_KERNEL_ERROR_OK;
    }

	int sceDisplayGetFrameBuf()
	{
		//TODO implement me
        errorf(sceDisplay,"UNIMPLEMENTED sceDisplayGetFrameBuf instruction");
		return 0;
	}

	f32 sceDisplayGetFramePerSec()
	{
    	return 59.940060f;
	}

	int sceDisplayIsForeground()
	{
    	debugf(sceDisplay, "sceDisplayIsForeground ret: %d" + isFbShowing);
		return isFbShowing ? 1 : 0;
	}

	int sceDisplay_77ED8B3A()
	{
		//TODO implement me
		errorf(sceDisplay,"UNIMPLEMENTED sceDisplay_77ED8B3A instruction");
		return 0;
	}

	int sceDisplay_40F1469C()
	{
		//TODO implement me
		errorf(sceDisplay,"UNIMPLEMENTED sceDisplay_40F1469C instruction");
		return 0;
	}

	int sceDisplayGetBrightness(u32 a0, u32 a1)
	{
        int leveladdr = a0;
        int unkaddr = a1;

        debugf(sceDisplay, "IGNORING: sceDisplayGetBrightness leveladdr=%h, unkaddr=%h", leveladdr, unkaddr);
		return 0;
	}

    /// VSYNC functions

    int sceDisplayGetVcount()
    {
        return hleGetVCount();
    }

    int sceDisplayIsVsync()
    {
        //TODO implement me
        errorf(sceDisplay,"UNIMPLEMENTED sceDisplayIsVsync instruction");
        return 0;
    }

    int sceDisplayWaitVblank()
    {
        sceDisplayWaitVblankStart();
        return 0;
    }

    int sceDisplayWaitVblankCB()
    {
        sceDisplayWaitVblankStart();
        return 0;
    }

    int sceDisplayWaitVblankStart()
    {
        return 0; 
    }

    int sceDisplayWaitVblankStartCB()
    {
        sceDisplayWaitVblankStart();
        return 0;
    }

    int sceDisplayIsVblank()
    {
        return 0;
    }

    int sceDisplayGetVblankRest()
    {
        //TODO implement me
        errorf(sceDisplay,"UNIMPLEMENTED sceDisplayGetVblankRest instruction");
        return 0;
    }

    /// HSYNC functions

    int sceDisplayGetCurrentHcount()
    {
        return int(hleGetVCount() * 0.15f);
    }

    int sceDisplayAdjustAccumulatedHcount()
    {
        return int(hleGetVCount() * 285.72f);
    }

    int sceDisplayGetAccumulatedHcount()
    {
        //TODO implement me
        errorf(sceDisplay,"UNIMPLEMENTED sceDisplayGetAccumulatedHcount instruction");
        return 0;
    }

}

namespace syscalls
{
    void sceDisplaySetMode(AlContext &context)                 { V0 = sceDisplay::sceDisplaySetMode(A0, A1, A2); }
    void sceDisplayGetMode(AlContext &context)                 { V0 = sceDisplay::sceDisplayGetMode(A0, A1, A2); }
    void sceDisplaySetHoldMode(AlContext &context)             { V0 = sceDisplay::sceDisplaySetHoldMode(A0); }
    void sceDisplaySetResumeMode(AlContext &context)           { V0 = sceDisplay::sceDisplaySetResumeMode(); }
    void sceDisplayGetResumeMode(AlContext &context)           { V0 = sceDisplay::sceDisplayGetResumeMode(); }

    void sceDisplaySetFrameBuf(AlContext &context)             { V0 = sceDisplay::sceDisplaySetFrameBuf(A0, A1, A2, A3); }
    void sceDisplayGetFrameBuf(AlContext &context)             { V0 = sceDisplay::sceDisplayGetFrameBuf(); }
	void sceDisplayGetFramePerSec(AlContext &context)          { F0 = sceDisplay::sceDisplayGetFramePerSec(); }
	void sceDisplayIsForeground(AlContext &context)            { V0 = sceDisplay::sceDisplayIsForeground(); }

    void sceDisplayGetVcount(AlContext &context)               { V0 = sceDisplay::sceDisplayGetVcount(); }
    void sceDisplayIsVsync(AlContext &context)                 { V0 = sceDisplay::sceDisplayIsVsync(); }
    void sceDisplayIsVblank(AlContext &context)                { V0 = sceDisplay::sceDisplayIsVblank(); }
    void sceDisplayWaitVblank(AlContext &context)              { V0 = sceDisplay::sceDisplayWaitVblank(); }
	void sceDisplayWaitVblankCB(AlContext &context)            { V0 = sceDisplay::sceDisplayWaitVblankCB(); }
    void sceDisplayWaitVblankStart(AlContext &context)         { V0 = sceDisplay::sceDisplayWaitVblankStart(); }
    void sceDisplayWaitVblankStartCB(AlContext &context)       { V0 = sceDisplay::sceDisplayWaitVblankStartCB(); }
    void sceDisplayGetVblankRest(AlContext &context)           { V0 = sceDisplay::sceDisplayGetVblankRest(); }

    void sceDisplay_77ED8B3A(AlContext &context)               { V0 = sceDisplay::sceDisplay_77ED8B3A(); }
	void sceDisplay_40F1469C(AlContext &context)               { V0 = sceDisplay::sceDisplay_40F1469C(); }

    void sceDisplayGetBrightness(AlContext &context)           { V0 = sceDisplay::sceDisplayGetBrightness(A0, A1); }

    void sceDisplayGetCurrentHcount(AlContext &context)        { V0 = sceDisplay::sceDisplayGetCurrentHcount(); }
    void sceDisplayGetAccumulatedHcount(AlContext &context)    { V0 = sceDisplay::sceDisplayGetAccumulatedHcount(); }
    void sceDisplayAdjustAccumulatedHcount(AlContext &context) { V0 = sceDisplay::sceDisplayAdjustAccumulatedHcount(); }
}
