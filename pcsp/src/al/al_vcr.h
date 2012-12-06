/*
#if defined(_M_IX86) || defined(__i386__)

__m128 pfxs_cst; // negative : swizzling, positive or zero : constant insertion
__m128 pfxs_abs; // no : 0x00000000, yes : 0x7FFFFFFF 
__m128 pfxs_neg; // no : 0x00000000, yes : 0x80000000

__m128 pfxt_cst; // negative : swizzling, positive or zero : constant insertion
__m128 pfxt_abs; // no : 0x00000000, yes : 0x7FFFFFFF
__m128 pfxt_neg; // no : 0x00000000, yes : 0x80000000

__m128 pfxd_min; // no : FLT_MIN, yes : -1.0f or 0.0f
__m128 pfxd_max; // no : FLT_MAX, yes : 1.0f
__m128 pfxd_msk; // 0x00000000 or 0xFFFFFFFF

#endif

u32 vcr[16];

*/

struct Random
{
    int seed;

    static const long long multiplier = 0x5DEECE66DLL;
	static const long long addend = 0xBL;
    static const long long mask = 0xFFFFFFFFFFFFFFFFLL; //(1L << 32) - 1;

protected:
	int Next (int bits)
	{
		seed = (seed * multiplier + addend) & mask;
		return (int)(seed >> (32 - bits));
	}

public:
	Random() 
	{
		Random(0x3f800001);
	}

	Random(int seed)
	{
		SetSeed(seed);
	}

	void SetSeed(int seed)
	{
        this->seed = seed & mask;
	}

	int GetSeed()
	{
		return (int)seed;
	}

	int NextInt()
	{
		return Next(32);
	}

	int NextInt(int n)
	{
		if (n <= 0)
		{
			//throw new IllegalArgumentException("n must be positive");
			return 0;			
		}

		if ((n & -n) == n)  // i.e., n is a power of 2
			return (int)((n * (long)Next(31)) >> 31);

		int bits, val;
		do
		{
			bits = Next(31);
			val = bits % n;
		} while (bits - val + (n-1) < 0);
		return val;
	}

	float NextFloat()
	{
		return Next(24) / ((float)(1 << 24));
	}
};

struct PfxSrc 
{
	int		swz[4];
	bool	abs[4];
	bool	cst[4];
	bool	neg[4];
	bool	enabled;

	PfxSrc()
	{
		enabled = false;
	}

	PfxSrc (const PfxSrc& right)
	{
		Copy(right);
	}

	void Reset()
	{
		memset (swz, 0, sizeof(swz));
		memset (abs, 0, sizeof(abs));
		memset (cst, 0, sizeof(cst));
		memset (neg, 0, sizeof(neg));

		enabled = false;
	}

	void Copy(const PfxSrc& right)
	{
		memcpy (swz, right.swz, sizeof(swz));
		memcpy (abs, right.abs, sizeof(abs));
		memcpy (cst, right.cst, sizeof(cst));
		memcpy (neg, right.neg, sizeof(neg));

		enabled = right.enabled;
	}
};

struct PfxDst
{
	int sat[4];
	bool msk[4];
	bool enabled;

	PfxDst()
	{
		enabled = false;
	}

	PfxDst(const PfxDst& right)
	{
		Copy(right);
	}

	void Reset()
	{
        ::memset(sat, 0, sizeof(sat));
        ::memset(msk, 0, sizeof(msk));
		enabled = false;
	}

	void Copy(PfxDst const &right)
	{
        ::memcpy(sat, right.sat, sizeof(sat));
        ::memcpy(msk, right.msk, sizeof(msk));

		enabled = right.enabled;
	}
};

struct Vcr
{
	PfxSrc pfxs;
	PfxSrc pfxt;

	PfxDst pfxd;
	bool cc[6];

	Vcr()
	{
	}

	Vcr(const Vcr& right)
	{
		Copy (right);
	}

	void Reset()
	{
		pfxs.Reset();
		pfxt.Reset();
		pfxd.Reset();
        ::memset(cc, 0, sizeof(cc));
	}

	void Copy(Vcr const &right)
	{
		pfxs.Copy(right.pfxs);
		pfxt.Copy(right.pfxt);
		pfxd.Copy(right.pfxd);
        ::memcpy(cc, right.cc, sizeof(cc));
	}
};

Random	rnd;
Vcr		vcr;

__forceinline void reset_vcr()
{
    vcr.Reset();
    rnd.SetSeed(0x3f800001);
}	

