#ifndef VFPU_H_
#define VFPU_H_

#include <math.h>
//#if defined(_M_IX86) || defined(__i386__)
//		#include "al_vpu_sse.h"
//#elif defined(__GNUC__)
//#if 0

// this source is a temporary C++ port of Java version in JPCSP
// an optimal one will be rewritten using SSE

#ifndef _WIN32
#define _scalb ldexp
#define _isnan isnan
#define _finite finite
#endif

    float	v1[4], v2[4], v3[4];

    __forceinline float intBitsToFloat(int i)
    {
        return *((float*)(&i));
    }

    __forceinline int floatToRawIntBits(float i)
    {
        return *((int*)(&i));
    }

    __forceinline int branchTarget(int npc, int simm16)
    {
        return npc + (simm16 << 2);
    }

    __forceinline float signum(float i) //TODO it probably can be done better
    {
		int x = floatToRawIntBits(i);
        int s = ((x >> 16) & 0x00008000); // sign
		float signf = (s == 1) ? -1.0f : 1.0f;
		if(i == -0.0f || i == 0.0f)
			return 0.0*signf;
        int &v = *((int *)&i);
        return ((v & 0x80000000) ? -1.0f : 1.0f);
    }
	__forceinline bool isNaN( float value ) 
	{ 
		return ((*(UINT*)&value) & 0x7fffffff) > 0x7f800000; 
	}

// VFPU stuff
    __forceinline float transformVr(int swz, bool abs, bool cst, bool neg, float* x)
    {
        float value = 0.0f;
        if (cst)
        {
            switch (swz)
            {
            case 0:
                value = abs ? 3.0f : 0.0f;
                break;
            case 1:
                value = abs ? (1.0f / 3.0f) : 1.0f;
                break;
            case 2:
                value = abs ? (1.0f / 4.0f) : 2.0f;
                break;
            case 3:
                value = abs ? (1.0f / 6.0f) : 0.5f;
                break;
            }
        }
        else
        {
            value = x[swz];
        }

        if (abs)
        {
            value = fabsf(value);
        }

        return neg ? (0.0f - value) : value;
    }

    __forceinline float applyPrefixVs(int i, float* x)
    {
        return transformVr(vcr.pfxs.swz[i], vcr.pfxs.abs[i], vcr.pfxs.cst[i], vcr.pfxs.neg[i], x);
    }

    __forceinline float applyPrefixVt(int i, float* x)
    {
        return transformVr(vcr.pfxt.swz[i], vcr.pfxt.abs[i], vcr.pfxt.cst[i], vcr.pfxt.neg[i], x);
    }

    __forceinline float applyPrefixVd(int i, float value)
    {
        switch (vcr.pfxd.sat[i])
        {
        case 1:
            return max(0.0f, min(1.0f, value));
        case 3:
            return max(-1.0f, min(1.0f, value));
        }

        return value;
    }

    template< int vsize > __forceinline void loadVs(int vs)
    {
        int m, s, i;

        m = (vs >> 2) & 7;
        i = (vs >> 0) & 3;

        switch (vsize)
        {
        case 1:
            {
                s = (vs >> 5) & 3;
                v1[0] = vpr[m][i][s];

                if (vcr.pfxs.enabled)
                {
                    v1[0] = applyPrefixVs(0, v1);
                    vcr.pfxs.enabled = false;
                }
                break;
            }

        case 2:
            {
                s = (vs & 64) >> 5;
                if ((vs & 32) != 0)
                {
                    v1[0] = vpr[m][s + 0][i];
                    v1[1] = vpr[m][s + 1][i];
                }
                else
                {
                    v1[0] = vpr[m][i][s + 0];
                    v1[1] = vpr[m][i][s + 1];
                }

                if (vcr.pfxs.enabled)
                {
                    v3[0] = applyPrefixVs(0, v1);
                    v3[1] = applyPrefixVs(1, v1);
                    v1[0] = v3[0];
                    v1[1] = v3[1];
                    vcr.pfxs.enabled = false;
                }
                break;
            }

        case 3:
            {
                s = (vs & 64) >> 6;
                if ((vs & 32) != 0)
                {
                    v1[0] = vpr[m][s + 0][i];
                    v1[1] = vpr[m][s + 1][i];
                    v1[2] = vpr[m][s + 2][i];
                }
                else
                {
                    v1[0] = vpr[m][i][s + 0];
                    v1[1] = vpr[m][i][s + 1];
                    v1[2] = vpr[m][i][s + 2];
                }

                if (vcr.pfxs.enabled)
                {
                    v3[0] = applyPrefixVs(0, v1);
                    v3[1] = applyPrefixVs(1, v1);
                    v3[2] = applyPrefixVs(2, v1);
                    v1[0] = v3[0];
                    v1[1] = v3[1];
                    v1[2] = v3[2];
                    vcr.pfxs.enabled = false;
                }
                break;
            }

        case 4:
            {
                if ((vs & 32) != 0)
                {
                    v1[0] = vpr[m][0][i];
                    v1[1] = vpr[m][1][i];
                    v1[2] = vpr[m][2][i];
                    v1[3] = vpr[m][3][i];
                }
                else
                {
                    v1[0] = vpr[m][i][0];
                    v1[1] = vpr[m][i][1];
                    v1[2] = vpr[m][i][2];
                    v1[3] = vpr[m][i][3];
                }

                if (vcr.pfxs.enabled)
                {
                    v3[0] = applyPrefixVs(0, v1);
                    v3[1] = applyPrefixVs(1, v1);
                    v3[2] = applyPrefixVs(2, v1);
                    v3[3] = applyPrefixVs(3, v1);
                    v1[0] = v3[0];
                    v1[1] = v3[1];
                    v1[2] = v3[2];
                    v1[3] = v3[3];
                    vcr.pfxs.enabled = false;
                }
                break;
            }
        }
    }

    template< int vsize > __forceinline void loadVt(int vt)
    {
        int m, s, i;

        m = (vt >> 2) & 7;
        i = (vt >> 0) & 3;

        switch (vsize)
        {
        case 1:
            s = (vt >> 5) & 3;
            v2[0] = vpr[m][i][s];

            if (vcr.pfxt.enabled)
            {
                v2[0] = applyPrefixVt(0, v2);
                vcr.pfxt.enabled = false;
            }
            return;

        case 2:
            s = (vt & 64) >> 5;
            if ((vt & 32) != 0)
            {
                v2[0] = vpr[m][s + 0][i];
                v2[1] = vpr[m][s + 1][i];
            }
            else
            {
                v2[0] = vpr[m][i][s + 0];
                v2[1] = vpr[m][i][s + 1];
            }

            if (vcr.pfxt.enabled)
            {
                v3[0] = applyPrefixVt(0, v2);
                v3[1] = applyPrefixVt(1, v2);
                v2[0] = v3[0];
                v2[1] = v3[1];
                vcr.pfxt.enabled = false;
            }
            return;

        case 3:
            s = (vt & 64) >> 6;
            if ((vt & 32) != 0)
            {
                v2[0] = vpr[m][s + 0][i];
                v2[1] = vpr[m][s + 1][i];
                v2[2] = vpr[m][s + 2][i];
            }
            else
            {
                v2[0] = vpr[m][i][s + 0];
                v2[1] = vpr[m][i][s + 1];
                v2[2] = vpr[m][i][s + 2];
            }

            if (vcr.pfxt.enabled)
            {
                v3[0] = applyPrefixVt(0, v2);
                v3[1] = applyPrefixVt(1, v2);
                v3[2] = applyPrefixVt(2, v2);
                v2[0] = v3[0];
                v2[1] = v3[1];
                v2[2] = v3[2];
                vcr.pfxt.enabled = false;
            }
            return;

        case 4:
            if ((vt & 32) != 0)
            {
                v2[0] = vpr[m][0][i];
                v2[1] = vpr[m][1][i];
                v2[2] = vpr[m][2][i];
                v2[3] = vpr[m][3][i];
            }
            else
            {
                v2[0] = vpr[m][i][0];
                v2[1] = vpr[m][i][1];
                v2[2] = vpr[m][i][2];
                v2[3] = vpr[m][i][3];
            }

            if (vcr.pfxt.enabled)
            {
                v3[0] = applyPrefixVt(0, v2);
                v3[1] = applyPrefixVt(1, v2);
                v3[2] = applyPrefixVt(2, v2);
                v3[3] = applyPrefixVt(3, v2);
                v2[0] = v3[0];
                v2[1] = v3[1];
                v2[2] = v3[2];
                v2[3] = v3[3];
                vcr.pfxt.enabled = false;
            }
            break;
        }
    }

    template< int vsize > __forceinline void loadVd(int vd)
    {
        int m, s, i;

        m = (vd >> 2) & 7;
        i = (vd >> 0) & 3;

        switch (vsize)
        {
        case 1:
            s = (vd >> 5) & 3;
            v3[0] = vpr[m][i][s];
            return;

        case 2:
            s = (vd & 64) >> 5;
            if ((vd & 32) != 0)
            {
                v3[0] = vpr[m][s + 0][i];
                v3[1] = vpr[m][s + 1][i];
            }
            else
            {
                v3[0] = vpr[m][i][s + 0];
                v3[1] = vpr[m][i][s + 1];
            }
            return;

        case 3:
            s = (vd & 64) >> 6;
            if ((vd & 32) != 0)
            {
                v3[0] = vpr[m][s + 0][i];
                v3[1] = vpr[m][s + 1][i];
                v3[2] = vpr[m][s + 2][i];
            }
            else
            {
                v3[0] = vpr[m][i][s + 0];
                v3[1] = vpr[m][i][s + 1];
                v3[2] = vpr[m][i][s + 2];
            }
            return;

        case 4:
            if ((vd & 32) != 0)
            {
                v3[0] = vpr[m][0][i];
                v3[1] = vpr[m][1][i];
                v3[2] = vpr[m][2][i];
                v3[3] = vpr[m][3][i];
            }
            else
            {
                v3[0] = vpr[m][i][0];
                v3[1] = vpr[m][i][1];
                v3[2] = vpr[m][i][2];
                v3[3] = vpr[m][i][3];
            }
            break;
        }
    }

    template< int vsize > __forceinline void saveVd(int vd, float* vr)
    {
        int m, s, i;

        m = (vd >> 2) & 7;
        i = (vd >> 0) & 3;

        vcr.pfxs.enabled = false;

        switch (vsize)
        {
        case 1:
            s = (vd >> 5) & 3;
            if (vcr.pfxd.enabled)
            {
                if (!vcr.pfxd.msk[0])
                {
                    vpr[m][i][s] = applyPrefixVd(0, vr[0]);
                }
                vcr.pfxd.enabled = false;
            }
            else
            {
                vpr[m][i][s] = vr[0];
            }
            break;

        case 2:
            s = (vd & 64) >> 5;
            if (vcr.pfxd.enabled)
            {
                if ((vd & 32) != 0)
                {
                    for (int j = 0; j < 2; ++j)
                    {
                        if (!vcr.pfxd.msk[j])
                        {
                            vpr[m][s + j][i] = applyPrefixVd(j, vr[j]);
                        }
                    }
                }
                else
                {
                    for (int j = 0; j < 2; ++j)
                    {
                        if (!vcr.pfxd.msk[j])
                        {
                            vpr[m][i][s + j] = applyPrefixVd(j, vr[j]);
                        }
                    }
                }
                vcr.pfxd.enabled = false;
            }
            else
            {
                if ((vd & 32) != 0)
                {
                    for (int j = 0; j < 2; ++j)
                    {
                        vpr[m][s + j][i] = vr[j];
                    }
                }
                else 
                {
                    for (int j = 0; j < 2; ++j)
                    {
                        vpr[m][i][s + j] = vr[j];
                    }
                }
            }
            break;

        case 3:
            s = (vd & 64) >> 6;
            if (vcr.pfxd.enabled)
            {
                if ((vd & 32) != 0)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        if (!vcr.pfxd.msk[j])
                        {
                            vpr[m][s + j][i] = applyPrefixVd(j, vr[j]);
                        }
                    }
                }
                else
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        if (!vcr.pfxd.msk[j])
                        {
                            vpr[m][i][s + j] = applyPrefixVd(j, vr[j]);
                        }
                    }
                }
                vcr.pfxd.enabled = false;
            }
            else
            {
                if ((vd & 32) != 0)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        vpr[m][s + j][i] = vr[j];
                    }
                }
                else
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        vpr[m][i][s + j] = vr[j];
                    }
                }
            }
            break;

        case 4:
            if (vcr.pfxd.enabled)
            {
                if ((vd & 32) != 0)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        if (!vcr.pfxd.msk[j])
                        {
                            vpr[m][j][i] = applyPrefixVd(j, vr[j]);
                        }
                    }
                }
                else
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        if (!vcr.pfxd.msk[j])
                        {
                            vpr[m][i][j] = applyPrefixVd(j, vr[j]);
                        }
                    }
                }
                vcr.pfxd.enabled = false;
            }
            else
            {
                if ((vd & 32) != 0)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        vpr[m][j][i] = vr[j];
                    }
                }
                else
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        vpr[m][i][j] = vr[j];
                    }
                }
            }
            break;

        default:
            break;
        }
    }

    __forceinline float halffloatToFloat(int imm16)
    {   
        int s = (imm16 >> 15) & 0x00000001; // sign
        int e = (imm16 >> 10) & 0x0000001f; // exponent
        int f = (imm16 >>  0) & 0x000003ff; // fraction

        // need to handle 0x7C00 INF and 0xFC00 -INF?
        if (e == 0)
        {
            // need to handle +-0 case f==0 or f=0x8000?
            if (f == 0)
            {
                // Plus or minus zero
                return intBitsToFloat(s << 31);                
            }
            else
            {
                // Denormalized number -- renormalize it
                while ((f & 0x00000400) == 0)
                {
                    f <<= 1;
                    e -=  1;
                }
                e += 1;
                f &= ~0x00000400;
            }
        }
        else if (e == 31)
        {
            if (f == 0)
            {
                // Inf
                return intBitsToFloat((s << 31) | 0x7f800000);
            }
            else
            {
                // NaN
                return intBitsToFloat((s << 31) | 0x7f800000 | (f << 13));
            }
        }

        e = e + (127 - 15);
        f = f << 13;

        return intBitsToFloat((s << 31) | (e << 23) | f);
    }

    __forceinline int floatToHalffloat(float v)
    {
        int i = floatToRawIntBits(v);
        int s = ((i >> 16) & 0x00008000);              // sign
        int e = ((i >> 23) & 0x000000ff) - (127 - 15); // exponent
        int f = ((i >>  0) & 0x007fffff);              // fraction

        // need to handle NaNs and Inf?
        if (e <= 0)
        {
            if (e < -10)
            {
                if (s != 0)
                {
                    // handle -0.0
                    return 0x8000;
                }
                return 0;
            }
            f = (f | 0x00800000) >> (1 - e);
            return s | (f >> 13);
        }
        else if (e == 0xff - (127 - 15))
        {
            if (f == 0)
            {
                // Inf
                return s | 0x7c00;
            }
            // NAN
            f >>= 13;
            return s | 0x7c00 | f | ((f == 0) ? 1 : 0);
        }
        if (e > 30)
        {
            // Overflow
            return s | 0x7c00;
        }
        return s | (e << 10) | (f >> 13);
    }

    // group VFPU0
    // VFPU0:VADD
    template< int vsize > void doVADD(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v1[i] += v2[i];
        }

        saveVd<vsize>(vd, v1);
    }

    // VFPU0:VSUB
    template< int vsize > void doVSUB(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v1[i] -= v2[i];
        }

        saveVd<vsize>(vd, v1);
    }

    // VFPU0:VSBN
    template< int vsize > void doVSBN(int vd, int vs, int vt)
    {
        if (vsize != 1)
        {
            doUNK("Only supported VSBN.S");
        }

        loadVs<1>(vs);
        loadVt<1>(vt);

        v1[0] = _scalb(v1[0], floatToRawIntBits(v2[0]));

        saveVd<1>(vd, v1);
    }

    // VFPU0:VDIV
    template< int vsize > void doVDIV(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v1[i] /= v2[i];
        }

        saveVd<vsize>(vd, v1);
    }

    // group VFPU1
    // VFPU1:VMUL
    template< int vsize > void doVMUL(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v1[i] *= v2[i];
        }

        saveVd<vsize>(vd, v1);
    }

    // VFPU1:VDOT
    template< int vsize > void doVDOT(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        float dot = v1[0] * v2[0];

        for (int i = 1; i < vsize; ++i)
        {
            dot += v1[i] * v2[i];
        }

        v3[0] = dot;

        saveVd<1>(vd, v3);
    }

    // VFPU1:VSCL
    template< int vsize > void doVSCL(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<1>(vt);

        float scale = v2[0];

        for (int i = 0; i < vsize; ++i)
        {
            v1[i] *= scale;
        }

        saveVd<vsize>(vd, v1);
    }

    // VFPU1:VHDP
    template< int vsize > void doVHDP(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        float hdp = v1[0] * v2[0];

        int i;

        for (i = 1; i < vsize - 1; ++i)
        {
            hdp += v1[i] * v2[i];
        }

        v2[0] = hdp + v2[i];

        saveVd<1>(vd, v2);
    }

    // VFPU1:VCRS
    template< int vsize > void doVCRS(int vd, int vs, int vt)
    {
        loadVs<3>(vs);
        loadVt<3>(vt);

        v3[0] = v1[1] * v2[2];
        v3[1] = v1[2] * v2[0];
        v3[2] = v1[0] * v2[1];

        saveVd<3>(vd, v3);
    }

    // VFPU1:VDET
    template< int vsize > void doVDET(int vd, int vs, int vt)
    {
        loadVs<2>(vs);
        loadVt<2>(vt);

        v1[0] = v1[0] * v2[1] - v1[1] * v2[0];

        saveVd<1>(vd, v1);
    }

    // VFPU2

    // VFPU2:MFV
    void doMFV(int rt, int imm7)
    {
        int r = (imm7 >> 5) & 3;
        int m = (imm7 >> 2) & 7;
        int c = (imm7 >> 0) & 3;

        gpr[rt] = floatToRawIntBits(vpr[m][c][r]);
    }
    // VFPU2:MFVC
    void doMFVC(int rt, int imm7)
    {
        if (rt != 0)
        {
            int value = 0;
            switch (imm7)
            {
            case 0: /* 128 */
                value |= vcr.pfxs.swz[0] << 0;
                value |= vcr.pfxs.swz[1] << 2;
                value |= vcr.pfxs.swz[2] << 4;
                value |= vcr.pfxs.swz[3] << 6;
                if (vcr.pfxs.abs[0]) value |=  1 <<  8;
                if (vcr.pfxs.abs[1]) value |=  1 <<  9;
                if (vcr.pfxs.abs[2]) value |=  1 << 10;
                if (vcr.pfxs.abs[3]) value |=  1 << 11;
                if (vcr.pfxs.cst[0]) value |=  1 << 12;
                if (vcr.pfxs.cst[1]) value |=  1 << 13;
                if (vcr.pfxs.cst[2]) value |=  1 << 14;
                if (vcr.pfxs.cst[3]) value |=  1 << 15;
                if (vcr.pfxs.neg[0]) value |=  1 << 16;
                if (vcr.pfxs.neg[1]) value |=  1 << 17;
                if (vcr.pfxs.neg[2]) value |=  1 << 18;
                if (vcr.pfxs.neg[3]) value |=  1 << 19;
                gpr[rt] = value;
                break;
            case 1: /* 129 */
                value |= vcr.pfxt.swz[0] << 0;
                value |= vcr.pfxt.swz[1] << 2;
                value |= vcr.pfxt.swz[2] << 4;
                value |= vcr.pfxt.swz[3] << 6;
                if (vcr.pfxt.abs[0]) value |=  1 <<  8;
                if (vcr.pfxt.abs[1]) value |=  1 <<  9;
                if (vcr.pfxt.abs[2]) value |=  1 << 10;
                if (vcr.pfxt.abs[3]) value |=  1 << 11;
                if (vcr.pfxt.cst[0]) value |=  1 << 12;
                if (vcr.pfxt.cst[1]) value |=  1 << 13;
                if (vcr.pfxt.cst[2]) value |=  1 << 14;
                if (vcr.pfxt.cst[3]) value |=  1 << 15;
                if (vcr.pfxt.neg[0]) value |=  1 << 16;
                if (vcr.pfxt.neg[1]) value |=  1 << 17;
                if (vcr.pfxt.neg[2]) value |=  1 << 18;
                if (vcr.pfxt.neg[3]) value |=  1 << 19;
                gpr[rt] = value;
                break;
            case 2: /* 130 */
                value |= vcr.pfxd.sat[0] << 0;
                value |= vcr.pfxd.sat[1] << 2;
                value |= vcr.pfxd.sat[2] << 4;
                value |= vcr.pfxd.sat[3] << 6;
                if (vcr.pfxd.msk[0]) value |=  1 <<  8;
                if (vcr.pfxd.msk[1]) value |=  1 <<  9;
                if (vcr.pfxd.msk[2]) value |=  1 << 10;
                if (vcr.pfxd.msk[3]) value |=  1 << 11;
                gpr[rt] = value;
                break;
            case 3: /* 131 */
                for (int i = 6 - 1; i >= 0; i--) {
                    value <<= 1;
                    if (vcr.cc[i]) {
                        value |= 1;
                    }
                }
                gpr[rt] = value;
                break;
            case 8: /* 136 - RCX0 */
                gpr[rt] = rnd.GetSeed();
                break;
            case 9:  /* 137 - RCX1 */
            case 10: /* 138 - RCX2 */
            case 11: /* 139 - RCX3 */
            case 12: /* 140 - RCX4 */
            case 13: /* 141 - RCX5 */
            case 14: /* 142 - RCX6 */
            case 15: /* 143 - RCX7 */
                // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
                gpr[rt] = 0x3f800000;
                break;
            default:
                break;
            }
        }
    }
    // VFPU2:MTV
    void doMTV(int rt, int imm7)
    {
        int r = (imm7 >> 5) & 3;
        int m = (imm7 >> 2) & 7;
        int c = (imm7 >> 0) & 3;

        vpr[m][c][r] = intBitsToFloat(gpr[rt]);
    }

    // VFPU2:MTVC
    void doMTVC(int rt, int imm7)
    {
        int value = gpr[rt]; 

        switch (imm7)
        {
        case 0: /* 128 */
            vcr.pfxs.swz[0] = ((value >> 0 ) & 3);
            vcr.pfxs.swz[1] = ((value >> 2 ) & 3);
            vcr.pfxs.swz[2] = ((value >> 4 ) & 3);
            vcr.pfxs.swz[3] = ((value >> 6 ) & 3);
            vcr.pfxs.abs[0] = ((value >> 8 ) & 1) == 1;
            vcr.pfxs.abs[1] = ((value >> 9 ) & 1) == 1;
            vcr.pfxs.abs[2] = ((value >> 10) & 1) == 1;
            vcr.pfxs.abs[3] = ((value >> 11) & 1) == 1;
            vcr.pfxs.cst[0] = ((value >> 12) & 1) == 1;
            vcr.pfxs.cst[1] = ((value >> 13) & 1) == 1;
            vcr.pfxs.cst[2] = ((value >> 14) & 1) == 1;
            vcr.pfxs.cst[3] = ((value >> 15) & 1) == 1;
            vcr.pfxs.neg[0] = ((value >> 16) & 1) == 1;
            vcr.pfxs.neg[1] = ((value >> 17) & 1) == 1;
            vcr.pfxs.neg[2] = ((value >> 18) & 1) == 1;
            vcr.pfxs.neg[3] = ((value >> 19) & 1) == 1;
            vcr.pfxs.enabled = true;
            break;               
        case 1: /* 129 */
            vcr.pfxt.swz[0] = ((value >> 0 ) & 3);
            vcr.pfxt.swz[1] = ((value >> 2 ) & 3);
            vcr.pfxt.swz[2] = ((value >> 4 ) & 3);
            vcr.pfxt.swz[3] = ((value >> 6 ) & 3);
            vcr.pfxt.abs[0] = ((value >> 8 ) & 1) == 1;
            vcr.pfxt.abs[1] = ((value >> 9 ) & 1) == 1;
            vcr.pfxt.abs[2] = ((value >> 10) & 1) == 1;
            vcr.pfxt.abs[3] = ((value >> 11) & 1) == 1;
            vcr.pfxt.cst[0] = ((value >> 12) & 1) == 1;
            vcr.pfxt.cst[1] = ((value >> 13) & 1) == 1;
            vcr.pfxt.cst[2] = ((value >> 14) & 1) == 1;
            vcr.pfxt.cst[3] = ((value >> 15) & 1) == 1;
            vcr.pfxt.neg[0] = ((value >> 16) & 1) == 1;
            vcr.pfxt.neg[1] = ((value >> 17) & 1) == 1;
            vcr.pfxt.neg[2] = ((value >> 18) & 1) == 1;
            vcr.pfxt.neg[3] = ((value >> 19) & 1) == 1;
            vcr.pfxt.enabled = true;
            break;
        case 2: /* 130 */
            vcr.pfxd.sat[0] = ((value >> 0 ) & 3);
            vcr.pfxd.sat[1] = ((value >> 2 ) & 3);
            vcr.pfxd.sat[2] = ((value >> 4 ) & 3);
            vcr.pfxd.sat[3] = ((value >> 6 ) & 3);
            vcr.pfxd.msk[0] = ((value >> 8 ) & 1) == 1;
            vcr.pfxd.msk[1] = ((value >> 9 ) & 1) == 1;
            vcr.pfxd.msk[2] = ((value >> 10) & 1) == 1;
            vcr.pfxd.msk[3] = ((value >> 11) & 1) == 1;
            vcr.pfxd.enabled = true;
            break;
        case 3: /* 131 */
            for (int i = 0; i < 6; i++) {
                vcr.cc[i] = (value & 1) != 0;
                value >>= 1;
            }
            break;
        case 8: /* 136 - RCX0 */
            rnd.SetSeed(value);
            break;
        case 9:  /* 137 - RCX1 */
        case 10: /* 138 - RCX2 */
        case 11: /* 139 - RCX3 */
        case 12: /* 140 - RCX4 */
        case 13: /* 141 - RCX5 */
        case 14: /* 142 - RCX6 */
        case 15: /* 143 - RCX7 */
            // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
            break;
        default:
            break;
        }
    }

    // VFPU2:BVF
    bool doBVF(int imm3, int simm16)
    {
        npc = (!vcr.cc[imm3]) ? branchTarget(pc, simm16) : (pc + 4);
        return true;
    }
    // VFPU2:BVT
    bool doBVT(int imm3, int simm16)
    {
        npc = (vcr.cc[imm3]) ? branchTarget(pc, simm16) : (pc + 4);
        return true;
    }
    // VFPU2:BVFL
    bool doBVFL(int imm3, int simm16)
    {
        if (!vcr.cc[imm3])
        {
            npc = branchTarget(pc, simm16);
            return true;
        }
        else
        {
            pc = pc + 4;
        }
        return false;
    }
    // VFPU2:BVTL
    bool doBVTL(int imm3, int simm16)
    {
        if (vcr.cc[imm3])
        {
            npc = branchTarget(pc, simm16);
            return true;
        }
        else
        {
            pc = pc + 4;
        }
        return false;
    }
    // group VFPU3
	

    // VFPU3:VCMP
    template< int vsize > void doVCMP(int vs, int vt, int cond)
    {
        bool cc_or = false;
        bool cc_and = true;

        if ((cond & 8) == 0)
        {
            bool not_ = ((cond & 4) == 4);

            bool cc = false;

            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                switch (cond & 3)
                {
                case 0:
                    cc = not_;
                    break;

                case 1:
                    cc = not_ ? (v1[i] != v2[i]) : (v1[i] == v2[i]);
                    break;

                case 2:
					if (isNaN(v1[i]) || isNaN(v2[i])) {
						cc = false;
					}else{
						cc = not_ ? (v1[i] >= v2[i]) : (v1[i] < v2[i]);
					}
                    break;

                case 3:
					if (isNaN(v1[i]) || isNaN(v2[i])) {
						cc=false;
					}else{
						cc = not_ ? (v1[i] > v2[i]) : (v1[i] <= v2[i]);
					}
                    break;

                }


                vcr.cc[i] = cc;
                cc_or = cc_or || cc;
                cc_and = cc_and && cc;
            }

        }
        else
        {
            loadVs<vsize>(vs);

			bool not_ = ((cond & 4) == 4);
			bool cc = false;

            for (int i = 0; i < vsize; ++i)
            {
				switch (cond & 3)
                {
                case 0:
                    cc = (abs(v1[i]) == 0.0f);
                    break;

                case 1:
                    cc = isNaN(v1[i]);
                    break;

                case 2:
					cc = !_finite(v1[i]);
                    break;

                case 3:
					cc = isNaN(abs(v1[i])) || !_finite(v1[i]);
                    break;

                }
				if(not_)
				{
					cc= !cc;
				}
                vcr.cc[i] = cc;
                cc_or = cc_or || cc;
                cc_and = cc_and && cc;
            }

        }
        vcr.cc[4] = cc_or;
        vcr.cc[5] = cc_and;
    }

    // VFPU3:VMIN
    template< int vsize > void doVMIN(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = min(v1[i], v2[i]);
        }

        saveVd<vsize>(vd, v3);
    }

    // VFPU3:VMAX
    template< int vsize > void doVMAX(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = max(v1[i], v2[i]);
        }

        saveVd<vsize>(vd, v3);
    }

    // VFPU3:VSCMP
    template< int vsize > void doVSCMP(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = signum(v1[i] - v2[i]);
        }

        saveVd<vsize>(vd, v3);
    }

    // VFPU3:VSGE
    template< int vsize > void doVSGE(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = (v1[i] >= v2[i]) ? 1.0f : 0.0f;
        }

        saveVd<vsize>(vd, v3);
    }

    // VFPU3:VSLT
    template< int vsize > void doVSLT(int vd, int vs, int vt)
    {
        loadVs<vsize>(vs);
        loadVt<vsize>(vt);

        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = (v1[i] < v2[i]) ? 1.0f : 0.0f;
        }

        saveVd<vsize>(vd, v3);
    }

    // group VFPU4
    // VFPU4:VMOV
    template< int vsize > void doVMOV(int vd, int vs)
    {
        loadVs<vsize>(vs);
        saveVd<vsize>(vd, v1);
    }

    // VFPU4:VABS
    template< int vsize > void doVABS(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = fabsf(v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VNEG
    template< int vsize > void doVNEG(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 0.0f - v1[i];
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VIDT
    template< int vsize > void doVIDT(int vd)
    {
        int id = vd & 3;
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = (id == i) ? 1.0f : 0.0f;
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VSAT0
    template< int vsize > void doVSAT0(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
			if(isNaN(v1[i]))
			{
				v3[i] = v1[i];
			}
			else
			{
              v3[i] = min(max(0.0f, v1[i]), 1.0f);
			}
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VSAT1
    template< int vsize > void doVSAT1(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
			if(isNaN(v1[i]))
			{
				v3[i] = v1[i];
			}
			else
			{
                v3[i] = min(max(-1.0f, v1[i]), 1.0f);
			}
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VZERO
    template< int vsize > void doVZERO(int vd)
    {
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 0.0f;
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VONE
    template< int vsize > void doVONE(int vd)
    {
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 1.0f;
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VRCP
    template< int vsize > void doVRCP(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 1.0f / v1[i];
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VRSQ
    template< int vsize > void doVRSQ(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 1.f / sqrtf(v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VSIN
    template< int vsize > void doVSIN(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = sinf(0.5 * (float)M_PI * v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VCOS
    template< int vsize > void doVCOS(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = cosf(0.5f * (float)M_PI * v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VEXP2
    template< int vsize > void doVEXP2(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = powf(2.f, v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VLOG2
    template< int vsize > void doVLOG2(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = logf(v1[i]) / logf(2.0);
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VSQRT
    template< int vsize > void doVSQRT(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = sqrtf(v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VASIN
    template< int vsize > void doVASIN(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = asinf(v1[i]) * 2.f / (float)M_PI;
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VNRCP
    template< int vsize > void doVNRCP(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 0.0f - (1.0f / v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VNSIN
    template< int vsize > void doVNSIN(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 0.0f - sinf(0.5f * (float)M_PI * v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VREXP2
    template< int vsize > void doVREXP2(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 1.f / powf(2.f, v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VRNDS
    template< int vsize > void doVRNDS(int vs)
    {
        // temporary solution
        if (vsize != 1)
        {
            doUNK("Only supported VRNDS.S");
            return;
        }

        loadVs<1>(vs);
        rnd.SetSeed(floatToRawIntBits(v1[0]));
    }
    // VFPU4:VRNDI
    template< int vsize > void doVRNDI(int vd)
    {
        // temporary solution
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = intBitsToFloat(rnd.NextInt());
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VRNDF1
    template< int vsize > void doVRNDF1(int vd)
    {
        // temporary solution
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = 1.0f + rnd.NextFloat();
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VRNDF2
    template< int vsize > void doVRNDF2(int vd)
    {
        // temporary solution
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = (1.0f + rnd.NextFloat())*2.0f;
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VF2H
    template< int vsize > void doVF2H(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize/2; ++i)
        {
            v3[i] = (floatToHalffloat(v1[1+i*2])<<16)|
                (floatToHalffloat(v1[0+i*2])<< 0);
        }
        saveVd<vsize/2>(vd, v3);
    }
    // VFPU4:VH2F
    template< int vsize > void doVH2F(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            int imm32 = floatToRawIntBits(v1[i]);
            v3[0+2*i] = halffloatToFloat(imm32 & 65535);
            v3[1+2*i] = halffloatToFloat(imm32 >> 16);
        }
        saveVd<vsize*2>(vd, v3);
    }
    // VFPU4:VSBZ
    template< int vsize > void doVSBZ(int vd, int vs)
    {
        doUNK("Unimplemented VSBZ");
    }
    // VFPU4:VLGB
    template< int vsize > void doVLGB(int vd, int vs)
    {
        doUNK("Unimplemented VLGB");
    }
    // VFPU4:VUC2I
    template< int vsize > void doVUC2I(int vd, int vs)
    {
        loadVs<1>(vs);
        int n = floatToRawIntBits(v1[0]);
        // Performs pseudo-full-scale conversion
        v3[0] = intBitsToFloat((u32)(((n      ) & 0xFF) * 0x01010101) >> 1);
        v3[1] = intBitsToFloat((u32)(((n >>  8) & 0xFF) * 0x01010101) >> 1);
        v3[2] = intBitsToFloat((u32)(((n >> 16) & 0xFF) * 0x01010101) >> 1);
        v3[3] = intBitsToFloat((u32)(((n >> 24) & 0xFF) * 0x01010101) >> 1);
        saveVd<4>(vd, v3);
    }
    // VFPU4:VC2I
    template< int vsize > void doVC2I(int vd, int vs)
    {
        loadVs<1>(vs);
        int n = floatToRawIntBits(v1[0]);
        v3[0] = intBitsToFloat(((n      ) & 0xFF) << 24);
        v3[1] = intBitsToFloat(((n >>  8) & 0xFF) << 24);
        v3[2] = intBitsToFloat(((n >> 16) & 0xFF) << 24);
        v3[3] = intBitsToFloat(((n >> 24) & 0xFF) << 24);
        saveVd<4>(vd, v3);
    }
    // VFPU4:VUS2I
    template< int vsize > void doVUS2I(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            int imm32 = floatToRawIntBits(v1[i]);
            v3[0+2*i] = intBitsToFloat(((imm32       ) & 0xFFFF) << 15);
            v3[1+2*i] = intBitsToFloat(((imm32 >> 16) & 0xFFFF) << 15);
        }
        saveVd<vsize*2>(vd, v3);
    }
    // VFPU4:VS2I
    template< int vsize > void doVS2I(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            int imm32 = floatToRawIntBits(v1[i]);
            v3[0+2*i] = intBitsToFloat(((imm32       ) & 0xFFFF) << 16);
            v3[1+2*i] = intBitsToFloat(((imm32 >> 16) & 0xFFFF) << 16);
        }
        saveVd<vsize*2>(vd, v3);
    }

    // VFPU4:VI2UC
    template< int vsize > void doVI2UC(int vd, int vs)
    {
        loadVs<4>(vs);
        int x = floatToRawIntBits(v1[0]);
        int y = floatToRawIntBits(v1[1]);
        int z = floatToRawIntBits(v1[2]);
        int w = floatToRawIntBits(v1[3]);
        v3[0] = intBitsToFloat(
            ((x < 0) ? 0 : ((x >> 23) << 0 )) |
            ((y < 0) ? 0 : ((y >> 23) << 8 )) |
            ((z < 0) ? 0 : ((z >> 23) << 16)) |
            ((w < 0) ? 0 : ((w >> 23) << 24)));
        saveVd<1>(vd, v3);
    }

    // VFPU4:VI2C
    template< int vsize > void doVI2C(int vd, int vs)
    {
        loadVs<4>(vs);
        int x = floatToRawIntBits(v1[0]);
        int y = floatToRawIntBits(v1[1]);
        int z = floatToRawIntBits(v1[2]);
        int w = floatToRawIntBits(v1[3]);
        v3[0] = intBitsToFloat(
            (((u32)x >> 24) << 0 ) |
            (((u32)y >> 24) << 8 ) |
            (((u32)z >> 24) << 16) |
            (((u32)w >> 24) << 24));
        saveVd<1>(vd, v3);
    }
    // VFPU4:VI2US
    template< int vsize > void doVI2US(int vd, int vs)
    {
        loadVs<vsize>(vs);
        int x = floatToRawIntBits(v1[0]);
        int y = floatToRawIntBits(v1[1]);
        v3[0] = intBitsToFloat(
            ((x < 0) ? 0 : ((x >> 15) << 0 )) |
            ((y < 0) ? 0 : ((y >> 15) << 16)));
        if (vsize == 4)
        {
            int z = floatToRawIntBits(v1[2]);
            int w = floatToRawIntBits(v1[3]);

            v3[1] = intBitsToFloat(
                ((z < 0) ? 0 : ((z >> 15) << 0 )) |
                ((w < 0) ? 0 : ((w >> 15) << 16)));
            saveVd<2>(vd, v3);
        }
        else
        {
            saveVd<1>(vd, v3);
        }
    }
    // VFPU4:VI2S
    template< int vsize > void doVI2S(int vd, int vs)
    {
        loadVs<vsize>(vs);
        int x = floatToRawIntBits(v1[0]);
        int y = floatToRawIntBits(v1[1]);
        v3[0] = intBitsToFloat(
            ((x >> 16) << 0 ) |
            ((y >> 16) << 16));
        if (vsize == 4)
        {
            int z = floatToRawIntBits(v1[2]);
            int w = floatToRawIntBits(v1[3]);

            v3[1] = intBitsToFloat(
                ((z >> 16) << 0 ) |
                ((w >> 16) << 16));
            saveVd<2>(vd, v3);
        }
        else
        {
            saveVd<1>(vd, v3);
        }
    }
    // VFPU4:VSRT1
    template< int vsize > void doVSRT1(int vd, int vs)
    {
        loadVs<4>(vs);
        float x = v1[0];
        float y = v1[1];
        float z = v1[2];
        float w = v1[3];
        v3[0] = min(x, y);
        v3[1] = max(x, y);
        v3[2] = min(z, w);
        v3[3] = max(z, w);
        saveVd<4>(vd, v3);
    }
    // VFPU4:VSRT2
    template< int vsize > void doVSRT2(int vd, int vs)
    {
        loadVs<4>(vs);
        float x = v1[0];
        float y = v1[1];
        float z = v1[2];
        float w = v1[3];
        v3[0] = min(x, w);
        v3[1] = min(y, z);
        v3[2] = max(y, z);
        v3[3] = max(x, w);
        saveVd<4>(vd, v3);
    }
    // VFPU4:VBFY1
    template< int vsize > void doVBFY1(int vd, int vs)
    {
        loadVs<vsize>(vs);
        float x = v1[0];
        float y = v1[1];
        v3[0] = x + y;
        v3[1] = x - y;
        if (vsize > 2)
        {
            float z = v1[2];
            float w = v1[3];
            v3[2] = z + w;
            v3[3] = z - w;
            saveVd<4>(vd, v3);
        }
        else
        {
            saveVd<2>(vd, v3);
        }
    }
    // VFPU4:VBFY2
    template< int vsize > void doVBFY2(int vd, int vs)
    {
        loadVs<vsize>(vs);
        float x = v1[0];
        float y = v1[1];
        float z = v1[2];
        float w = v1[3];
        v3[0] = x + z;
        v3[1] = y + w;
        v3[2] = x - z;
        v3[3] = y - w;
        saveVd<4>(vd, v3);
    }
    // VFPU4:VOCP
    template< int vsize > void doVOCP(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v1[i] = 1.0f - v1[i];
        }
        saveVd<vsize>(vd, v1);
    }
    // VFPU4:VSOCP
    template< int vsize > void doVSOCP(int vd, int vs)
    {
        loadVs<vsize>(vs);
        float x = v1[0];
        v3[0] = min(max(0.0f, 1.0f - x), 1.0f);
        v3[1] = min(max(0.0f,x), 1.0f);
        if (vsize > 1)
        {
            float y = v1[1];
            v3[2] = min(max(0.0f, 1.0f - y), 1.0f);
            v3[3] = min(max(0.0f, y), 1.0f);
            saveVd<4>(vd, v3);
        }
        else
        {
            saveVd<2>(vd, v3);
        }
    }
    // VFPU4:VFAD
    template< int vsize > void doVFAD(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 1; i < vsize; ++i)
        {
            v1[0] += v1[i];
        }
        saveVd<1>(vd, v1);
    }
    // VFPU4:VAVG
    template< int vsize > void doVAVG(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 1; i < vsize; ++i)
        {
            v1[0] += v1[i];
        }
        v1[0] /= vsize;
        saveVd<1>(vd, v1);
    }
    // VFPU4:VSRT3
    template< int vsize > void doVSRT3(int vd, int vs)
    {
        loadVs<4>(vs);
        float x = v1[0];
        float y = v1[1];
        float z = v1[2];
        float w = v1[3];
        v3[0] = max(x, y);
        v3[1] = min(x, y);
        v3[2] = max(z, w);
        v3[3] = min(z, w);
        saveVd<4>(vd, v3);
    }
    // VFPU4:VSRT4
    template< int vsize > void doVSRT4(int vd, int vs)
    {
        loadVs<4>(vs);
        float x = v1[0];
        float y = v1[1];
        float z = v1[2];
        float w = v1[3];
        v3[0] = max(x, w);
        v3[1] = max(y, z);
        v3[2] = min(y, z);
        v3[3] = min(x, w);
        saveVd<4>(vd, v3);
    }
    // VFPU4:VSGN
    template< int vsize > void doVSGN(int vd, int vs)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = signum(v1[i]);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VMFVC
    void doVMFVC(int vd, int imm7)
    {
        int value = 0;
        switch (imm7)
        {
        case 0: /* 128 */
            value |= vcr.pfxs.swz[0] << 0;
            value |= vcr.pfxs.swz[1] << 2;
            value |= vcr.pfxs.swz[2] << 4;
            value |= vcr.pfxs.swz[3] << 6;
            if (vcr.pfxs.abs[0]) value |=  1 <<  8;
            if (vcr.pfxs.abs[1]) value |=  1 <<  9;
            if (vcr.pfxs.abs[2]) value |=  1 << 10;
            if (vcr.pfxs.abs[3]) value |=  1 << 11;
            if (vcr.pfxs.cst[0]) value |=  1 << 12;
            if (vcr.pfxs.cst[1]) value |=  1 << 13;
            if (vcr.pfxs.cst[2]) value |=  1 << 14;
            if (vcr.pfxs.cst[3]) value |=  1 << 15;
            if (vcr.pfxs.neg[0]) value |=  1 << 16;
            if (vcr.pfxs.neg[1]) value |=  1 << 17;
            if (vcr.pfxs.neg[2]) value |=  1 << 18;
            if (vcr.pfxs.neg[3]) value |=  1 << 19;
            v3[0] = intBitsToFloat(value);
            saveVd<1>(vd, v3);
            break;
        case 1: /* 129 */
            value |= vcr.pfxt.swz[0] << 0;
            value |= vcr.pfxt.swz[1] << 2;
            value |= vcr.pfxt.swz[2] << 4;
            value |= vcr.pfxt.swz[3] << 6;
            if (vcr.pfxt.abs[0]) value |=  1 <<  8;
            if (vcr.pfxt.abs[1]) value |=  1 <<  9;
            if (vcr.pfxt.abs[2]) value |=  1 << 10;
            if (vcr.pfxt.abs[3]) value |=  1 << 11;
            if (vcr.pfxt.cst[0]) value |=  1 << 12;
            if (vcr.pfxt.cst[1]) value |=  1 << 13;
            if (vcr.pfxt.cst[2]) value |=  1 << 14;
            if (vcr.pfxt.cst[3]) value |=  1 << 15;
            if (vcr.pfxt.neg[0]) value |=  1 << 16;
            if (vcr.pfxt.neg[1]) value |=  1 << 17;
            if (vcr.pfxt.neg[2]) value |=  1 << 18;
            if (vcr.pfxt.neg[3]) value |=  1 << 19;
            v3[0] = intBitsToFloat(value);
            saveVd<1>(vd, v3);
            break;
        case 2: /* 130 */
            value |= vcr.pfxd.sat[0] << 0;
            value |= vcr.pfxd.sat[1] << 2;
            value |= vcr.pfxd.sat[2] << 4;
            value |= vcr.pfxd.sat[3] << 6;
            if (vcr.pfxd.msk[0]) value |=  1 <<  8;
            if (vcr.pfxd.msk[1]) value |=  1 <<  9;
            if (vcr.pfxd.msk[2]) value |=  1 << 10;
            if (vcr.pfxd.msk[3]) value |=  1 << 11;
            v3[0] = intBitsToFloat(value);
            saveVd<1>(vd, v3);
            break;
        case 3: /* 131 */
            for (int i = 6 - 1; i >= 0; i--) {
                value <<= 1;
                if (vcr.cc[i]) {
                    value |= 1;
                }
            }
            v3[0] = intBitsToFloat(value);
            saveVd<1>(vd, v3);
            break;
        case 8: /* 136 - RCX0 */
            v3[0] = intBitsToFloat(rnd.GetSeed());
            saveVd<1>(vd, v3);
            break;
        case 9:  /* 137 - RCX1 */
        case 10: /* 138 - RCX2 */
        case 11: /* 139 - RCX3 */
        case 12: /* 140 - RCX4 */
        case 13: /* 141 - RCX5 */
        case 14: /* 142 - RCX6 */
        case 15: /* 143 - RCX7 */
            // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
            v3[0] = intBitsToFloat(0x3f800000);
            saveVd<1>(vd, v3);
            break;
        default:
            break;
        }
    }
    // VFPU4:VMTVC
    void doVMTVC(int vd, int imm7)
    {
        int value = floatToRawIntBits(vd); 
        switch (imm7)
        {
        case 0: /* 128 */
            vcr.pfxs.swz[0] = ((value >> 0 ) & 3);
            vcr.pfxs.swz[1] = ((value >> 2 ) & 3);
            vcr.pfxs.swz[2] = ((value >> 4 ) & 3);
            vcr.pfxs.swz[3] = ((value >> 6 ) & 3);
            vcr.pfxs.abs[0] = ((value >> 8 ) & 1) == 1;
            vcr.pfxs.abs[1] = ((value >> 9 ) & 1) == 1;
            vcr.pfxs.abs[2] = ((value >> 10) & 1) == 1;
            vcr.pfxs.abs[3] = ((value >> 11) & 1) == 1;
            vcr.pfxs.cst[0] = ((value >> 12) & 1) == 1;
            vcr.pfxs.cst[1] = ((value >> 13) & 1) == 1;
            vcr.pfxs.cst[2] = ((value >> 14) & 1) == 1;
            vcr.pfxs.cst[3] = ((value >> 15) & 1) == 1;
            vcr.pfxs.neg[0] = ((value >> 16) & 1) == 1;
            vcr.pfxs.neg[1] = ((value >> 17) & 1) == 1;
            vcr.pfxs.neg[2] = ((value >> 18) & 1) == 1;
            vcr.pfxs.neg[3] = ((value >> 19) & 1) == 1;
            vcr.pfxs.enabled = true;
            break;               
        case 1: /* 129 */
            vcr.pfxt.swz[0] = ((value >> 0 ) & 3);
            vcr.pfxt.swz[1] = ((value >> 2 ) & 3);
            vcr.pfxt.swz[2] = ((value >> 4 ) & 3);
            vcr.pfxt.swz[3] = ((value >> 6 ) & 3);
            vcr.pfxt.abs[0] = ((value >> 8 ) & 1) == 1;
            vcr.pfxt.abs[1] = ((value >> 9 ) & 1) == 1;
            vcr.pfxt.abs[2] = ((value >> 10) & 1) == 1;
            vcr.pfxt.abs[3] = ((value >> 11) & 1) == 1;
            vcr.pfxt.cst[0] = ((value >> 12) & 1) == 1;
            vcr.pfxt.cst[1] = ((value >> 13) & 1) == 1;
            vcr.pfxt.cst[2] = ((value >> 14) & 1) == 1;
            vcr.pfxt.cst[3] = ((value >> 15) & 1) == 1;
            vcr.pfxt.neg[0] = ((value >> 16) & 1) == 1;
            vcr.pfxt.neg[1] = ((value >> 17) & 1) == 1;
            vcr.pfxt.neg[2] = ((value >> 18) & 1) == 1;
            vcr.pfxt.neg[3] = ((value >> 19) & 1) == 1;
            vcr.pfxt.enabled = true;
            break;
        case 2: /* 130 */
            vcr.pfxd.sat[0] = ((value >> 0 ) & 3);
            vcr.pfxd.sat[1] = ((value >> 2 ) & 3);
            vcr.pfxd.sat[2] = ((value >> 4 ) & 3);
            vcr.pfxd.sat[3] = ((value >> 6 ) & 3);
            vcr.pfxd.msk[0] = ((value >> 8 ) & 1) == 1;
            vcr.pfxd.msk[1] = ((value >> 9 ) & 1) == 1;
            vcr.pfxd.msk[2] = ((value >> 10) & 1) == 1;
            vcr.pfxd.msk[3] = ((value >> 11) & 1) == 1;
            vcr.pfxd.enabled = true;
            break;
        case 3: /* 131 */
            for (int i = 0; i < 6; i++) {
                vcr.cc[i] = (value & 1) != 0;
                value >>= 1;
            }
            break;
        case 8: /* 136 - RCX0 */
            rnd.SetSeed(value);
            break;
        case 9:  /* 137 - RCX1 */
        case 10: /* 138 - RCX2 */
        case 11: /* 139 - RCX3 */
        case 12: /* 140 - RCX4 */
        case 13: /* 141 - RCX5 */
        case 14: /* 142 - RCX6 */
        case 15: /* 143 - RCX7 */
            // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
            break;
        default:
            break;
        }
    }
    // VFPU4:VT4444
    template< int vsize > void doVT4444(int vd, int vs)
    {
        loadVs<4>(vs);
        int i0 = floatToRawIntBits(v1[0]);
        int i1 = floatToRawIntBits(v1[1]);
        int i2 = floatToRawIntBits(v1[2]);
        int i3 = floatToRawIntBits(v1[3]);
        int o0 = 0, o1 = 0;
        o0 |= ((i0>> 4)&15) << 0;
        o0 |= ((i0>>12)&15) << 4;
        o0 |= ((i0>>20)&15) << 8;
        o0 |= ((i0>>28)&15) <<12;
        o0 |= ((i1>> 4)&15) <<16;
        o0 |= ((i1>>12)&15) <<20;
        o0 |= ((i1>>20)&15) <<24;
        o0 |= ((i1>>28)&15) <<28;
        o1 |= ((i2>> 4)&15) << 0;
        o1 |= ((i2>>12)&15) << 4;
        o1 |= ((i2>>20)&15) << 8;
        o1 |= ((i2>>28)&15) <<12;
        o1 |= ((i3>> 4)&15) <<16;
        o1 |= ((i3>>12)&15) <<20;
        o1 |= ((i3>>20)&15) <<24;
        o1 |= ((i3>>28)&15) <<28;
        v3[0] = intBitsToFloat(o0);
        v3[1] = intBitsToFloat(o1);
        saveVd<2>(vd, v3);
    }
    // VFPU4:VT5551
    template< int vsize > void doVT5551(int vd, int vs)
    {
        loadVs<4>(vs);


        int i0 = floatToRawIntBits(v1[0]);
        int i1 = floatToRawIntBits(v1[1]);
        int i2 = floatToRawIntBits(v1[2]);
        int i3 = floatToRawIntBits(v1[3]);
       
		int o0 = 0, o1 = 0;
        o0 |= ((i0>> 3)&31) << 0;
        o0 |= ((i0>>11)&31) << 5;
        o0 |= ((i0>>19)&31) <<10;
        o0 |= ((i0>>31)& 1) <<15;
        o0 |= ((i1>> 3)&31) <<16;
        o0 |= ((i1>>11)&31) <<21;
        o0 |= ((i1>>19)&31) <<26;
        o0 |= ((i1>>31)& 1) <<31;
        o1 |= ((i2>> 3)&31) << 0;
        o1 |= ((i2>>11)&31) << 5;
        o1 |= ((i2>>19)&31) <<10;
        o1 |= ((i2>>31)& 1) <<15;
        o1 |= ((i3>> 3)&31) <<16;
        o1 |= ((i3>>11)&31) <<21;
        o1 |= ((i3>>19)&31) <<26;
        o1 |= ((i3>>31)& 1) <<31;
        v3[0] = intBitsToFloat(o0);
        v3[1] = intBitsToFloat(o1);
        saveVd<2>(vd, v3);
    }
    // VFPU4:VT5650
    template< int vsize > void doVT5650(int vd, int vs)
    {
        loadVs<4>(vs);
        int i0 = floatToRawIntBits(v1[0]);
        int i1 = floatToRawIntBits(v1[1]);
        int i2 = floatToRawIntBits(v1[2]);
        int i3 = floatToRawIntBits(v1[3]);
        int o0 = 0, o1 = 0;
        o0 |= ((i0>> 3)&31) << 0;
        o0 |= ((i0>>10)&63) << 5;
        o0 |= ((i0>>19)&31) <<11;
        o0 |= ((i1>> 3)&31) <<16;
        o0 |= ((i1>>10)&63) <<21;
        o0 |= ((i1>>19)&31) <<27;
        o1 |= ((i2>> 3)&31) << 0;
        o1 |= ((i2>>10)&63) << 5;
        o1 |= ((i2>>19)&31) <<11;
        o1 |= ((i3>> 3)&31) <<16;
        o1 |= ((i3>>10)&63) <<21;
        o1 |= ((i3>>19)&31) <<27;
        v3[0] = intBitsToFloat(o0);
        v3[1] = intBitsToFloat(o1);
        saveVd<2>(vd, v3);
    }
    // VFPU4:VCST
    template< int vsize > void doVCST(int vd, int imm5)
    {
        static float floatConstants[] =
        {
            0.0f,
            FLT_MAX,
            sqrtf(2.0f),
            sqrtf(0.5f),
            2.0f / sqrtf((float)M_PI),
            2.0f / (float)M_PI,
            1.0f / (float)M_PI,
            (float)M_PI / 4.0f,
            (float)M_PI / 2.0f,
            (float)M_PI,
            (float)M_E,
            logf((float)M_E) / logf(2.0f), // log2(E) = log(E) / log(2)
            log10f((float)M_E),
            logf(2.0f),
            logf(10.0f),
            (float)M_PI * 2.0f,
            (float)M_PI / 6.0f,
            log10f(2.0),
            logf(10.0f) / logf(2.0f), // log2(10) = log(10) / log(2)
            sqrtf(3.0f) / 2.0f
        };
        float constant = 0.0f;
        if (imm5 >= 0 && imm5 < (int)(sizeof(floatConstants)/sizeof(float)))
        {
            constant = floatConstants[imm5];
        }
        for (int i = 0; i < vsize; ++i)
        {
            v3[i] = constant;
        }
        saveVd<vsize>(vd, v3);
    }

    // VFPU4:VF2IN
    template< int vsize > void doVF2IN(int vd, int vs, int imm5)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            float value = _scalb(v1[i], imm5);
            v3[i] = intBitsToFloat((int)floorf(value + 0.5f));
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VF2IZ
    template< int vsize > void doVF2IZ(int vd, int vs, int imm5)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            float value = _scalb(v1[i], imm5);
            v3[i] = intBitsToFloat(v1[i] >= 0 ? (int) floorf(value) : (int) ceilf(value));
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VF2IU
    template< int vsize > void doVF2IU(int vd, int vs, int imm5)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            float value = _scalb(v1[i], imm5);
            v3[i] = intBitsToFloat((int) ceil(value));
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VF2ID
    template< int vsize > void doVF2ID(int vd, int vs, int imm5)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i) {
            float value = _scalb(v1[i], imm5);
            v3[i] = intBitsToFloat((int) floor(value));
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VI2F
    template< int vsize > void doVI2F(int vd, int vs, int imm5)
    {
        loadVs<vsize>(vs);
        for (int i = 0; i < vsize; ++i)
        {
            float value = (float) floatToRawIntBits(v1[i]);
            v3[i] = _scalb(value, -imm5);
        }
        saveVd<vsize>(vd, v3);
    }
    // VFPU4:VCMOVT
    template< int vsize > void doVCMOVT(int vd, int vs,int imm3)
    {
        if (imm3 < 6)
        {
            if (vcr.cc[imm3])
            {
                loadVs<vsize>(vs);
                saveVd<vsize>(vd, v1);
            }
            else
            {
				vcr.pfxs.enabled = false;
				if (vcr.pfxd.enabled)
				{
                  loadVd<vsize>(vd);
                  saveVd<vsize>(vd, v3);
				}
            }
        }
        else if (imm3 == 6)
        {
            loadVs<vsize>(vs);
            loadVd<vsize>(vd);
            for (int i = 0; i < vsize; ++i)
            {
                if (vcr.cc[i])
                {
                    v3[i] = v1[i];
                }
            }
            saveVd<vsize>(vd, v3);
        }
		else
		{
			//never copy
		}
    }
    // VFPU4:VCMOVF
    template< int vsize > void doVCMOVF(int vd, int vs,int imm3)
    {
        if (imm3 < 6)
        {
            if (!vcr.cc[imm3])
            {
                loadVs<vsize>(vs);
                saveVd<vsize>(vd, v1);
            }
            else
            {
                vcr.pfxs.enabled = false;
                if (vcr.pfxd.enabled)
                {
                    loadVd<vsize>(vd);
                    saveVd<vsize>(vd, v3);
                }
            }
        }
        else if (imm3 == 6)
        {
            loadVs<vsize>(vs);
            loadVd<vsize>(vd);
            for (int i = 0; i < vsize; ++i)
            {
                if (!vcr.cc[i])
                {
                    v3[i] = v1[i];
                }
            }
            saveVd<vsize>(vd, v3);
        }
        else
        {
            loadVs<vsize>(vs);
            saveVd<vsize>(vd, v1);
        }
    }
    // VFPU4:VWBN
    template< int vsize > void doVWBN(int vd, int vs, int imm8)
    {
        (void)vd;
        (void)vs;
        (void)imm8;
        doUNK("Unimplemented VWBN");
    }
    // group VFPU5
    // VFPU5:VPFXS
    void doVPFXS(u32 imm24)
    {
        u32 swzx = (imm24>>0)&3;
        u32 swzy = (imm24>>2)&3;
        u32 swzz = (imm24>>4)&3;
        u32 swzw = (imm24>>6)&3;
        u32 absx = (imm24>>8)&1;
        u32 absy = (imm24>>9)&1;
        u32 absz = (imm24>>10)&1;
        u32 absw = (imm24>>11)&1;
        u32 cstx = (imm24>>12)&1;
        u32 csty = (imm24>>13)&1;
        u32 cstz = (imm24>>14)&1;
        u32 cstw = (imm24>>15)&1;
        u32 negx = (imm24>>16)&1;
        u32 negy = (imm24>>17)&1;
        u32 negz = (imm24>>18)&1;
        u32 negw = (imm24>>19)&1;
        vcr.pfxs.swz[0] = swzx;
        vcr.pfxs.swz[1] = swzy;
        vcr.pfxs.swz[2] = swzz;
        vcr.pfxs.swz[3] = swzw;
        vcr.pfxs.abs[0] = absx != 0;
        vcr.pfxs.abs[1] = absy != 0;
        vcr.pfxs.abs[2] = absz != 0;
        vcr.pfxs.abs[3] = absw != 0;
        vcr.pfxs.cst[0] = cstx != 0;
        vcr.pfxs.cst[1] = csty != 0;
        vcr.pfxs.cst[2] = cstz != 0;
        vcr.pfxs.cst[3] = cstw != 0;
        vcr.pfxs.neg[0] = negx != 0;
        vcr.pfxs.neg[1] = negy != 0;
        vcr.pfxs.neg[2] = negz != 0;
        vcr.pfxs.neg[3] = negw != 0;
        vcr.pfxs.enabled = true;
    }

    // VFPU5:VPFXT
    void doVPFXT(u32 imm24)
    {
        u32 swzx = (imm24>>0)&3;
        u32 swzy = (imm24>>2)&3;
        u32 swzz = (imm24>>4)&3;
        u32 swzw = (imm24>>6)&3;
        u32 absx = (imm24>>8)&1;
        u32 absy = (imm24>>9)&1;
        u32 absz = (imm24>>10)&1;
        u32 absw = (imm24>>11)&1;
        u32 cstx = (imm24>>12)&1;
        u32 csty = (imm24>>13)&1;
        u32 cstz = (imm24>>14)&1;
        u32 cstw = (imm24>>15)&1;
        u32 negx = (imm24>>16)&1;
        u32 negy = (imm24>>17)&1;
        u32 negz = (imm24>>18)&1;
        u32 negw = (imm24>>19)&1;
        vcr.pfxt.swz[0] = swzx;
        vcr.pfxt.swz[1] = swzy;
        vcr.pfxt.swz[2] = swzz;
        vcr.pfxt.swz[3] = swzw;
        vcr.pfxt.abs[0] = absx != 0;
        vcr.pfxt.abs[1] = absy != 0;
        vcr.pfxt.abs[2] = absz != 0;
        vcr.pfxt.abs[3] = absw != 0;
        vcr.pfxt.cst[0] = cstx != 0;
        vcr.pfxt.cst[1] = csty != 0;
        vcr.pfxt.cst[2] = cstz != 0;
        vcr.pfxt.cst[3] = cstw != 0;
        vcr.pfxt.neg[0] = negx != 0;
        vcr.pfxt.neg[1] = negy != 0;
        vcr.pfxt.neg[2] = negz != 0;
        vcr.pfxt.neg[3] = negw != 0;
        vcr.pfxt.enabled = true;
    }

    // VFPU5:VPFXD
    void doVPFXD(u32 imm24)
    {
        u32 satx = (imm24>>0)&3;
        u32 saty = (imm24>>2)&3;
        u32 satz = (imm24>>4)&3;
        u32 satw = (imm24>>6)&3;
        u32 mskx = (imm24>>8)&1;
        u32 msky = (imm24>>9)&1;
        u32 mskz = (imm24>>10)&1;
        u32 mskw = (imm24>>11)&1;
        vcr.pfxd.sat[0] = satx;
        vcr.pfxd.sat[1] = saty;
        vcr.pfxd.sat[2] = satz;
        vcr.pfxd.sat[3] = satw;
        vcr.pfxd.msk[0] = mskx != 0;
        vcr.pfxd.msk[1] = msky != 0;
        vcr.pfxd.msk[2] = mskz != 0;
        vcr.pfxd.msk[3] = mskw != 0;
        vcr.pfxd.enabled = true;
    }

    // VFPU5:VIIM
    void doVIIM(int vd, int imm16)
    {
        v3[0] = (float) imm16;
        saveVd<1>(vd, v3);
    }

    // VFPU5:VFIM
    void doVFIM(int vd, int imm16)
    {        
        v3[0] = halffloatToFloat(imm16);
        saveVd<1>(vd, v3);
    }

    // group VFPU6   
    // VFPU6:VMMUL
    template< int vsize > void doVMMUL(int vd, int vs, int vt)
    {
        // you must do it for disasm, not for emulation !
        //vs = vs ^ 32;
        for (int i = 0; i < vsize; ++i)
        {
            loadVt<vsize>(vt + i);
            for (int j = 0; j < vsize; ++j)
            {
                loadVs<vsize>(vs + j);
                float dot = v1[0] * v2[0];
                for (int k = 1; k < vsize; ++k)
                {
                    dot += v1[k] * v2[k];
                }
                v3[j] = dot;
            }
            saveVd<vsize>(vd + i, v3);
        }
    }

    // VFPU6:VHTFM2
    template< int vsize > void doVHTFM2(int vd, int vs, int vt)
    {
        // you must do it for disasm, not for emulation !
        //vs = vs ^ 32;
        loadVt<1>(vt);
        loadVs<2>(vs + 0);
        v3[0] = v1[0] * v2[0] + v1[1];
        loadVs<2>(vs + 1);
        v3[1] = v1[0] * v2[0] + v1[1];
        saveVd<2>(vd, v3);
    }

    // VFPU6:VTFM2
    template< int vsize > void doVTFM2(int vd, int vs, int vt)
    {
        // you must do it for disasm, not for emulation !
        //vs = vs ^ 32;
        loadVt<2>(vt);
        loadVs<2>(vs + 0);
        v3[0] = v1[0] * v2[0] + v1[1] * v2[1];
        loadVs<2>(vs + 1);
        v3[1] = v1[0] * v2[0] + v1[1] * v2[1];
        saveVd<2>(vd, v3);
    }

    // VFPU6:VHTFM3
    template< int vsize > void doVHTFM3(int vd, int vs, int vt)
    {
        // you must do it for disasm, not for emulation !
        //vs = vs ^ 32;
        loadVt<2>(vt);
        loadVs<3>(vs + 0);
        v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2];
        loadVs<3>(vs + 1);
        v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2];
        loadVs<3>(vs + 2);
        v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2];
        saveVd<3>(vd, v3);
    }

    // VFPU6:VTFM3
    template< int vsize > void doVTFM3(int vd, int vs, int vt)
    {
        // you must do it for disasm, not for emulation !
        //vs = vs ^ 32;
        loadVt<3>(vt);
        loadVs<3>(vs + 0);
        v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
        loadVs<3>(vs + 1);
        v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
        loadVs<3>(vs + 2);
        v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
        saveVd<3>(vd, v3);
    }

    // VFPU6:VHTFM4
    template< int vsize > void doVHTFM4(int vd, int vs, int vt)
    {
        // you must do it for disasm, not for emulation !
        //vs = vs ^ 32;
        loadVt<3>(vt);
        loadVs<4>(vs + 0);
        v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
        loadVs<4>(vs + 1);
        v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
        loadVs<4>(vs + 2);
        v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
        loadVs<4>(vs + 3);
        v3[3] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
        saveVd<4>(vd, v3);
    }

    // VFPU6:VTFM4
    template< int vsize > void doVTFM4(int vd, int vs, int vt)
    {
        // you must do it for disasm, not for emulation !
        //vs = vs ^ 32;
        loadVt<4>(vt);
        loadVs<4>(vs + 0);
        v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
        loadVs<4>(vs + 1);
        v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
        loadVs<4>(vs + 2);
        v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
        loadVs<4>(vs + 3);
        v3[3] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
        saveVd<4>(vd, v3);
    }

    // VFPU6:VMSCL
    template< int vsize > void doVMSCL(int vd, int vs, int vt)
    {
        for (int i = 0; i < vsize; ++i) {
            doVSCL<vsize>(vd + i, vs + i, vt);
        }
    }

    // VFPU6:VCRSP
    template< int vsize > void doVCRSP(int vd, int vs, int vt)
    {
        loadVs<3>(vs);
        loadVt<3>(vt);
        v3[0] = +v1[1] * v2[2] - v1[2] * v2[1];
        v3[1] = +v1[2] * v2[0] - v1[0] * v2[2];
        v3[2] = +v1[0] * v2[1] - v1[1] * v2[0];
        saveVd<3>(vd, v3);
    }

    // VFPU6:VQMUL
    template< int vsize > void doVQMUL(int vd, int vs, int vt)
    {
        loadVs<4>(vs);
        loadVt<4>(vt);
        v3[0] = +v1[0] * v2[3] + v1[1] * v2[2] - v1[2] * v2[1] + v1[3] * v2[0];
        v3[1] = -v1[0] * v2[2] + v1[1] * v2[3] + v1[2] * v2[0] + v1[3] * v2[1];
        v3[2] = +v1[0] * v2[1] - v1[1] * v2[0] + v1[2] * v2[3] + v1[3] * v2[2];
        v3[3] = -v1[0] * v2[0] - v1[1] * v2[1] - v1[2] * v2[2] + v1[3] * v2[3];
        saveVd<4>(vd, v3);
    }

    // VFPU6:VMMOV
    template< int vsize > void doVMMOV(int vd, int vs)
    {
        for (int i = 0; i < vsize; ++i)
        {
            doVMOV<vsize>(vd + i, vs + i);
        }
    }

    // VFPU6:VMIDT
    template< int vsize > void doVMIDT(int vd)
    {
        for (int i = 0; i < vsize; ++i)
        {
            doVIDT<vsize>(vd + i);
        }
    }

    // VFPU6:VMZERO
    template< int vsize > void doVMZERO(int vd)
    {
        for (int i = 0; i < vsize; ++i)
        {
            doVZERO<vsize>(vd + i);
        }
    }

    // VFPU7:VMONE
    template< int vsize > void doVMONE(int vd)
    {
        for (int i = 0; i < vsize; ++i)
        {
            doVONE<vsize>(vd + i);
        }
    }

    // VFPU6:VROT
    template< int vsize > void doVROT(int vd, int vs, int imm5)
    {
        loadVs<1>(vs);
        double a = 0.5 * (float)M_PI * v1[0];
        double ca = cos(a);
        double sa = sin(a);
        int i;
        int si = (imm5 >> 2) & 3;
        int ci = (imm5 >> 0) & 3;
        if (((imm5 & 16) != 0))
        {
            sa = 0.0 - sa;
        }
        if (si == ci)
        {
            for (i = 0; i < vsize; ++i)
            {
                v3[i] = (float) sa;
            }
        }
        else
        {
            for (i = 0; i < vsize; ++i)
            {
                v3[i] = (float) 0.0;
            }
            v3[si] = (float) sa;
        }
        v3[ci] = (float) ca;
        saveVd<vsize>(vd, v3);
    }

    // group VLSU     
    // LSU:LVS
    void doLVS(int vt, int rs, int simm14_a16)
    {
        int s = (vt >> 5) & 3;
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        *((u32 *)(&vpr[m][i][s])) =  Memory::memw(gpr[rs] + simm14_a16);
    }

    // LSU:SVS
    void doSVS(int vt, int rs, int simm14_a16)
    {
        int s = (vt >> 5) & 3;
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        Memory::memw(gpr[rs] + simm14_a16) = *((u32 *)(&vpr[m][i][s]));
    }

    // LSU:LVQ
    void doLVQ(int vt, int rs, int simm14_a16)
    {
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        int address = gpr[rs] + simm14_a16;
        u32 *p =  Memory::addrw(address);
        if ((vt & 32) != 0)
        {
            for (int j = 0; j < 4; ++j)
            {
                *((u32 *)(&vpr[m][j][i])) = *p++;
            }
        }
        else
        {
            for (int j = 0; j < 4; ++j)
            {
                *((u32 *)(&vpr[m][i][j])) = *p++;
            }
        }
    }

    // LSU:LVLQ
    void doLVLQ(int vt, int rs, int simm14_a16)
    {
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        int address = gpr[rs] + simm14_a16;
        int k = 3 - ((address >> 2) & 3);
        u32 *p =  Memory::addrw(address & ~15);
        if ((vt & 32) != 0)
        {
            for (int j = k; j < 4; ++j)
            {
                *((u32 *)(&vpr[m][j][i])) = *p++;
            }
        }
        else
        {
            for (int j = k; j < 4; ++j)
            {
                *((u32 *)(&vpr[m][i][j])) = *p++;
            }
        }
    }

    // LSU:LVRQ
    void doLVRQ(int vt, int rs, int simm14_a16)
    {
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        int address = gpr[rs] + simm14_a16;
        int k = 4 - ((address >> 2) & 3);
        u32 *p =  Memory::addrw(address);
        if ((vt & 32) != 0)
        {
            for (int j = 0; j < k; ++j)
            {
                *((u32 *)(&vpr[m][j][i])) = *p++;
            }
        }
        else
        {
            for (int j = 0; j < k; ++j)
            {
                *((u32 *)(&vpr[m][i][j])) = *p++;
            }
        }
    }

    // LSU:SVQ
    void doSVQ(int vt, int rs, int simm14_a16)
    {
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        int address = gpr[rs] + simm14_a16;
        u32 *p =  Memory::addrw(address);
        if ((vt & 32) != 0)
        {
            for (int j = 0; j < 4; ++j)
            {
                *p++ = *((u32 *)(&vpr[m][j][i]));
            }
        } 
        else
        {
            for (int j = 0; j < 4; ++j)
            {
                *p++ = *((u32 *)(&vpr[m][i][j]));
            }
        }
    }

    void doSVLQ(int vt, int rs, int simm14_a16)
    {
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        int address = gpr[rs] + simm14_a16;
        int k = 3 - ((address >> 2) & 3);
        u32 *p =  Memory::addrw(address & ~15);
        if ((vt & 32) != 0)
        {
            for (int j = k; j < 4; ++j)
            {
                *p++ = *((u32 *)(&vpr[m][j][i]));
            }
        }
        else
        {
            for (int j = k; j < 4; ++j)
            {
                *p++ = *((u32 *)(&vpr[m][i][j]));
            }
        }
    }

    // LSU:SVRQ
    void doSVRQ(int vt, int rs, int simm14_a16)
    {
        int m = (vt >> 2) & 7;
        int i = (vt >> 0) & 3;
        int address = gpr[rs] + simm14_a16;
        int k = 4 - ((address >> 2) & 3);
        u32 *p =  Memory::addrw(address);
        if ((vt & 32) != 0)
        {
            for (int j = 0; j < k; ++j)
            {
                *p++ = *((u32 *)(&vpr[m][j][i]));
            }
        }
        else
        {
            for (int j = 0; j < k; ++j)
            {
                *p++ = *((u32 *)(&vpr[m][i][j]));
            }
        }
    }
//#endif
//
//#endif /* __GNUC__ */

#endif /* VFPU_H_ */
