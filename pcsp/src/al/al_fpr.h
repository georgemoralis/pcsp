/* FPR */
f32 fpr[32];

__forceinline void reset_fpr()
{
	::memset(fpr, 0, sizeof(fpr));
}
