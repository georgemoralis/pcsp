#ifndef sceMpeg_h__
#define sceMpeg_h__

namespace sceMpeg
{
    extern bool Reboot();
    extern bool ShutDown();

    extern int sceMpegGetAvcAu(); 
	extern int sceMpegQueryAtracEsSize(); 
	extern int sceMpegAvcDecodeStopYCbCr(); 
	extern int sceMpegAvcDecodeYCbCr(); 
	extern int sceMpegGetAtracAu(); 
	extern int sceMpegCreate(); 
	extern int sceMpegRingbufferQueryMemSize(); 
	extern int sceMpegFreeAvcEsBuf(); 
	extern int sceMpegQueryUserdataEsSize(); 
	extern int sceMpegQueryMemSize(); 
	extern int sceMpegQueryPcmEsSize(); 
	extern int sceMpegRingbufferAvailableSize(); 
	extern int sceMpegRingbufferPut(); 
	extern int sceMpegMallocAvcEsBuf(); 
	extern int sceMpegAvcDecodeMode(); 
	extern int sceMpegChangeGetAuMode(); 
	extern int sceMpegGetAvcEsAu(); 
	extern int sceMpegGetPcmAu(); 
	extern int sceMpegFinish(); 
	extern int sceMpegAtracDecode(); 
	extern int sceMpegRingbufferQueryPackNum(); 
	extern int sceMpeg_75E21135(); 
	extern int sceMpegAvcDecodeStop(); 
	extern int sceMpegFlushAllStream(); 
	extern int sceMpegInit(); 
	extern int sceMpegAvcInitYCbCr(); 
	extern int sceMpegQueryStreamSize(); 
	extern int sceMpegDelete(); 
	extern int sceMpegUnRegistStream(); 
	extern int sceMpegFlushStream(); 
	extern int sceMpegAvcDecodeFlush(); 
	extern int sceMpeg_42C679F6(); 
	extern int sceMpegRegistStream(); 
	extern int sceMpegNextAvcRpAu(); 
	extern int sceMpegRingbufferConstruct(); 
	extern int sceMpegAvcCsc(); 
	extern int sceMpegChangeGetAvcAuMode(); 
	extern int sceMpegQueryStreamOffset(); 
	extern int sceMpegAvcQueryYCbCrSize(); 
	extern int sceMpegInitAu(); 
	extern int sceMpegRingbufferDestruct(); 
	extern int sceMpegGetAvcNalAu(); 
	extern int sceMpegAvcDecodeDetail(); 
	extern int sceMpegAvcDecode(); 
	extern int sceMpegAvcCopyYCbCr(); 
	extern int sceMpegGetUserdataAu(); 
}
#endif // sceMpeg_h__
