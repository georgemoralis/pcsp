#ifndef EMULATOR_MEMORY_H_
#define EMULATOR_MEMORY_H_

#include "types.h"

//	0x00010000	0x00004000 (16 KiB)	Scratch pad
//	0x04000000	0x00200000 (2 MiB)	Lower video ram
//	0x04800000	0x00200000 (2 MiB)	Upper video ram (SLIM only)
//	0x08000000	0x02000000 (32 MiB)	Lower main ram
//	0x0A000000	0x02000000 (32 MiB)	Upper main ram (SLIM only)

#define ECTX_START 0x00000000
#define VMEM_START 0x00000000
#define SRAM_START 0x00010000
#define VRAM_START 0x04000000
#define MRAM_START 0x08000000

#define SRAM_SIZE 0x00004000
#define ECTX_SIZE 0x00010000
#define GARB_SIZE 0x00020000
#define VRAM_SIZE 0x00200000
#define MRAM_SIZE 0x04000000
#define VMEM_SIZE 0x10000000

#ifndef KB
#define KB *1024
#endif
#ifndef MB
#define MB *1024 KB
#endif
#ifndef GB
#define GB *1024 * MB
#endif

union vmem_u
{
	s8  b[VMEM_SIZE];
	u8  bu[VMEM_SIZE];
	s16 h[VMEM_SIZE/2];
	u16 hu[VMEM_SIZE/2];
	u32 w[VMEM_SIZE/4];
	f32 f[VMEM_SIZE/4];
};

union sram_u
{
    s8  b[SRAM_SIZE];
    u8  bu[SRAM_SIZE];
    s16 h[SRAM_SIZE/2];
    u16 hu[SRAM_SIZE/2];
    u32 w[SRAM_SIZE/4];
    f32 f[SRAM_SIZE/4];
};

union vram_u
{
    s8  b[VRAM_SIZE];
    u8  bu[VRAM_SIZE];
    s16 h[VRAM_SIZE/2];
    u16 hu[VRAM_SIZE/2];
    u32 w[VRAM_SIZE/4];
    f32 f[VRAM_SIZE/4];
};

union mram_u
{
    s8  b[MRAM_SIZE];
    u8  bu[MRAM_SIZE];
    s16 h[MRAM_SIZE/2];
    u16 hu[MRAM_SIZE/2];
    u32 w[MRAM_SIZE/4];
    f32 f[MRAM_SIZE/4];
};

namespace Memory
{
	extern void * pointer;

	u32 const address_mask = 0x3FFFFFFF;

	template< typename T >
    static __forceinline T *      addr(u32 address)   { return reinterpret_cast< T * >(reinterpret_cast< char * > (Memory::pointer) + VMEM_SIZE + (address & (VMEM_SIZE - 1))); }
	static __forceinline s8 *     addrb(u32 address)  { return addr< s8 >(address); }
	static __forceinline u8 *     addrbu(u32 address) { return addr< u8 >(address); }
	static __forceinline s16 *    addrh(u32 address)  { return addr< s16 >(address); }
	static __forceinline u16 *    addrhu(u32 address) { return addr< u16 >(address); }
	static __forceinline u32 *    addrw(u32 address)  { return addr< u32 >(address); }
	static __forceinline f32 *    addrf(u32 address)  { return addr< f32 >(address); }

    template< typename T >
    static __forceinline T *      xaddr(u32 address)   { return reinterpret_cast< T * >(reinterpret_cast< char * > (Memory::pointer) + (address & (VMEM_SIZE - 1))); }
    static __forceinline s8 *     xaddrb(u32 address)  { return addr< s8 >(address); }
    static __forceinline u8 *     xaddrbu(u32 address) { return addr< u8 >(address); }
    static __forceinline s16 *    xaddrh(u32 address)  { return addr< s16 >(address); }
    static __forceinline u16 *    xaddrhu(u32 address) { return addr< u16 >(address); }
    static __forceinline u32 *    xaddrw(u32 address)  { return addr< u32 >(address); }
    static __forceinline f32 *    xaddrf(u32 address)  { return addr< f32 >(address); }

    template< typename T >
    static __forceinline T &      mem(u32 address)    { return *addr< T >(address); }
    static __forceinline s8 &     memb(u32 address)   { return *addrb(address); }
    static __forceinline u8 &     membu(u32 address)  { return *addrbu(address); }
    static __forceinline s16 &    memh(int address)   { return *addrh(address); }
    static __forceinline u16 &    memhu(u32 address)  { return *addrhu(address); }
    static __forceinline u32 &    memw(u32 address)   { return *addrw(address); }
    static __forceinline f32 &    memf(u32 address)   { return *addrf(address); }

    template< typename T >
    static __forceinline T &      xmem(u32 address)    { return *xaddr< T >(address); }
    static __forceinline s8 &     xmemb(u32 address)   { return *xaddrb(address); }
    static __forceinline u8 &     xmembu(u32 address)  { return *xaddrbu(address); }
    static __forceinline s16 &    xmemh(int address)   { return *xaddrh(address); }
    static __forceinline u16 &    xmemhu(u32 address)  { return *xaddrhu(address); }
    static __forceinline u32 &    xmemw(u32 address)   { return *xaddrw(address); }
    static __forceinline f32 &    xmemf(u32 address)   { return *xaddrf(address); }

    static __forceinline vmem_u & vmem()              { return mem< vmem_u >(0); }
	static __forceinline sram_u & sram()              { return mem< sram_u >(SRAM_START); }
	static __forceinline vram_u & vram()              { return mem< vram_u >(VRAM_START); }
    static __forceinline mram_u & mram()              { return mem< mram_u >(MRAM_START); }

	template< typename T >
	struct Ptr
	{
		u32 m_address;

        const T * operator -> () const                      { return addr< T >(m_address); }
		T * operator -> ()                                  { return addr< T >(m_address); }

        operator T * () const                               { return addr< T >(m_address); }
		operator T * ()                                     { return addr< T >(m_address); }

		bool IsInside()                                     { u32 delta = (u32)(addr< T >(m_address) - addr< T >(VMEM_START)); return delta < VMEM_SIZE; }

		Ptr()                                               {}
		explicit Ptr(int address) : m_address(address)      {}
		Ptr(Ptr< T > const &ptr) : m_address(ptr.m_address) {}
	};

    static __forceinline bool IsReserved()                  { return Memory::pointer != 0; }


    void *                    Reserve();
	void                      Release();

	bool                      Initialize();
	void                      Terminate();
	void                      Reset();

    void                      SetDisplayFrameBuffer(u32  start, u32  end);
    void                      ClearDisplayFrameBuffer();
    void                      GetDisplayFrameBuffer(u32 &start, u32 &end);
    bool                      IsExceptionInDisplayFrameBuffer(u32 address);
    bool                      IsDisplayFrameBufferDirty(bool reset = true);

    bool                      IsAddressValid(u32 address);

    void                      EnableExceptions(bool enable);
    
    void                      GuardPages(u32 start, u32 end);
    void                      WatchDirtyPages(u32 start, u32 end, bool enabled = true);
}
#endif /* EMULATOR_MEMORY_H_ */
