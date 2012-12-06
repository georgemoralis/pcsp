/* GPR */
u32 gpr[32];

__forceinline void reset_gpr()
{
	::memset(gpr, 0, sizeof(gpr));	
}

