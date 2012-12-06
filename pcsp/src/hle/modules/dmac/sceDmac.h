#ifndef sceDmac_h__
#define sceDmac_h__

namespace sceDmac
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int sceDmacTryMemcpy(); 
	extern int sceDmacMemcpy(); 
}
#endif // sceDmac_h__
