#ifndef gl_shaderprogram_h__
#define gl_shaderprogram_h__


//#include <QtOpenGL>
#include <qglshaderprogram.h>
#include "gl_Uniforms.h"
#include "gl_Attributes.h"
#include "gl_ShaderPreprocessor.h"

class gl_ShaderProgram : public QGLShaderProgram, protected gl_Core
{
public:
    enum
    {
        VS_SKINNING           =  1,
        VS_LIGHTING           =  2,
        VS_TEXTURE_MAPPING    =  4
    };

    enum
    {
        PS_TEXTURE_MAPPING    =    1,
        PS_FOGGING            =    2,
        PS_SCISSORING         =    4,
        PS_DEPTH_RANGE_TEST   =    8,
        PS_COLOR_TEST         =   16,
        PS_ALPHA_TEST         =   32,
        PS_STENCIL_TEST       =   64,
        PS_DEPTH_TEST         =  128,
        PS_ALPHA_BLENDING     =  256,
        PS_DITHERING          =  512,
        PS_LOGICAL_OPERATIONS = 1024,
        PS_MASKING            = 2048
    };

    gl_ShaderProgram(u32 key)
    :   QGLShaderProgram()
    ,   m_linked(false)
    {
        QByteArray vsource;
        QByteArray psource;

        QDir::current().mkdir("shaders");

        QString vkey = QString("0x%1").arg(key, 8, 16, QLatin1Char('0'));
        QString pkey = QString("0x%1").arg(key, 8, 16, QLatin1Char('0'));

        {
            QFile vfile(QString("./shaders/[%1]v.glsl").arg(vkey));
            QFile pfile(QString("./shaders/[%1]f.glsl").arg(pkey));

            memset(m_location,        -1, sizeof(m_location));
            memset(m_uniform_changes, -1, sizeof(m_uniform_changes));

            bool no_vfile = false;
            if (!QFile::exists(vfile.fileName()))
            {
                vfile.setFileName(":/shaders/vstage.glsl");
                no_vfile = true;
            }

            bool no_pfile = false;
            if (!QFile::exists(pfile.fileName()))
            {
                pfile.setFileName(":/shaders/fstage.glsl");
                no_pfile = true;
            }

            vfile.open(QIODevice::ReadOnly);
            pfile.open(QIODevice::ReadOnly);

            vsource = vfile.readAll();
            psource = pfile.readAll();

            if (no_vfile)
            {
                gl_ShaderPreprocessor preprocessor;

                vsource.replace("GE_VTYPE_TT", QString::number(((key >>  0) & 3)).toAscii().constData()); 
                vsource.replace("GE_VTYPE_CT", QString::number(((key >>  2) & 7)).toAscii().constData()); 
                vsource.replace("GE_VTYPE_NT", QString::number(((key >>  5) & 3)).toAscii().constData()); 
                vsource.replace("GE_VTYPE_VT", QString::number(((key >>  7) & 3)).toAscii().constData()); 
                vsource.replace("GE_VTYPE_WT", QString::number(((key >>  9) & 3)).toAscii().constData()); 
                vsource.replace("GE_VTYPE_WC", QString::number(((key >> 14) & 7)).toAscii().constData()); 
                vsource.replace("GE_VTYPE_TM", QString::number(((key >> 23) & 1)).toAscii().constData()); 

                if (preprocessor.Preprocess(vsource))
                {
                    vsource = preprocessor.Result().toAscii();

                    QFile vout(QString("./shaders/[%1]v.glsl").arg(vkey));
                    vout.open(QIODevice::WriteOnly);
                    vout.write(vsource);
                }
            }

            vsource.prepend("#version 140\n#extension GL_EXT_gpu_shader4 : enable\n");

            if (no_pfile)
            {
                gl_ShaderPreprocessor preprocessor;

                psource.replace("GE_VTYPE_TM", QString::number(((key >> 23) & 1)).toAscii().constData()); 

                if (preprocessor.Preprocess(psource))
                {
                    psource = preprocessor.Result().toAscii();

                    QFile pout(QString("./shaders/[%1]f.glsl").arg(pkey));
                    pout.open(QIODevice::WriteOnly);
                    pout.write(psource);
                }
            }

            psource.prepend("#version 140\n#extension GL_EXT_gpu_shader4 : enable\n");
        }

        if (!addShaderFromSourceCode(QGLShader::Vertex, vsource))
        {
            QByteArray errors = log().toAscii();
            errorf(Renderer, "ShaderProgram Failure : Vertex shader compiler : %s", errors.constData());
        }
        else
        {
            QByteArray infos = log().toAscii();
            infof(Renderer, "ShaderProgram Success : Vertex shader compiler : %s", infos.constData());

            if (!addShaderFromSourceCode(QGLShader::Fragment, psource))
            {
                QByteArray errors = log().toAscii();
                errorf(Renderer, "ShaderProgram Failure : Fragment shader compiler : %s", errors.constData());
            }
            else
            {
                QByteArray infos = log().toAscii();
                infof(Renderer, "ShaderProgram Success : Fragment shader compiler : %s", infos.constData());

                if (!link())
                {
                    QByteArray errors = log().toAscii();
                    errorf(Renderer, "ShaderProgram Failure : linker :  %s", errors.constData());
                }
                else
                {
                    QByteArray infos = log().toAscii();
                    infof(Renderer, "ShaderProgram Success : linker :  %s", infos.constData());

                    m_linked = true;

                    int program_id = programId();

                    m_location[U_VFLAGS] = glGetUniformLocation(program_id, "vflags");
                    m_location[U_PFLAGS] = glGetUniformLocation(program_id, "pflags");
                    m_location[U_BM    ] = glGetUniformLocation(program_id, "BM");
                    m_location[U_WC    ] = glGetUniformLocation(program_id, "WC");
                    m_location[U_WM    ] = glGetUniformLocation(program_id, "WM");
                    m_location[U_VM    ] = glGetUniformLocation(program_id, "VM");
                    m_location[U_PM    ] = glGetUniformLocation(program_id, "PM");
                    m_location[U_LE    ] = glGetUniformLocation(program_id, "Le");
                    m_location[U_LMADS ] = glGetUniformLocation(program_id, "Lmads");
                    m_location[U_LTYPE ] = glGetUniformLocation(program_id, "LTYPE");
                    m_location[U_LV    ] = glGetUniformLocation(program_id, "LV");
                    m_location[U_LD    ] = glGetUniformLocation(program_id, "LD");
                    m_location[U_LAC   ] = glGetUniformLocation(program_id, "LAC");
                    m_location[U_LDC   ] = glGetUniformLocation(program_id, "LDC");
                    m_location[U_LSC   ] = glGetUniformLocation(program_id, "LSC");
                    m_location[U_MC    ] = glGetUniformLocation(program_id, "MC");
                    m_location[U_LKA   ] = glGetUniformLocation(program_id, "LKA");
                    m_location[U_LKS   ] = glGetUniformLocation(program_id, "LKS");
                    m_location[U_LKO   ] = glGetUniformLocation(program_id, "LKO");
                    m_location[U_AC    ] = glGetUniformLocation(program_id, "AC");
                    m_location[U_MK    ] = glGetUniformLocation(program_id, "MK");
                    m_location[U_TMAP  ] = glGetUniformLocation(program_id, "Tmap");
                    m_location[U_TSHADE] = glGetUniformLocation(program_id, "Tshade");
                    m_location[U_TDATA ] = glGetUniformLocation(program_id, "Tdata");
                    m_location[U_TFUNC ] = glGetUniformLocation(program_id, "Tfunc");
                    m_location[U_TRGB  ] = glGetUniformLocation(program_id, "Trgb");
                    m_location[U_TSCALE] = glGetUniformLocation(program_id, "Tscale");
                    m_location[U_TTRANS] = glGetUniformLocation(program_id, "Ttrans");
                    m_location[U_TPROJ ] = glGetUniformLocation(program_id, "Tproj");
                    m_location[U_TSIZE ] = glGetUniformLocation(program_id, "Tsize");
                    m_location[U_CTEST ] = glGetUniformLocation(program_id, "Cfnc");
                    m_location[U_CREF  ] = glGetUniformLocation(program_id, "Cref");
                    m_location[U_CMSK  ] = glGetUniformLocation(program_id, "Cmsk");
                    m_location[U_NREV  ] = glGetUniformLocation(program_id, "NREV");

                    m_in[A_POSITION ] = glGetAttribLocation(program_id, "Pv");
                    m_in[A_NORMAL   ] = glGetAttribLocation(program_id, "Nv");
                    m_in[A_TEXTURE  ] = glGetAttribLocation(program_id, "Tv");
                    m_in[A_COLOR    ] = glGetAttribLocation(program_id, "Cv");
                    m_in[A_WEIGHT0_3] = glGetAttribLocation(program_id, "Wv_0_3");
                    m_in[A_WEIGHT4_7] = glGetAttribLocation(program_id, "Wv_4_7");

                    //m_out[V_COLOR] = glGetFragDataLocation(program_id, "Cf");
                }
            }
        }
    }

    ~gl_ShaderProgram()
    {
    }

    bool Linked()
    {
        return m_linked;
    }

    bool Bind()
    {
        return bind();
    }

    void Unbind()
    {
        release();
    }

    __forceinline int Location(int u) const { return m_location[u]; }

    __forceinline int Attribute(int a) const { return m_in[a]; }

    __forceinline int UniformChanges(int u) const { return m_uniform_changes[u]; }

    __forceinline int &UniformChanges(int u) { return m_uniform_changes[u]; }

    __forceinline void SetTexCoordPointer(u32 size, u32 type, u32 stride, u32 offset)
    {
        SetVertexAttribPointer(A_TEXTURE, size, type, false, stride, offset);
    }

    __forceinline void SetColorPointer(u32 size, u32 type, u32 stride, u32 offset)
    {
        SetVertexAttribPointer(A_COLOR, size, type, false, stride, offset);
    }

    __forceinline void SetVertexPointer(u32 size, u32 type, u32 stride, u32 offset)
    {
        SetVertexAttribPointer(A_POSITION, size, type, false, stride, offset);
    }

    __forceinline void SetNormalPointer(u32 type, u32 stride, u32 offset)
    {
        SetVertexAttribPointer(A_NORMAL, 3, type, false, stride, offset);
    }

    __forceinline void SetWeightPointer(u32 size, u32 type, u32 stride, u32 offset0_3, u32 offset4_7)
    {
        SetVertexAttribPointer(A_WEIGHT0_3, 4, type, false, stride, offset0_3);
        if (size > 3)
        {
            SetVertexAttribPointer(A_WEIGHT4_7, 4, type, false, stride, offset4_7);
        }
    }

    __forceinline void SetVertexAttribPointer(u32 id, u32 size, u32 type, bool normalized, u32 stride, u32 offset)
    {
        GLuint aid = m_in[id];
        glVertexAttribPointer(aid, GLint(size), GLenum(type), GLboolean(normalized), GLsizei(stride), (GLvoid const *)offset);
        glEnableVertexAttribArray(aid);
    }

    __forceinline void UnsetTexCoordPointer()
    {
        UnsetVertexAttribPointer(A_TEXTURE);
    }

    __forceinline void UnsetColorPointer()
    {
        UnsetVertexAttribPointer(A_COLOR);
    }

    __forceinline void UnsetVertexPointer()
    {
        UnsetVertexAttribPointer(A_POSITION);
    }

    __forceinline void UnsetNormalPointer()
    {
        UnsetVertexAttribPointer(A_NORMAL);
    }

    __forceinline void UnsetWeightPointer(int size)
    {
        UnsetVertexAttribPointer(A_WEIGHT0_3);
        if (size > 3)
        {
            UnsetVertexAttribPointer(A_WEIGHT4_7);
        }
    }

    __forceinline void UnsetVertexAttribPointer(u32 id)
    {
        glDisableVertexAttribArray(m_in[id]);
    }

    __forceinline void SetColor(f32 const *data)
    {
        SetVertexAttrib4fv(A_COLOR, data);
    }

    __forceinline void SetVertexAttrib4fv(u32 id, f32 const *data)
    {
        glVertexAttrib4fv(m_in[id], (GLfloat const *)data);
    }

    __forceinline void DrawPrimitiveArray(u32 type, u32 count)
    {
        static GLuint prim[8] = { POINTS, LINES, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN };

        if (type == 6)
        {
            DrawRectangleArrays(count/4);
        }
        else
        {
            DrawArrays(prim[type], 0, count);
        }
    }

    __forceinline void SetVertexOperations(u32 vflags)
    {
        glUniform1i(m_location[U_VFLAGS], GLint(vflags));
    }

    __forceinline void SetPixelOperations(u32 pflags)
    {
        glUniform1i(m_location[U_PFLAGS], GLint(pflags));
    }

#if 0
    QString CreateVertexShaderSource(ge_VertexInfo &info);
    QString CreatePixelShaderSource(ge_VertexInfo &info);
#endif

private:
    GLint  m_location[64];
    GLint  m_in[8];
    GLint  m_out[1];
    int    m_uniform_changes[64];
    bool   m_linked;
};

/*

Vertex shader :
    - NORMAL/THROUGH MODE      : [tm:1]                                        : 1
    - SKINNING (normal)        : [we:1][wc:3]                                  : 1 + 1 + 3 = 5
    - LIGHTING (normal)        : [le:1]x4[lcomp:2]x4[ltype:2]x4[ssc:1][nrev:1] : 5 + 1x4 + 2x4 + 2x4 + 1 + 1 = 27
    - TEXTURE MAPPING (normal) : [te:1][tmn:2][tmi:2]                          : 27 + 1 + 2 + 2 = 32


Pixel shader :
    - TEXTURE MAPPING (normal) : [txf:3][tcc:1][cd:1]                          : 32 + 3 + 1 + 1 = 37
    - FOGGING                  : [fe:1]                                        : 37 + 1 = 38
    - COLOR TEST               : [ctf:2]                                       : 38 + 2 = 40
    - ALPHA TEST               : [atf:3]                                       : 40 + 3 = 43
    
*/

struct vertex
{
    u32 tt : 2;
    u32 ct : 3;
    u32 nt : 2;
    u32 vt : 2;
    u32 wt : 2;
    u32 it : 2;
    u32 _0 : 1;
    u32 wc : 2;
    u32 _1 : 1;
    u32 mc : 2;
    u32 _2 : 2;
    u32 tm : 1;
    u32 _3 : 8;
};

class gl_ShaderProgramManager : public QCache< u32, gl_ShaderProgram >, private gl_Core
{
public:
    gl_ShaderProgramManager()
    :   QCache< u32, gl_ShaderProgram >(8192)
    {
    }

    gl_ShaderProgram *operator[] (u32 const &key)
    {
        gl_ShaderProgram *program = QCache< u32, gl_ShaderProgram >::operator[](key);
        if (!program)
        {
            program = new gl_ShaderProgram(key);
            this->insert(key, program);
        }

        return program;
    }
};

struct texture
{
    u32 tme : 1; // CMD_TME[0]

    u32 u     : 2; // CMD_SHADE.u           --> 27
    u32 v     : 2; // CMD_SHADE.v           --> 28
};

struct ge_LightState
{
    u32 lte   : 1; // CMD_LTE[0]            --> 1
    u32 le0   : 1; // CMD_LE0[0]            --> 2
    u32 le1   : 1; // CMD_LE1[0]            --> 3
    u32 le2   : 1; // CMD_LE2[0]            --> 4
    u32 le3   : 1; // CMD_LE3[0]            --> 5
    u32 nrev  : 1; // CMD_NREV[0]           --> 6
    u32 ac    : 1; // CMD_MATERIAL.ac       --> 7
    u32 dc    : 1; // CMD_MATERIAL.dc       --> 8
    u32 sc    : 1; // CMD_MATERIAL.sc       --> 9
    u32 ssc   : 1; // CMD_LMODE.ssc         --> 10
    u32 comp0 : 2; // CMD_LYPE0.comp        --> 12
    u32 comp1 : 2; // CMD_LYPE1.comp        --> 14
    u32 comp2 : 2; // CMD_LYPE2.comp        --> 16
    u32 comp3 : 2; // CMD_LYPE3.comp        --> 18
    u32 type0 : 2; // CMD_LYPE0.type        --> 20
    u32 type1 : 2; // CMD_LYPE1.type        --> 22
    u32 type2 : 2; // CMD_LYPE2.type        --> 24
    u32 type3 : 2; // CMD_LYPE3.type        --> 26
    u32 _0    : 6; //                       --> 32
};
#endif // gl_shaderprogram_h__


