/* BCR */
u32 pc, npc;

__forceinline void reset_bcr()
{
	pc = 0x00010000;
	npc = 0x00010004;
}

