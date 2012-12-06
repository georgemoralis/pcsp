namespace prx_decrypter
{
	int DecryptPRX1(const u8* pbIn, u8* pbOut, int cbTotal, u32 tag);
	int DecryptPRX2(const u8 *inbuf, u8 *outbuf, u32 size, u32 tag);
};