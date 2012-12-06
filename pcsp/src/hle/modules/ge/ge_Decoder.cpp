#include "stdafx.h"

#include "ge_Decoder.h"
#include "ge_TextureDecoder.h"
#include "ge_Constants.h"
#include "ge_Context.h"
#include "memory/memory.h"
#include "log.h"
#include "ge_DisplayListInterpreter.h"
#include "renderer.h"

#include "opengl/gl_Uniforms.h"

ge_Decoder	theDecoder;

template< u32 N > __forceinline u32 fast_align(u32 value) { return value + (N-1) & ~(N-1); }

static inline u32* spline_knot(u32* knot, u32 n, u32 type)
{
	for(u32 i = 0; i < n - 1; i++) 
		knot[i + 3] = i;
	if((type & 1) == 0) 
	{
		knot[0] = -3;
		knot[1] = -2;
		knot[2] = -1;
	}
	if((type & 2) == 0) 
	{
		knot[n + 2] = n - 1;
		knot[n + 3] = n;
		knot[n + 4] = n + 1;
	} 
	else 
	{
		knot[n + 2] = n - 2;
		knot[n + 3] = n - 2;
		knot[n + 4] = n - 2;
	}
	return knot;
}
float spline_n(u32 i, u32 j, float u, u32* knot) {
	if(j == 0) {
		if(knot[i] <= u && u < knot[i + 1])
			return 1;
		return 0;
	}
	float res = 0;
	if(knot[i + j] - knot[i] != 0)
	    res += (u - knot[i]) / (knot[i + j] - knot[i]) * spline_n(i, j - 1, u, knot);
	if(knot[i + j + 1] - knot[i + 1] != 0)
		res += (knot[i + j + 1] - u) / (knot[i + j + 1] - knot[i + 1]) * spline_n(i + 1, j - 1, u, knot);
	return res;
}

static inline void pointMultAdd(ge_DecodedVertex* dest, ge_DecodedVertex* src, float f, bool useVertexColor, bool useTexture, bool useNormal) 
{
	dest->v[0] += f * src->v[0];
	dest->v[1] += f * src->v[1];
	dest->v[2] += f * src->v[2];
	if(useTexture) 
	{
		dest->t[0] += f * src->t[0];
		dest->t[1] += f * src->t[1];
	}
	if(useVertexColor) 
	{
		dest->c[0] += f * src->c[0];
		dest->c[1] += f * src->c[1];
		dest->c[2] += f * src->c[2];
		dest->c[3] += f * src->c[3];
	}
	if(useNormal) 
	{
		dest->n[0] += f * src->n[0];
		dest->n[1] += f * src->n[1];
		dest->n[2] += f * src->n[2];
	}
}


ge_Decoder::ge_Decoder()
{

}

ge_Decoder::~ge_Decoder()
{

}

__forceinline void pointAdd(ge_DecodedVertex &r, const ge_DecodedVertex &p, const ge_DecodedVertex &q)
{
    r.v[0] = p.v[0] + q.v[0];
    r.v[1] = p.v[1] + q.v[1];
    r.v[2] = p.v[2] + q.v[2];

    r.n[0] = p.n[0] + q.n[0];
    r.n[1] = p.n[1] + q.n[1];
    r.n[2] = p.n[2] + q.n[2];

    r.c[0] = p.c[0] + q.c[0];
    r.c[1] = p.c[1] + q.c[1];
    r.c[2] = p.c[2] + q.c[2];
    r.c[3] = p.c[3] + q.c[3];
}

__forceinline void pointTimes(ge_DecodedVertex &p, float c, const ge_DecodedVertex &q)
{
    p.v[0] = q.v[0] * c;
    p.v[1] = q.v[1] * c;
    p.v[2] = q.v[2] * c;

    p.n[0] = p.n[0] * c;
    p.n[1] = p.n[1] * c;
    p.n[2] = p.n[2] * c;

    p.c[0] = q.c[0] * c;
    p.c[1] = q.c[1] * c;
    p.c[2] = q.c[2] * c;
    p.c[3] = q.c[3] * c;
}

__forceinline void Bernstein(ge_DecodedVertex &r, float u, const ge_DecodedVertex *p)
{
    ge_DecodedVertex a, b, c, d;

    float t  = 1.0f - u;
    float u2 = u*u;
    float t2 = t*t;

    pointTimes(a,      u*u2, p[0]);
    pointTimes(b, 3.0f*t*u2, p[1]);
    pointTimes(c, 3.0f*u*t2, p[2]);
    pointTimes(d,      t*t2, p[3]);

    pointAdd(a, a, b);
    pointAdd(c, c, d);
    pointAdd(r, a, c);
}

__forceinline void PaddingMax(int &x, int y) { if (x < y) x = y; }

void ge_Decoder::SetVertexInfo(ge_VertexInfo &vertexInfo)
{
    // param to parse
    vertexInfo.param = theGeContext.transform_mode;

    // vertex elements
    vertexInfo.tt = (vertexInfo.param >>   0) & 0x3;
    vertexInfo.ct = (vertexInfo.param >>   2) & 0x7;
    vertexInfo.nt = (vertexInfo.param >>   5) & 0x3;
    vertexInfo.vt = (vertexInfo.param >>   7) & 0x3;
    vertexInfo.wt = (vertexInfo.param >>   9) & 0x3;
    vertexInfo.it = (vertexInfo.param >>  11) & 0x3;

    vertexInfo.wc = ((vertexInfo.param >> 14) & 0x7) + 1;
    vertexInfo.mc = ((vertexInfo.param >> 18) & 0x7) + 1;
    vertexInfo.tm = ((vertexInfo.param >> 23) & 0x1) != 0;

    // offsets and alignment size
    u32 offset  = 0;
    int padding = 0;
    u32 type;

    if (!vertexInfo.tm && vertexInfo.wt)
    {
        theGeContext.ChangeUniform(U_WC);
        type = vertexInfo.wt;
        offset += size_mapping[type] * vertexInfo.wc;
        PaddingMax(padding, size_padding[type]);
    }

    if (vertexInfo.tt)
    {
        type = vertexInfo.tt; 
        offset = (offset + size_padding[type]) & ~size_padding[type];
        vertexInfo.texture_offset = offset;
        offset += size_mapping[type] * 2;
        PaddingMax(padding, size_padding[type]);
    }
   
    if (vertexInfo.ct)
    {
        type = vertexInfo.ct;
        offset = (offset + color_size_padding[type]) & ~color_size_padding[type];
        vertexInfo.color_offset = offset;
        offset += color_size_mapping[type];
        PaddingMax(padding, color_size_padding[type]); 
    }
   
    if (!vertexInfo.tm && vertexInfo.nt)
    {
        type = vertexInfo.nt;
        offset = (offset + size_padding[type]) & ~size_padding[type];
        vertexInfo.normal_offset = offset;
        offset += size_mapping[type] * 3;
        PaddingMax(padding, size_padding[type]); 
    }

    type = vertexInfo.vt; 
    offset = (offset + size_padding[type]) & ~size_padding[type];
    vertexInfo.position_offset = offset;    
    offset += size_mapping[type] * 3;
    PaddingMax(padding, size_padding[type]);

    vertexInfo.one_vertex_size = (offset + padding) & ~padding;
    vertexInfo.vertex_size     = vertexInfo.one_vertex_size*vertexInfo.mc;
}

void ge_Decoder::DecodeVertices(ge_VertexInfo &vertexInfo, ge_DecodedVertex *outDecodedVertices, const void *inVertices, const void *inIndices, u32 inCount)
{
    if (vertexInfo.mc == 1 && !vertexInfo.wt)
    {
        theGeContext.morphing_weights[0] = 1.0f;
    }

    for (u32 i = 0; i < inCount; i++)
    {
        int current_address = i;

        switch (vertexInfo.it)
        {
        case 1:
            {
                current_address = ((u8 *)inIndices)[i];
            }
            break;
        case 2:
            {
                current_address = ((u16 *)inIndices)[i];
            }
            break;
        case 3:
            {
                current_address = ((u32*)inIndices)[i];
            }
            break;
        }

        char *vertex_address = ((char *)inVertices) + (vertexInfo.vertex_size * current_address);

        // weights
        if (!vertexInfo.tm && vertexInfo.wt)
        {
            memset(outDecodedVertices[i].w, 0, sizeof(f32)*8);
            switch (vertexInfo.wt)
            {
            case 1:
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    u8 *weightData = (u8 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size));
                    for (u32 skinCounter = 0; skinCounter < vertexInfo.wc; skinCounter++)
                    {
                        outDecodedVertices[i].w[skinCounter] += (f32(weightData[skinCounter]) / 128.0f) * theGeContext.morphing_weights[morphcounter];
                    }
                }
                break;
            case 2:
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    u16 *weightData = (u16 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size));
                    for (u32 skinCounter = 0; skinCounter < vertexInfo.wc; skinCounter++)
                    {
                        outDecodedVertices[i].w[skinCounter] += (f32(weightData[skinCounter]) / 32768.0f) * theGeContext.morphing_weights[morphcounter];
                    }
                }
                break;
            case 3:
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    f32 *weightData = (f32 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size));
                    for (u32 skinCounter = 0; skinCounter < vertexInfo.wc; skinCounter++)
                    {
                        outDecodedVertices[i].w[skinCounter] += weightData[skinCounter] * theGeContext.morphing_weights[morphcounter];
                    }
                }
                break;
            }
        }

        // texture
        if (vertexInfo.tt)
        {
            if (vertexInfo.tm)
            {
                switch (vertexInfo.tt)
                {
                case 1:
                    {
                        u8 *uvdata = (u8 *)(vertex_address + vertexInfo.texture_offset);
                        outDecodedVertices[i].t[0] = f32(uvdata[0]);
                        outDecodedVertices[i].t[1] = f32(uvdata[1]);
                    }
                    break;
                case 2:
                    {
                        u16 *uvdata = (u16 *)(vertex_address + vertexInfo.texture_offset);
                        outDecodedVertices[i].t[0] = f32(uvdata[0]);
                        outDecodedVertices[i].t[1] = f32(uvdata[1]);
                    }
                    break;
                case 3:
                    {
                        f32 *uvdata = (f32 *)(vertex_address + vertexInfo.texture_offset);
                        outDecodedVertices[i].t[0] = uvdata[0];
                        outDecodedVertices[i].t[1] = uvdata[1];
                    }
                    break;
                }
            }
            else
            {
                f32 morphUV[2] = { 0.0f, 0.0f };
                switch (vertexInfo.tt)
                {
                case 1:
                    for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                    {
                        u8 *uvdata = (u8 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.texture_offset);

                        morphUV[0] += (f32(uvdata[0]) / 128.0f) * theGeContext.morphing_weights[morphcounter];
                        morphUV[1] += (f32(uvdata[1]) / 128.0f) * theGeContext.morphing_weights[morphcounter];
                    }
                    break;
                case 2:
                    for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                    {
                        u16 *uvdata = (u16 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.texture_offset);

                        morphUV[0] += (f32(uvdata[0]) / 32768.0f) * theGeContext.morphing_weights[morphcounter];
                        morphUV[1] += (f32(uvdata[1]) / 32768.0f) * theGeContext.morphing_weights[morphcounter];
                    }
                    break;
                case 3:
                    for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                    {
                        f32 *uvdata = (f32 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.texture_offset);

                        morphUV[0] += uvdata[0] * theGeContext.morphing_weights[morphcounter];
                        morphUV[1] += uvdata[1] * theGeContext.morphing_weights[morphcounter];
                    }
                    break;
                }
                outDecodedVertices[i].t[0] = morphUV[0];
                outDecodedVertices[i].t[1] = morphUV[1];
            }
        }

        // color
        if (vertexInfo.ct)
        {
            memset(outDecodedVertices[i].c, 0, sizeof(f32)*4);
            switch(vertexInfo.ct)
            {
            case 1:
            case 2:
            case 3:
                break;
            case 4: // GU_COLOR_5650
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    u16 current_color = *(u16 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.color_offset);
                    f32 r,g,b;

                    r = f32(current_color>>( 0) & 0x1f) / 31.0f;
                    g = f32(current_color>>( 5) & 0x3f) / 63.0f;
                    b = f32(current_color>>(11) & 0x1f) / 31.0f;

                    outDecodedVertices[i].c[0] += r * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[1] += g * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[2] += b * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[3] +=     theGeContext.morphing_weights[morphcounter];
                }
            case 5: // GU_COLOR_5551
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    u16 current_color = *(u16 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.color_offset);
                    f32 r,g,b,a;

                    r = f32(current_color>>(0*5) & 0x1f) / 31.0f;
                    g = f32(current_color>>(1*5) & 0x1f) / 31.0f;
                    b = f32(current_color>>(2*5) & 0x1f) / 31.0f;
                    a = f32(current_color>>(3*5));

                    outDecodedVertices[i].c[0] += r * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[1] += g * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[2] += b * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[3] += a * theGeContext.morphing_weights[morphcounter];
                }
            case 6: // GU_COLOR_4444
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    u16 current_color = *(u16 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.color_offset);
                    float r,g,b,a;

                    r = f32(current_color>>(0*4) & 0xF) / 15.0f;
                    g = f32(current_color>>(1*4) & 0xF) / 15.0f;
                    b = f32(current_color>>(2*4) & 0xF) / 15.0f;
                    a = f32(current_color>>(3*4) & 0xF) / 15.0f;

                    outDecodedVertices[i].c[0] += r * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[1] += g * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[2] += b * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[3] += a * theGeContext.morphing_weights[morphcounter];
                }
                break;
            case 7: // GU_COLOR_8888
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
					u32 current_color = *(u32 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.color_offset);
                    f32 r,g,b,a;

                    r = f32(current_color>>(0*8) & 0xff) / 255.0f;
                    g = f32(current_color>>(1*8) & 0xff) / 255.0f;
                    b = f32(current_color>>(2*8) & 0xff) / 255.0f;
                    a = f32(current_color>>(3*8) & 0xff) / 255.0f;

                    outDecodedVertices[i].c[0] += r * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[1] += g * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[2] += b * theGeContext.morphing_weights[morphcounter];
                    outDecodedVertices[i].c[3] += a * theGeContext.morphing_weights[morphcounter];
                }
                break;
            }
        }


        // normals
        if (!vertexInfo.tm && vertexInfo.nt)
        {
            float morphNormals[3] = { 0.0f, 0.0f, 0.0f};
            switch (vertexInfo.nt)
            {
            case 1:
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    s8 *float_normals = (s8 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.normal_offset);

                    morphNormals[0] += f32(float_normals[0]) / 127.0f * theGeContext.morphing_weights[morphcounter];
                    morphNormals[1] += f32(float_normals[1]) / 127.0f * theGeContext.morphing_weights[morphcounter];
                    morphNormals[2] += f32(float_normals[2]) / 127.0f * theGeContext.morphing_weights[morphcounter];
                }
                break;
            case 2:
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    s16 *float_normals = (s16 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.normal_offset);

                    morphNormals[0] += f32(float_normals[0]) / 32767.0f * theGeContext.morphing_weights[morphcounter];
                    morphNormals[1] += f32(float_normals[1]) / 32767.0f * theGeContext.morphing_weights[morphcounter];
                    morphNormals[2] += f32(float_normals[2]) / 32767.0f * theGeContext.morphing_weights[morphcounter];
                }
                break;
            case 3:
                for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                {
                    f32 *float_normals = (f32 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.normal_offset);

                    morphNormals[0] += f32(float_normals[0]) * theGeContext.morphing_weights[morphcounter];
                    morphNormals[1] += f32(float_normals[1]) * theGeContext.morphing_weights[morphcounter];
                    morphNormals[2] += f32(float_normals[2]) * theGeContext.morphing_weights[morphcounter];
                }
                break;
            }
            outDecodedVertices[i].n[0] = morphNormals[0];
            outDecodedVertices[i].n[1] = morphNormals[1];
            outDecodedVertices[i].n[2] = morphNormals[2];
        }

        // position
        if (vertexInfo.vt)
        {
            if (vertexInfo.tm)
            {
                switch (vertexInfo.vt)
                {
                case 1:
                    {
                        u8 *current_vertex = (u8 *)(vertex_address + vertexInfo.position_offset);
                        outDecodedVertices[i].v[0] = f32(s32(s8(current_vertex[0])));
                        outDecodedVertices[i].v[1] = f32(s32(s8(current_vertex[1])));
                        outDecodedVertices[i].v[2] = f32(u32(u8(current_vertex[2])));
                    }
                    break;
                case 2:
                    {
                        u16 *current_vertex = (u16 *)(vertex_address + vertexInfo.position_offset);
                        outDecodedVertices[i].v[0] = f32(s32(s16(current_vertex[0])));
                        outDecodedVertices[i].v[1] = f32(s32(s16(current_vertex[1])));
                        outDecodedVertices[i].v[2] = f32(u32(u16(current_vertex[2])));
                    }
                    break;
                case 3:
                    {
                        f32 *current_vertex = (f32 *)(vertex_address + vertexInfo.position_offset);
                        outDecodedVertices[i].v[0] = current_vertex[0];
                        outDecodedVertices[i].v[1] = current_vertex[1];
                        outDecodedVertices[i].v[2] = current_vertex[2];
                    }
                    break;
                }
            }
            else
            {
                float morphVerts[3] = { 0.0f, 0.0f, 0.0f };
                switch (vertexInfo.vt)
                {
                case 1:
                    for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                    {
                        s8 *current_vertex = (s8 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.position_offset);

                        morphVerts[0] += f32(current_vertex[0]) / 127.0f * theGeContext.morphing_weights[morphcounter];
                        morphVerts[1] += f32(current_vertex[1]) / 127.0f * theGeContext.morphing_weights[morphcounter];
                        morphVerts[2] += f32(current_vertex[2]) / 127.0f * theGeContext.morphing_weights[morphcounter];
                    }
                    break;
                case 2:
                    for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                    {
                        s16 *current_vertex = (s16 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.position_offset);
                        {
                            morphVerts[0] += f32(current_vertex[0]) / 32767.0f * theGeContext.morphing_weights[morphcounter];
                            morphVerts[1] += f32(current_vertex[1]) / 32767.0f * theGeContext.morphing_weights[morphcounter];
                            morphVerts[2] += f32(current_vertex[2]) / 32767.0f * theGeContext.morphing_weights[morphcounter];
                        }
                    }
                    break;
                case 3:
                    for (u32 morphcounter = 0; morphcounter < vertexInfo.mc; morphcounter++)
                    {
                        f32 *current_vertex = (f32 *)(vertex_address + (morphcounter * vertexInfo.one_vertex_size) + vertexInfo.position_offset);

                        morphVerts[0] += current_vertex[0] * theGeContext.morphing_weights[morphcounter];
                        morphVerts[1] += current_vertex[1] * theGeContext.morphing_weights[morphcounter];
                        morphVerts[2] += current_vertex[2] * theGeContext.morphing_weights[morphcounter];
                    }
                    break;
                }
                outDecodedVertices[i].v[0] = morphVerts[0];
                outDecodedVertices[i].v[1] = morphVerts[1];
                outDecodedVertices[i].v[2] = morphVerts[2];
            }
        }
    }
}

void ge_Decoder::ConvertToQuads(ge_DecodedVertex *inDecodedVertices, ge_DecodedVertex *outDecodedVertices, u32 inCount)
{
    int i = 0;

    for(u32 i2 = 0; i2 < inCount; ++i2, ++i)
    {
        u32 i1 = i2++;
        u32 ix;
        u32 iy;

        ge_DecodedVertex &v1 = inDecodedVertices[i1];
        ge_DecodedVertex &v2 = inDecodedVertices[i2];

        if ((v2.v[0] - v1.v[0]) * (v2.v[1] - v1.v[1]) < 0)
        {
            ix = i2;
            iy = i1;
        }
        else
        {
            ix = i1;
            iy = i2;
        }

        ge_DecodedVertex &vx = inDecodedVertices[ix];
        ge_DecodedVertex &vy = inDecodedVertices[iy];

#if 0 // QUADS
        //1
        outDecodedVertices[i].t[0] = v1.t[0]; // 1----------------- -----------------* *----------------- -----------------1
        outDecodedVertices[i].t[1] = v1.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = v1.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = v1.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // -----------------* 1----------------- -----------------1 *-----------------

        //2
        i++;
        outDecodedVertices[i].t[0] = vx.t[0]; // 1----------------- -----------------* *----------------2 2----------------1
        outDecodedVertices[i].t[1] = vy.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = vx.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = vy.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // 2----------------* 1----------------2 -----------------1 *-----------------

        //3
        i++;
        outDecodedVertices[i].t[0] = v2.t[0]; // 1----------------- -----------------3 3----------------2 2----------------1
        outDecodedVertices[i].t[1] = v2.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = v2.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = v2.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // 2----------------3 1----------------2 -----------------1 3-----------------

        //4
        i++;
        outDecodedVertices[i].t[0] = vy.t[0]; // 1----------------4 4----------------3 3----------------2 2----------------1
        outDecodedVertices[i].t[1] = vx.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = vy.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = vx.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // 2----------------3 1----------------2 4----------------1 3----------------4
#else // TRIANGLE_STRIP
        //1
        outDecodedVertices[i].t[0] = vx.t[0]; // ^----------------- -----------------* *----------------1 1----------------^
        outDecodedVertices[i].t[1] = vy.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = vx.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = vy.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // 1----------------* ^----------------1 -----------------^ *-----------------

        //2
        i++;
        outDecodedVertices[i].t[0] = v1.t[0]; // 2----------------- -----------------* *----------------1 1----------------2
        outDecodedVertices[i].t[1] = v1.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = v1.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = v1.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // 1----------------* 2----------------1 -----------------2 *-----------------

        //3
        i++;
        outDecodedVertices[i].t[0] = v2.t[0]; // 2----------------- -----------------3 3----------------1 1----------------2
        outDecodedVertices[i].t[1] = v2.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = v2.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = v2.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // 1----------------3 2----------------1 -----------------2 3-----------------

        //4
        i++;
        outDecodedVertices[i].t[0] = vy.t[0]; // 2----------------4 4----------------3 3----------------1 1----------------2
        outDecodedVertices[i].t[1] = vx.t[1]; // |                | |                | |                | |                |
        outDecodedVertices[i].v[0] = vy.v[0]; // |    xxxxxxxx    | |    x           | |           x    | |    xxxxxxxx    |
        outDecodedVertices[i].v[1] = vx.v[1]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].v[2] = v2.v[2]; // |    xxxxx       | |    x  x        | |       xxxxx    | |        x  x    |
        outDecodedVertices[i].c[0] = v2.c[0]; // |    x           | |    x  x        | |           x    | |        x  x    |
        outDecodedVertices[i].c[1] = v2.c[1]; // |    x           | |    xxxxxxxx    | |    xxxxxxxx    | |           x    |
        outDecodedVertices[i].c[2] = v2.c[2]; // |                | |                | |                | |                |
        outDecodedVertices[i].c[3] = v2.c[3]; // 1----------------3 2----------------1 4----------------2 3----------------4
#endif
    }
}

void ge_Decoder::DecodeBezierSurface(ge_VertexInfo &vertexInfo, ge_DecodedVertex *&outVertices, u32 &outCount, const void *inVertices, const void *inIndices, u32 ucount, u32 vcount)
{
    int udivs = theGeContext.patch_div_u;
    int vdivs = theGeContext.patch_div_v;

    if (ucount != 4 || vcount != 4 || udivs < 1 || vdivs < 1 || MAX_PATCH_DIVS < udivs || MAX_PATCH_DIVS < vdivs)
    {
        errorf(dList, "Unsupported bezier format");
        return;
    }

    static ge_DecodedVertex vertex_array[(MAX_PATCH_DIVS+1)*(MAX_PATCH_DIVS+1)*2];
    static ge_DecodedVertex anchors[4][4];
    static ge_DecodedVertex temp[4];
    static ge_DecodedVertex last[MAX_PATCH_DIVS+1];
    
    theDecoder.DecodeVertices(vertexInfo, (ge_DecodedVertex *)anchors, inVertices, inIndices, vcount * ucount);
    
    int	  u = 0, v;
    float py1, px1, py0; 

    for (u32 u = 0; u < ucount; u++)
    {
        temp[u] = anchors[u][3];
    }

    for (v = 0; v <= vdivs; v++) 
    {
        px1 = ((float)v)/((float)vdivs);

        Bernstein(last[v], px1, temp);
    }

    py0 = 1.0f;

    ge_DecodedVertex *vertex = vertex_array;

    float uScale = theGeContext.texture_scale_u;
    float vScale = theGeContext.texture_scale_v;
    float uOffset = theGeContext.texture_offset_u;
    float vOffset = theGeContext.texture_offset_v;

    (void)uScale;
    (void)vScale;
    (void)uOffset;
    (void)vOffset;

    for (u = 1; u <= udivs; u++) 
    {
        py1 = ((float)u)/((float)udivs);			
        Bernstein(temp[0], py1, anchors[0]);		
        Bernstein(temp[1], py1, anchors[1]);
        Bernstein(temp[2], py1, anchors[2]);
        Bernstein(temp[3], py1, anchors[3]);
        py1 = 1.0f - py1;

        for (v = 0; v <= vdivs; v++) 
        {
            ::memcpy(vertex[0].v, last[v].v, sizeof(vertex[0].v));
            ::memcpy(vertex[0].c, last[v].c, sizeof(vertex[0].c));
            ::memcpy(vertex[0].n, last[v].n, sizeof(vertex[0].n));

            px1 = ((float)v)/((float)vdivs);
            Bernstein(last[v], px1, temp);
            px1 = 1.0f - px1;

            ::memcpy(vertex[1].v, last[v].v, sizeof(vertex[1].v));
            ::memcpy(vertex[1].c, last[v].c, sizeof(vertex[1].c));
            ::memcpy(vertex[1].n, last[v].n, sizeof(vertex[0].n));

            vertex[0].t[0] = py0;
            vertex[0].t[1] = px1;
            vertex[1].t[0] = py1;
            vertex[1].t[1] = px1;
            
            vertex += 2;
        }

        py0 = py1;
    }

    outVertices = vertex_array;
    outCount    = vertex - vertex_array;
}

void ge_Decoder::DecodeSplineSurface(ge_VertexInfo &inInfo, ge_DecodedVertex *&outVertices, u32 &outCount, const void *inVertices, const void *inIndices, u32 ucount, u32 vcount, u32 uf, u32 vf)
{
	outCount = 0;
	u32 uvcount = vcount * ucount;
    ge_DecodedVertex* anchors = new ge_DecodedVertex[uvcount];
	ge_DecodedVertex* decoded = new ge_DecodedVertex[uvcount];
	memset(anchors, 0 , sizeof(ge_DecodedVertex) * uvcount);
	memset(decoded, 0 , sizeof(ge_DecodedVertex) * uvcount);
	theDecoder.DecodeVertices(inInfo, (ge_DecodedVertex *)anchors, inVertices, inIndices, uvcount);

    u32 n = ucount - 1;
    u32 m = vcount - 1;
    u32 *knot_u = new u32[n + 5];
	u32 *knot_v = new u32[m + 5];

	memset(knot_u, 0, sizeof(u32) * (n+5));
	memset(knot_v, 0, sizeof(u32) * (m+5));

	spline_knot(knot_u, n, uf);
    spline_knot(knot_v, m, vf);

	float limit = 2.000001f;
	u32 cnt = 0;
	for (u32 u = 0; u < ucount; u++)
    {
		for (u32 v = 0; v < vcount; v++) 
		{
			decoded[u * ucount + v] = anchors[cnt++];
		}
	}

	for (u32 j = 0; j <= theGeContext.patch_div_v; j++) 
	{
		float v = (float)j * (float)(m - limit) / (float)theGeContext.patch_div_v;
		for (u32 i = 0; i <= theGeContext.patch_div_u; i++) 
		{
			float u = (float)i * (float)(n - limit) / (float)theGeContext.patch_div_u;
			ge_DecodedVertex* p = &anchors[i * (theGeContext.patch_div_v+1) + j];
			memset(p, 0, sizeof(ge_DecodedVertex));
			for (u32 ii = 0; ii <= n; ii++) 
			{
				for (u32 jj = 0; jj <= m; jj++) 
				{
					float f = spline_n(ii, 3, u, knot_u) * spline_n(jj, 3, v, knot_v);
					if (f != 0)
                    {
						pointMultAdd(p, &decoded[jj * (n+1) + ii], f, inInfo.ct, inInfo.tt, inInfo.nt);
					}
				}
			}
			
			if (theGeContext.texture_mapping_enable && theGeContext.texture_storage == 0)
            {
				p->t[0] = u;
				p->t[1] = v;
			}
		}
	}

    for (u32 j = 0; j <= theGeContext.patch_div_u; j++) 
    {
        for (u32 i = 0; i <= theGeContext.patch_div_v; i++) 
        {
            outVertices[outCount+0] = decoded[i*(theGeContext.patch_div_v+2) + j + 0];
            outVertices[outCount+1] = decoded[i*(theGeContext.patch_div_v+2) + j + 1];
            outCount +=2;
        }
    }
	safe_delete_array(anchors);
	safe_delete_array(decoded);
	safe_delete_array(knot_u);
	safe_delete_array(knot_v);
}