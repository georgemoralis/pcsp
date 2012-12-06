#ifndef gl_Texture_h__
#define gl_Texture_h__

#include "gl_Core.h"
#include "gl_States.h"

class gl_Texture : protected gl_Core
{
public:

protected:
    GLuint m_id;
};

class gl_SwizzledTexture : protected gl_Texture
{
    static char const UNSWIZZLER_FS[] =
        "#version 140\n"
        "#define BPP %BPP%"
        "uniform int log2_w;"
        "uniform sampler1D base;" 
        "float unswizzle(int offset, int log2_w)"
        "{"
        "   if (log2_w <= 4) return float(offset);"
        "   int w_mask = (1 << log2_w) - 1;"
        "   ivec2 m = ivec2(offset & 0xf,                   offset & 0x70);"
        "   ivec2 b = ivec2(offset & ((w_mask & 0xf) << 7), offset & (~7 << log2_w));"   
        "   return float(b.y | (b.x >> 3) | (m.y << (log2_w - 4)) | m.x);
        "}"
        "void main()"
        "{" 
        "   float index  = unswizzle(int(gl_TexCoord[0].x) + int(gl_TexCoord[0].y) << log2_w, log2_w)/%BPP%;" 
        "   gl_FragColor = texture1D(base, (index + 0.5) / pow(float(1 << log2_w), 2.0)).rgba;"
        "}"
        ;
};

class gl_DepalettizedTexture : protected gl_Texture
{
    static char const DEPALETTIZER_FS[] =
        "#version 140\n"
        "#define NUM_COLORS %NUM_COLORS%\n"
        "uniform sampler2D base;"
        "uniform sampler1D clut;"
        "void main()"
        "{"
        "   float sample = texture2D(base, gl_TexCoord[0].xy).r;\n"
        "   float index  = floor(sample * float(NUM_COLORS-1));\n"
        "   gl_FragColor = texture1D(u_Palette, (index + 0.5) / float(NUM_COLORS)).rgba;\n"
        "}"
        ;
};

#endif // gl_Texture_h__
