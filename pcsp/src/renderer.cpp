
#include "stdafx.h"

#include "emulator.h"
#include "renderer.h"
#include "log.h"
#include "qpspscreen.h"

#include "kernel/kernel_vsync.h"

#include "hle/modules/ge/ge_Context.h"
#include "hle/modules/ge/ge_Types.h"
#include "hle/modules/ge/ge_Constants.h"

//#include <QGLWidget>

#include "opengl/gl_Core.h"
#include "opengl/gl_States.h"
#include "opengl/gl_ShaderProgram.h"
#include "opengl/gl_VertexBufferObject.h"
#include "opengl/gl_FrameBufferObject.h"
#include "opengl/gl_OcclusionQuery.h"

template< typename T > T Min(T x, T y) { return x < y ? x : y; }
template< typename T > T Max(T x, T y) { return x > y ? x : y; }

template< typename T > T Clamp(T x, T v, T y) { return Max(x, Min(v, y)); }

bool use_shaders = false;
static bool last_use_shaders = false;

Renderer	theRenderer;

extern volatile int vsync_limiter;

gl_VertexBufferObject  *theVertexBufferObject = 0;
gl_FrameBufferObject   *theFrameBufferObject  = 0;
gl_OcclusionQuery      *theOcclusionQuery     = 0;

gl_ShaderProgramManager theShaderProgram;

Renderer::Renderer()
:   mInitialized(false)
,   mVertexFlags(0)
,   mPixelFlags(0)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
    if (!mInitialized)
    {
        thePspScreen->makeCurrent();

        gl_Core::Initialize();

        theOcclusionQuery = new gl_OcclusionQuery;

        if (!version_1_5)
        {
            theEmulator.Sc().Critical("OpenGL", "Sorry, at least OpenGL 1.5 is mandatory.");
            theEmulator.Leave();
            return false;
        }

        theVertexBufferObject = new gl_VertexBufferObject;

        //if (!theShaderProgram[0]->Linked() || !theShaderProgram[1]->Linked())
        //{
        //    theEmulator.Sc().Critical("OpenGL", "Sorry, shaders are not linked.");
        //    theEmulator.Leave();
        //    return false;
        //}

        mInitialized = true;

        SaveScreenshot = false;

        Disable(LIGHTING);
        Disable(COLOR_MATERIAL);
        Disable(CULL_FACE);
        Disable(TEXTURE_2D);
        theFogging.Reset();
        theScissorTest.Reset();
        theDepthBoundsTest.Reset();
        theAlphaTest.Reset();
        theStencilTest.Reset();
        theDepthTest.Reset();
        theBlending.Reset();
        theDithering.Reset();
        theLogicalOperation.Reset();
        theLineSmoothing.Reset();

        MatrixMode(MODELVIEW);
        LoadIdentity();
        MatrixMode(PROJECTION);
        LoadIdentity();
        MatrixMode(TEXTURE);
        LoadIdentity();

        glActiveTexture(GL_TEXTURE0);
    }

    return true;
}

void Renderer::Terminate()
{
    if (mInitialized)
    {
        if (theVertexBufferObject)
        {
            delete theVertexBufferObject;
            theVertexBufferObject = 0;
        }

        theShaderProgram.clear();

        if (theOcclusionQuery)
        {
            delete theOcclusionQuery;
            theOcclusionQuery = 0;
        }

        mInitialized = false;
    }

    gl_Core::Terminate();
}

void Renderer::Swap()
{
    thePspScreen->swapBuffers();

    CalcFps();

    //mCurrentFps = KernelVsync::CurrentFps();

    if (SaveScreenshot)
    {
        thePspScreen->SaveScreenshot();
        SaveScreenshot = false;
    }
}

__forceinline bool Renderer::CalcFps()
{
    static Timer fps_timer;

    static u64 last_time;

    static u64 current_time = 0;
    static double time = 0;
    static int	frames_count = 0;

    frames_count++;

    current_time = fps_timer.Get();

    bool set = false;
    if (0 != last_time)
    {
        mLastFrameTime = (float)(current_time - last_time);

        time += (double)mLastFrameTime * (double)0.001f;

        if (time >= 1000.0f)
        {
            mCurrentFps = (float)frames_count;

            time   = 0;
            frames_count = 0;
        }

        if (time >= 500.0f)
            set = true;
    }

    last_time = current_time;

    return set;
}

void Renderer::SetTexture(ge_DecodedTexture *inTexture)
{
    static ge_DecodedTexture *lastTexture = 0;
    static u32 filter[] = { NEAREST, LINEAR, 0, 0, NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR };

    GLuint Texture = *((GLuint *)&inTexture->Resource);
    BindTexture(TEXTURE_2D, Texture);

    if (lastTexture != inTexture)
    {
        lastTexture = inTexture;
        theGeContext.ChangeUniform(U_TDATA);
    }

    TexParameteri(TEXTURE_2D, TEXTURE_WRAP_S,     theGeContext.texture_wrap_mode_s ? CLAMP_TO_EDGE : REPEAT);
    TexParameteri(TEXTURE_2D, TEXTURE_WRAP_T,     theGeContext.texture_wrap_mode_t ? CLAMP_TO_EDGE : REPEAT);
    TexParameteri(TEXTURE_2D, TEXTURE_MAG_FILTER, theGeContext.texture_mag_filter ? LINEAR : NEAREST);
    TexParameteri(TEXTURE_2D, TEXTURE_MIN_FILTER, filter[theGeContext.texture_min_filter]);

    f32 lod_base;
    f32 lod_bias;
    f32 lod_max;

    switch (theGeContext.texture_mipmap_mode)
    {
    case  1:
        lod_base = theGeContext.texture_mipmap_bias;
        lod_bias = 0.0f;
        lod_max  = lod_base;
        break;

    case  2:
        lod_base = logf(fabsf(theGeContext.texture_mipmap_slope/theGeContext.viewport_tz))/logf(2.0f) + theGeContext.texture_mipmap_bias;
        lod_bias = 0.0f;
        lod_max  = Min(lod_base, f32(theGeContext.texture_num_mip_maps));
        break;

    default:
        lod_base = 0;
        lod_bias = theGeContext.texture_mipmap_bias;
        lod_max  = theGeContext.texture_num_mip_maps;
        break;
    }

    TexParameteri(TEXTURE_2D, TEXTURE_MIN_LOD, 0                               );
    TexParameteri(TEXTURE_2D, TEXTURE_MAX_LOD, theGeContext.texture_num_mip_maps);

    TexEnvf(TEXTURE_FILTER_CONTROL, TEXTURE_LOD_BIAS, lod_bias);

    TexParameterf(TEXTURE_2D, GL_TEXTURE_BASE_LEVEL,  Clamp(0.0f, lod_base, lod_max));
    TexParameterf(TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,   Max  (0.0f, lod_max          ));
}

void Renderer::CreateTexture(ge_DecodedTexture *inTexture)
{
    static u32 tpf2tcf[] =
    {
        GL_UNSIGNED_SHORT_5_6_5_REV,
        GL_UNSIGNED_SHORT_1_5_5_5_REV,
        GL_UNSIGNED_SHORT_4_4_4_4_REV,
        GL_UNSIGNED_INT_8_8_8_8_REV,
        GL_UNSIGNED_SHORT_5_6_5_REV,
        GL_UNSIGNED_SHORT_1_5_5_5_REV,
        GL_UNSIGNED_SHORT_4_4_4_4_REV,
        GL_UNSIGNED_INT_8_8_8_8_REV,
        GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
        GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
        GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
    };

    u32 tpf = inTexture->Parameters.texture_storage;
    u32 tcf = tpf2tcf[tpf];

    if (tpf == 0xFFFFFFFF)
    {
        errorf(Renderer, "Error: unsupported texture pixel format (%01X)", tpf);
    }
    else
    {
        GLuint Texture;
        GenTextures(1, &Texture);
        BindTexture(TEXTURE_2D, Texture);

        // opengl does not handle a null texture alignment well.
        if (inTexture->TextureByteAlignment)
        {
            PixelStorei(UNPACK_ALIGNMENT, inTexture->TextureByteAlignment);
        }

        if (tpf >= GE_TFMT_DXT1)
        {
            for (u32 level = 0; level <= inTexture->Parameters.texture_mipmap_max; ++level)
            {
                u32 w   = inTexture->Parameters.texture_width[level];
                u32 h   = inTexture->Parameters.texture_height[level];
                PixelStorei(UNPACK_ROW_LENGTH, inTexture->Parameters.texture_buffer_width[level]);
                CompressedTexImage2D(TEXTURE_2D, level, tcf, w, h, 0, ((w+3)/4)*((h+3)/4)*((tpf == GE_TFMT_DXT1) ? 8 : 16), (GLvoid *)tempTexture[level]);
            }
        }
        else
        {
            if (tpf >= GE_TFMT_CLUT4)
            {
                tcf = tpf2tcf[inTexture->Parameters.texture_clut_mode];
            }

            u32 ipf = (tcf == UNSIGNED_SHORT_5_6_5_REV) ? RGB : RGBA; 
            for (u32 level = 0; level <= inTexture->Parameters.texture_mipmap_max; ++level)
            {
                u32 w   = inTexture->Parameters.texture_width[level];
                u32 h   = inTexture->Parameters.texture_height[level];
                PixelStorei(UNPACK_ROW_LENGTH, inTexture->Parameters.texture_buffer_width[level]);
                TexImage2D(TEXTURE_2D, level, ipf, w, h, 0, ipf, tcf, (GLvoid*)tempTexture[level]);
            }
        }

        PixelStorei(UNPACK_ALIGNMENT,  4);
        PixelStorei(UNPACK_ROW_LENGTH, 0);

        inTexture->Resource = (void *)(GLuint64EXT)Texture;
    }
}

void Renderer::DeleteTexture(ge_DecodedTexture *inTexture)
{
    DeleteTextures(1, (const GLuint *)(&inTexture->Resource));
}

void Renderer::SetMatrix(ge_matrix_type inType, ge_Matrix44*	inMatrix)
{
    switch(inType)
    {
    case SCE_GE_MTXNO_WORLD:
        mWM.DeepCopyFrom(*inMatrix);
        break;
    case SCE_GE_MTXNO_VIEW:
        mVM.DeepCopyFrom(*inMatrix);
        break;
    case SCE_GE_MTXNO_PROJ:
        mPM.DeepCopyFrom(*inMatrix);
        break;
    case SCE_GE_MTXNO_TEXGEN:
        mTM.DeepCopyFrom(*inMatrix);
        break;
    case SCE_GE_MTXNO_BONE0:
    case SCE_GE_MTXNO_BONE1:
    case SCE_GE_MTXNO_BONE2:
    case SCE_GE_MTXNO_BONE3:
    case SCE_GE_MTXNO_BONE4:
    case SCE_GE_MTXNO_BONE5:
    case SCE_GE_MTXNO_BONE6:
    case SCE_GE_MTXNO_BONE7:
        mBM[inType - SCE_GE_MTXNO_BONE0].DeepCopyFrom(*inMatrix);
        break;
    }
}

ge_Matrix44* Renderer::GetMatrix(ge_matrix_type inType)
{
    switch (inType)
    {
    case SCE_GE_MTXNO_WORLD:
        return &mWM;
    case SCE_GE_MTXNO_VIEW:
        return &mVM;
    case SCE_GE_MTXNO_PROJ:
        return &mPM;
    case SCE_GE_MTXNO_TEXGEN:
        return &mTM;
    case SCE_GE_MTXNO_BONE0:
    case SCE_GE_MTXNO_BONE1:
    case SCE_GE_MTXNO_BONE2:
    case SCE_GE_MTXNO_BONE3:
    case SCE_GE_MTXNO_BONE4:
    case SCE_GE_MTXNO_BONE5:
    case SCE_GE_MTXNO_BONE6:
    case SCE_GE_MTXNO_BONE7:
        return &mBM[inType - SCE_GE_MTXNO_BONE0];
    }
    return 0;
}

enum
{
    TEXTURE_NO_MAPPING             = -1,
    TEXTURE_PROJECTION_MAPPING_XYZ = 0,     // (X, Y, Z)
    TEXTURE_PROJECTION_MAPPING_UV0 = 1,     // (U, V, 0)
    TEXTURE_PROJECTION_MAPPING_NN  = 2,     // (Nx/|N|, Ny/|N|, Nz/|N|)
    TEXTURE_PROJECTION_MAPPING_N   = 3,     // (Nx, Ny, Nz)
    TEXTURE_UV_MAPPING             = 4,
    TEXTURE_SHADE_MAPPING          = 5
};

gl_ShaderProgram *gShaderProgram;

#define UNIFORM_CHANGED(location) gShaderProgram->UniformChanges(location) != theGeContext.UniformChanges(location) 
#define UNIFORM_UPDATED(location) gShaderProgram->UniformChanges(location) = theGeContext.UniformChanges(location) 

#define glshUniform1i(location, ...) if (UNIFORM_CHANGED(location)) { glUniform1i(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform1f(location, ...) if (UNIFORM_CHANGED(location)) { glUniform1f(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform2i(location, ...) if (UNIFORM_CHANGED(location)) { glUniform2i(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform2f(location, ...) if (UNIFORM_CHANGED(location)) { glUniform2f(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform3i(location, ...) if (UNIFORM_CHANGED(location)) { glUniform3i(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform3f(location, ...) if (UNIFORM_CHANGED(location)) { glUniform3f(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform4i(location, ...) if (UNIFORM_CHANGED(location)) { glUniform4i(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform4f(location, ...) if (UNIFORM_CHANGED(location)) { glUniform4f(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }

#define glshUniform1iv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform1iv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform1fv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform1fv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform2iv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform2iv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform2fv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform2fv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform3iv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform3iv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform3fv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform3fv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform4iv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform4iv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniform4fv(location, ...) if (UNIFORM_CHANGED(location)) { glUniform4fv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }

#define glshUniformMatrix2fv(location, ...) if (UNIFORM_CHANGED(location)) { glUniformMatrix2fv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniformMatrix3fv(location, ...) if (UNIFORM_CHANGED(location)) { glUniformMatrix3fv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }
#define glshUniformMatrix4fv(location, ...) if (UNIFORM_CHANGED(location)) { glUniformMatrix4fv(gShaderProgram->Location(location), ## __VA_ARGS__); UNIFORM_UPDATED(location); }

template< bool tm, bool cm, bool ce, bool te >
__forceinline void Renderer::PrepareDraw(ge_VertexInfo *inInfo, u32 inType)
{
    static const GLuint tfunc[8] = { NEVER, ALWAYS, EQUAL, NOTEQUAL, LESS, LEQUAL, GREATER, GEQUAL };

    texture_projection_map_mode = TEXTURE_NO_MAPPING;

    mVertexFlags = 0;
    mPixelFlags  = 0;

    Hint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT, tm ? FASTEST : DONT_CARE);
    
    if (USE_SHADERS)
    {
        gShaderProgram->Bind();

        // Model To World Coordinate and World To View Coordinate Transformations
        if (!tm)
        {
            glshUniformMatrix4fv(U_WM,  1, false, (GLfloat const *)(mWM.mData));
            glshUniformMatrix4fv(U_VM,  1, false, (GLfloat const *)(mVM.mData));
        }
    }
    else
    {
        // World to View Coordinate Transformation
        MatrixMode(MODELVIEW);
        if (tm)
        {
            LoadIdentity();
        }
        else
        {
            LoadMatrixf(mVM.mData);
        }
    }

    // Lighting/Shade Mapping
    if (!USE_SHADERS)
    {
        if (tm || !theGeContext.lighting_enable)
        {
            Disable(LIGHTING);
        }
        else
        {
            for (int i = 0; i < 4; i++) 
            {
                GLenum light = GL_LIGHT0 + i;
                if (theGeContext.light_enabled & (1<<i)) 
                {
                    Lightfv(light, POSITION, theGeContext.light_lv[i]);

                    if (theGeContext.light_type[i] == GE_LIGHT_TYPE_SPOT)
                    {
                        float cutoff = 180.0f * acosf(theGeContext.light_lko[i]) / M_PI;
                        Lightf(light, SPOT_CUTOFF,     cutoff);
                        Lightf(light, SPOT_EXPONENT,   theGeContext.light_lks[i]);
                        Lightfv(light, SPOT_DIRECTION, theGeContext.light_ld[i]);	
                    }
                    else
                    {
                        Lightf(light, SPOT_CUTOFF, 180.0f);
                        Lightf(light, SPOT_EXPONENT, 0.0f);
                    }

                    Lightfv(light, AMBIENT, theGeContext.light_lac[i]);
                    Lightfv(light, DIFFUSE, theGeContext.light_ldc[i]);

                    if (theGeContext.light_kind[i] == GE_LIGHT_KIND_DIFFUSE_ONLY) 
                    {
                        static float default_specular[] = { 0.0, 0.0, 0.0, 0.0 };
                        Lightfv(light, SPECULAR, default_specular);
                    }
                    else
                    {
                        Lightfv(light, SPECULAR, theGeContext.light_lsc[i]);
                    }

                    Lightf(light, CONSTANT_ATTENUATION,  theGeContext.light_lka[i][0]);
                    Lightf(light, LINEAR_ATTENUATION,    theGeContext.light_lka[i][1]);
                    Lightf(light, QUADRATIC_ATTENUATION, theGeContext.light_lka[i][2]);

                    Enable(light);
                }
                else
                {
                    Disable(light);
                }
            }
            Enable(LIGHTING);
            Materialf(FRONT_AND_BACK, GL_SHININESS, theGeContext.light_mk);
            LightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, theGeContext.light_mode ? GL_SEPARATE_SPECULAR_COLOR : GL_SINGLE_COLOR);
            LightModelfv(LIGHT_MODEL_AMBIENT, theGeContext.light_ac);
        }
    }
    else if (!tm && theGeContext.lighting_enable)
    {
        mVertexFlags |= gl_ShaderProgram::VS_LIGHTING;

        glshUniform1i(U_LE,            GLint(theGeContext.light_enabled));
        glshUniform1i(U_LMADS,         GLint((theGeContext.material_flags & 7) | (theGeContext.light_mode<<3)));
        glshUniform1f(U_MK,            GLfloat(theGeContext.light_mk));
        glshUniform1f(U_NREV,          theGeContext.reverse_normals ? -1.0f : 1.0f);
        glshUniform4iv(U_LTYPE,     2, (GLint const *)theGeContext.light_type);
        glshUniform4fv(U_LKS,       1, (GLfloat const *)(&theGeContext.light_lks));
        glshUniform4fv(U_LKO,       1, (GLfloat const *)(&theGeContext.light_lko));
        glshUniform4fv(U_AC,        1, (GLfloat const *)(&theGeContext.light_ac));
        glshUniformMatrix4fv(U_LKA, 1, false, (GLfloat const *)(&theGeContext.light_lka));
        glshUniformMatrix4fv(U_LAC, 1, false, (GLfloat const *)(&theGeContext.light_lac));
        glshUniformMatrix4fv(U_LDC, 1, false, (GLfloat const *)(&theGeContext.light_ldc));
        glshUniformMatrix4fv(U_LSC, 1, false, (GLfloat const *)(&theGeContext.light_lsc));
        glshUniformMatrix4fv(U_MC,  1, false, (GLfloat const *)(&theGeContext.material_mac));
        glshUniformMatrix4fv(U_LV,  1, false, (GLfloat const *)(&theGeContext.light_lv));
        glshUniformMatrix4fv(U_LD,  1, false, (GLfloat const *)(&theGeContext.light_ld));
    }

    // View to Clip Coordinate Transformation & Viewport Transformation
#if 1
    {
        // temporary way to set viewport and scissoring as long as we have no FBO nor RBO
        f32 viewport_w =  theGeContext.viewport_sx + theGeContext.viewport_sx;
        f32 viewport_h = -theGeContext.viewport_sy - theGeContext.viewport_sy;
        f32 viewport_x = theGeContext.viewport_tx - theGeContext.offset_x - theGeContext.viewport_sx;
        f32 viewport_y = theGeContext.viewport_ty - theGeContext.offset_y - theGeContext.viewport_sy;
        f32 w          = thePspScreen->width();
        f32 h          = thePspScreen->height();
        f32 ratiox     = w / viewport_w;
        f32 ratioy     = h / viewport_h;
        if (!tm)
        {
            Viewport(GLint(viewport_x * ratiox), GLint((viewport_h - viewport_y) * ratioy), GLint(viewport_w * ratiox), GLint(viewport_h * ratioy));
        }
        else
        {
            Viewport(0, 0, w, h);
        }

        // Scissoring --- doc is controversial :
        // 17.1 - "However, when clear mode is set, scissoring is disabled"
        // 19.6 - "Note that dithering, scissoring, depth mask and plain mask are performed" 
        theScissorTest.enabled = !cm;
        if (!cm)
        {
            s32 scissor_w = 1 + theGeContext.scissor[2] - theGeContext.scissor[0];
            s32 scissor_h = 1 + theGeContext.scissor[3] - theGeContext.scissor[1];
            s32 scissor_x = s32(viewport_x) + theGeContext.scissor[0]; 
            s32 scissor_y = s32(viewport_y) + theGeContext.scissor[1];
            if (scissor_x < 0 || scissor_y < 0 || scissor_w <= 0 || scissor_h <= 0)
            {
                scissor_w = w;
                scissor_h = h;
                scissor_x = 0; 
                scissor_y = 0;
            }
            theScissorTest.area(s32(scissor_x * ratiox), s32((viewport_h - scissor_y) * ratioy), s32(scissor_w * ratiox), s32(scissor_h * ratioy));
        }

        if (tm)
        {
            DepthRange(0.0, 1.0);

            MatrixMode(PROJECTION);
            LoadIdentity();
            Ortho(0.0, viewport_w, viewport_h, 0.0, 0.0, -65535.0);

            if (USE_SHADERS)
            {
                f32 matrix[16];
                GetFloatv(PROJECTION_MATRIX, matrix);
                glshUniformMatrix4fv(U_PM, 1, false, matrix);
            }

            //glOrtho(0.0, w, h, 0.0, 0.0, -65535.0);
        }
        else
        {
            //f32 viewport_width  =  2.0f * theGPUState.viewport_sx;
            //f32 viewport_height = -2.0f * theGPUState.viewport_sy;
            //f32 viewport_x      = theGPUState.viewport_tx - theGPUState.offset_x - theGPUState.viewport_sx;
            //f32 viewport_y      = 272.0f - (theGPUState.viewport_ty - theGPUState.offset_y) + theGPUState.viewport_sy;
            f32 minz            = (theGeContext.viewport_tz - theGeContext.viewport_sz) / 65535.0f;
            f32 maxz            = (theGeContext.viewport_tz + theGeContext.viewport_sz) / 65535.0f;

            DepthRange(minz, maxz);

            if (USE_SHADERS)
            {
                glshUniformMatrix4fv(U_PM, 1, false, (GLfloat const *)(mPM.mData));
            }
            else
            {
                MatrixMode(PROJECTION);
                LoadMatrixf(mPM.mData);
            }
        }
    }
#else
    {
        s32 viewport_w = thePspScreen->width();
        s32 viewport_h = thePspScreen->height();
        f32 w =   theGeContext.viewport_sx + theGeContext.viewport_sx;
        f32 h = - theGeContext.viewport_sy - theGeContext.viewport_sy;
        f32 d =   theGeContext.viewport_sz + theGeContext.viewport_sz;
        f32 viewport_x = ((theGeContext.viewport_tx - theGeContext.viewport_sx - theGeContext.offset_x) * viewport_w) / w;
        f32 viewport_y = ((theGeContext.viewport_ty + theGeContext.viewport_sy - theGeContext.offset_y) * viewport_h) / h;
        f32 viewport_n = (theGeContext.viewport_tz - theGeContext.viewport_sz);
        f32 viewport_f = (theGeContext.viewport_tz + theGeContext.viewport_sz);
        
        glViewport(viewport_x, viewport_y, viewport_w, viewport_h);
        glDepthRange(viewport_n / d, viewport_f / d);

        if (GLEE_NV_depth_clamp)
        {
            if (theGeContext.clipping_enable)
            {
                glEnable(GL_DEPTH_CLAMP_NV);
            }
            else
            {
                glDisable(GL_DEPTH_CLAMP_NV);
            }
        }

        if (tm)
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, w, h, 0.0, 0.0, -65535.0);
        }
        else
        {
            if (USE_SHADERS)
            {
                glshUniformMatrix4fv(U_PM, 1, false, (GLfloat const *)(mPM.mData));
            }
            else
            {
                glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(mPM.mData);
            }
        }
    }
#endif
    // Texture projection
    if (!cm && theGeContext.texture_mapping_enable) // No texture mapping whatever te is set or not
    {
        if (USE_SHADERS)
        {
            glshUniform2i(U_TMAP, theGeContext.texture_mapping_mode, theGeContext.texture_projection_mapping);
            glshUniform3i(U_TFUNC, theGeContext.texture_function.txf, theGeContext.texture_function.tcc, theGeContext.texture_function.cd);
            glshUniform1i(U_TDATA, (GLint)0);
            if (theGeContext.texture_function.txf == 2)
            {
                glshUniform3f(U_TRGB, theGeContext.texture_function.rgba[0], theGeContext.texture_function.rgba[1], theGeContext.texture_function.rgba[2]);
            }
        }
        else
        {
            Disable(TEXTURE_GEN_S);
            Disable(TEXTURE_GEN_T);
        }

        if (tm)
        {
            if (te)
            {
                texture_projection_map_mode = TEXTURE_UV_MAPPING;

                if (USE_SHADERS)
                {
                    mVertexFlags |= gl_ShaderProgram::VS_TEXTURE_MAPPING;
                    mPixelFlags  |= gl_ShaderProgram::PS_TEXTURE_MAPPING;
                    glUniform2f(gShaderProgram->Location(U_TSIZE), 1.0f / theGeContext.texture_width[0], 1.0f / theGeContext.texture_height[0]);
                }
                else
                {
                    MatrixMode(TEXTURE);
                    LoadIdentity();
                    Scalef(1.0f / theGeContext.texture_width[0], 1.0f / theGeContext.texture_height[0], 1.f);
                }

            }
        }
        else
        {
            switch (theGeContext.texture_mapping_mode) 
            {
            case 0: // TMAP_TEXTURE_MAP_MODE_TEXTURE_COORDINATES_UV
                {
                    if (te)
                    {
                        texture_projection_map_mode = TEXTURE_UV_MAPPING;

                        if (USE_SHADERS)
                        {
                            mVertexFlags |= gl_ShaderProgram::VS_TEXTURE_MAPPING;
                            mPixelFlags  |= gl_ShaderProgram::PS_TEXTURE_MAPPING;
                            glshUniform2f(U_TSCALE, theGeContext.texture_scale_u, theGeContext.texture_scale_v);
                            glshUniform2f(U_TTRANS, theGeContext.texture_offset_u, theGeContext.texture_offset_v);
                        }
                        else
                        {
                            MatrixMode(TEXTURE);
                            LoadIdentity();
                            Translatef(theGeContext.texture_offset_u, theGeContext.texture_offset_v, 0.f);
                            Scalef(theGeContext.texture_scale_u, theGeContext.texture_scale_v, 1.f);
                        }

                    }
                }
                break;

            case 1: // TMAP_TEXTURE_MAP_MODE_TEXTURE_MATRIX
                {
                    if (theGeContext.texture_projection_mapping != 1 || te)
                    {
                        texture_projection_map_mode = theGeContext.texture_projection_mapping;

                        if (USE_SHADERS)
                        {
                            mVertexFlags |= gl_ShaderProgram::VS_TEXTURE_MAPPING;
                            mPixelFlags  |= gl_ShaderProgram::PS_TEXTURE_MAPPING;
                            glshUniformMatrix4fv(U_TPROJ, 1, false, (GLfloat const *)(mTM.mData));
                        }
                        else
                        {
                            MatrixMode(TEXTURE);
                            LoadMatrixf(mTM.mData);
                        }

                    }
                }
                break;

            case 2: // TMAP_TEXTURE_MAP_MODE_ENVIRONMENT_MAP
                {
                    texture_projection_map_mode = TEXTURE_SHADE_MAPPING;

                    if (USE_SHADERS)
                    {
                        mVertexFlags |= gl_ShaderProgram::VS_TEXTURE_MAPPING;
                        mPixelFlags  |= gl_ShaderProgram::PS_TEXTURE_MAPPING;
                        glshUniform2iv(U_TSHADE, 1, (GLint const *)&theGeContext.texture_shade);
                        if (!theGeContext.lighting_enable)
                        {
                            glshUniform4iv(U_LTYPE,    2, (GLint const *)theGeContext.light_type);
                            glshUniformMatrix4fv(U_LV, 1, false, (GLfloat const *)(&theGeContext.light_lv));
                        }
                    }
                    else
                    {
                        TexGeni(S, TEXTURE_GEN_MODE, SPHERE_MAP);
                        TexGeni(T, TEXTURE_GEN_MODE, SPHERE_MAP);

                        Enable(TEXTURE_GEN_S);
                        Enable(TEXTURE_GEN_T);

                        for (int i = 0; i < 3; ++i)
                        {
                            theGeContext.texture_matrix[0 + i] = theGeContext.light_lv[theGeContext.texture_shade.u][i];
                            theGeContext.texture_matrix[4 + i] = theGeContext.light_lv[theGeContext.texture_shade.v][i];
                        }

                        MatrixMode(TEXTURE);
                        LoadMatrixf(theGeContext.texture_matrix);
                    }
                }
                break;
            }
        }
    }

    // Model to World Coordinate Transformation
    if (!USE_SHADERS && !tm)
    {
        MatrixMode(MODELVIEW);
        MultMatrixf(mWM.mData);
    }

    // Shading
    ShadeModel(!tm && theGeContext.gouraud_enable ? SMOOTH : FLAT);

    // Material
    if (!USE_SHADERS)
    {
        if (!tm && theGeContext.lighting_enable)
        {
            float alpha = theGeContext.material_mac[3] * theGeContext.light_ac[3];

            alpha = min(max(alpha, 0.0f), 1.0f);

            float material_mdc[4] = { theGeContext.material_mdc[0], theGeContext.material_mdc[1], theGeContext.material_mdc[2], alpha };

            Materialfv(FRONT_AND_BACK, AMBIENT,  theGeContext.material_mac);
            Materialfv(FRONT_AND_BACK, DIFFUSE,               material_mdc);
            Materialfv(FRONT_AND_BACK, SPECULAR, theGeContext.material_msc);
            Materialfv(FRONT_AND_BACK, EMISSION, theGeContext.material_mec);

            if (theGeContext.material_flags)
            {
                switch (theGeContext.material_flags)
                {
                case 1:
                case 5: ColorMaterial(FRONT_AND_BACK, AMBIENT);             alpha = theGeContext.material_mac[3]; break;
                case 2: 
                case 6: ColorMaterial(FRONT_AND_BACK, DIFFUSE);                                                  break;     
                case 3:
                case 7: ColorMaterial(FRONT_AND_BACK, AMBIENT_AND_DIFFUSE);                                      break;
                case 4: ColorMaterial(FRONT_AND_BACK, SPECULAR);            alpha = theGeContext.material_mac[3]; break;
                }

                if (!inInfo->ct)
                {
                    float material_mac[4] = { theGeContext.material_mac[0], theGeContext.material_mac[1], theGeContext.material_mac[2], alpha };
                    Color4fv(material_mac);
                }

                Enable(COLOR_MATERIAL);
            }
            else 
            {
                Disable(COLOR_MATERIAL);
            }
        }
        else
        {
            if (!inInfo->ct)
            {
                Color4fv(theGeContext.material_mac);
            }

            Disable(COLOR_MATERIAL);
        }
    }

    // Patch culling
    if (!tm && theGeContext.patch_culling_enable)
    {
    }

    // Face culling
    if (cm  || !theGeContext.face_culling_enable || u32(inType - GE_PRIM_TRIANGLES) > u32(GE_PRIM_TRIANGLE_FAN - GE_PRIM_TRIANGLES))
    {
        Disable(CULL_FACE);
    }
    else
    {
        Enable(CULL_FACE);
        FrontFace(theGeContext.face_culling_direction ? CW : CCW);
    }

    // Texture mapping
    if (!USE_SHADERS)
    {
        if (cm || !theGeContext.texture_mapping_enable || texture_projection_map_mode == TEXTURE_NO_MAPPING)
        {
            Disable(TEXTURE_2D);
        }
        else
        {
            Enable(TEXTURE_2D);
            theRenderer.SetTexFunc(theGeContext.texture_function.txf, theGeContext.texture_function.tcc, theGeContext.texture_function.cd);
            TexEnvfv(TEXTURE_ENV, TEXTURE_ENV_COLOR, theGeContext.texture_function.rgba);
        }
    }

    // Fogging
    if (cm || tm || !theGeContext.fogging_enable)
    {
        theFogging.enabled = false;
    }
    else
    {
        theFogging.enabled  = true;
        theFogging.mode     = LINEAR;
        theFogging.end      = theGeContext.fog_end;
        theFogging.distance = theGeContext.fog_dist;
        theFogging.color    = theGeContext.fog_color;
    }

    // Color/Alpha test
    if (0 && USE_SHADERS)
    {
#if 1
        if (!cm && (theGeContext.color_test_enable||theGeContext.alpha_test_enable))
        {
            if (theGeContext.color_test_enable)
            {
                mPixelFlags |= gl_ShaderProgram::PS_COLOR_TEST;
            }
            if (theGeContext.alpha_test_enable)
            {
                mPixelFlags |= gl_ShaderProgram::PS_ALPHA_TEST;
            }
            glshUniform2i(U_CTEST, theGeContext.color_test_function, theGeContext.alpha_test_function);
            glshUniform4iv(U_CREF, 1, (GLint const *)theGeContext.color_test_color_ref);
            glshUniform4iv(U_CMSK, 1, (GLint const *)theGeContext.color_test_color_msk);
        }
#else
        bool update = false;
        if (theGeContext.color_test_enable && !cm)
        {
            mPixelFlags |= gl_ShaderProgram::PS_COLOR_TEST;
            update = true;
        }
        if (theGeContext.alpha_test_enable || cm)
        {
            mPixelFlags |= gl_ShaderProgram::PS_ALPHA_TEST;
            update = true;
        }
        if (update)
        {
            glshUniform2i(U_CTEST, theGeContext.color_test_function, cm ? 1 : theGeContext.alpha_test_function);
            if (!cm)
            {
                glshUniform4iv(U_CREF, 1, (GLint const *)theGeContext.color_test_color_ref);
                glshUniform4iv(U_CMSK, 1, (GLint const *)theGeContext.color_test_color_msk);
            }
        }
#endif
    }
    else
    {
        // Alpha test
        theAlphaTest.enabled = cm || theGeContext.alpha_test_enable;
        if (cm || theGeContext.alpha_test_enable)
        {
            theAlphaTest.function(u8(cm ? 1 : theGeContext.alpha_test_function), u8(cm ? 255 : theGeContext.alpha_test_color_ref), 255);
        }
    }

    // Stencil test
    theStencilTest.enabled = !cm && theGeContext.stencil_test_enable;
    if (!cm && theGeContext.stencil_test_enable)
    {
        theStencilTest.function(u8(theGeContext.stencil_test_function), u8(theGeContext.stencil_test_ref), u8(theGeContext.stencil_test_msk));
        theStencilTest.operation(u8(theGeContext.stencil_sfail), u8(theGeContext.stencil_zfail), u8(theGeContext.stencil_zpass));
    }

    // Depth test
    theDepthTest.enabled  = cm || theGeContext.depth_test_enable;
    if (cm || theGeContext.depth_test_enable)
    {
        theDepthTest.function = cm ? 1 : theGeContext.depth_test_function; 
    }

    // Alpha blending
    theBlending.enabled = !cm && theGeContext.alpha_blending_enable;
    if (!cm && theGeContext.alpha_blending_enable)
    {
        theBlending.equation(theGeContext.alpha_blending_a, theGeContext.alpha_blending_b, theGeContext.alpha_blending_equ, theGeContext.alpha_blending_fixa, theGeContext.alpha_blending_fixb);
    }

    // Dithering
    theDithering.enabled = !cm && theGeContext.dithering_enable;

    // Logical operation
    theLogicalOperation.enabled = !cm && theGeContext.logical_operation_enable;
    if (!cm && theGeContext.logical_operation_enable)
    {
        theLogicalOperation.function = theGeContext.logical_operation_function;
    }


    // Masking
    if (cm)
    {
        ColorMask(theGeContext.clear_color_masked, theGeContext.clear_color_masked, theGeContext.clear_color_masked, theGeContext.clear_alpha_masked);
        DepthMask(theGeContext.clear_depth_masked);
    }
    else
    {
        ColorMask(theGeContext.color_mask[0], theGeContext.color_mask[1], theGeContext.color_mask[2], theGeContext.alpha_mask);
        DepthMask(theGeContext.depth_mask);
    }

    // Line anti-aliasing
    theLineSmoothing.enabled = !cm && theGeContext.antialiasing_enable;

    if (USE_SHADERS)
    {
        if (!tm && inInfo->wt)
        {
            mVertexFlags |= gl_ShaderProgram::VS_SKINNING;

            glshUniform1i(U_WC, inInfo->wc);
            glshUniformMatrix4fv(U_BM, inInfo->wc, false, (GLfloat const *)this->mBM);
        }
        else
        {
            mVertexFlags &= ~gl_ShaderProgram::VS_SKINNING;
        }
    }

    theFogging.Apply();
    theScissorTest.Apply();
    theDepthBoundsTest.Apply();
    theAlphaTest.Apply();
    theStencilTest.Apply();
    theDepthTest.Apply();
    theBlending.Apply();
    theLogicalOperation.Apply();
    theDithering.Apply();
    theLineSmoothing.Apply();
}

#define glshVertexAttribPointer(location, ...) theVertexBufferObject[tm]->SetVertexAttribPointer(gShaderProgram->Attribute(location), ## __VA_ARGS__)
#define glshVertexAttrib1fv(location, ...) VertexAttrib1fv(gShaderProgram->Attribute(location), ## __VA_ARGS__)
#define glshVertexAttrib2fv(location, ...) VertexAttrib2fv(gShaderProgram->Attribute(location), ## __VA_ARGS__)
#define glshVertexAttrib3fv(location, ...) VertexAttrib3fv(gShaderProgram->Attribute(location), ## __VA_ARGS__)
#define glshVertexAttrib4fv(location, ...) VertexAttrib4fv(gShaderProgram->Attribute(location), ## __VA_ARGS__)
#define glshEnableVertexAttribArray(location) EnableVertexAttribArray(gShaderProgram->Attribute(location))
#define glshDisableVertexAttribArray(location) theVertexBufferObject[tm]->UnsetVertexAttribPointer(gShaderProgram->Attribute(location))

template< bool tm, bool ce, bool te, bool we, bool ne >
__forceinline void Renderer::Draw(ge_VertexInfo *inInfo, ge_DecodedVertex *inVertices, u32 inType, u32 inCount)
{
    if (USE_SHADERS)
    {
        gShaderProgram->SetVertexOperations(mVertexFlags);
        gShaderProgram->SetPixelOperations(mPixelFlags);

        theVertexBufferObject->Bind(inVertices, inCount*sizeof(ge_DecodedVertex));

        if (tm)
        {
            gShaderProgram->SetVertexPointer(3, GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, v[0]));

            if (ce)
            {
                gShaderProgram->SetColorPointer(4, GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, c[0]));
            }
            else
            {
                gShaderProgram->SetColor(theGeContext.material_mac);
            }

            if (te && theGeContext.texture_mapping_enable)
            {
                gShaderProgram->SetTexCoordPointer(2, GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, t[0]));
            }

            gShaderProgram->DrawPrimitiveArray(inType, inCount);

            gShaderProgram->UnsetVertexPointer();

            if (ce)
            {
                gShaderProgram->UnsetColorPointer();
            }

            if (te && theGeContext.texture_mapping_enable)
            {
                gShaderProgram->UnsetTexCoordPointer();
            }
        }
        else
        {
            gShaderProgram->SetVertexPointer(3, GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, v[0]));

            if (!tm && ne)
            {
                gShaderProgram->SetNormalPointer(GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, n[0]));
            }

            if (te && theGeContext.texture_mapping_enable)
            {
                gShaderProgram->SetTexCoordPointer(2, GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, t[0]));
            }

            if (ce)
            {
                gShaderProgram->SetColorPointer(4, GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, c[0]));
            }
            else
            {
                gShaderProgram->SetColor(theGeContext.material_mac);
            }

            if (!tm && we)
            {
                gShaderProgram->SetWeightPointer(inInfo->wc, GL_FLOAT, sizeof(ge_DecodedVertex), offsetof(ge_DecodedVertex, w[0]), offsetof(ge_DecodedVertex, w[4]));
            }

            gShaderProgram->DrawPrimitiveArray(inType, inCount);

            gShaderProgram->UnsetVertexPointer();

            if (!tm && ne)
            {
                gShaderProgram->UnsetNormalPointer();
            }

            if (te && theGeContext.texture_mapping_enable)
            {
                gShaderProgram->UnsetTexCoordPointer();
            }

            if (ce)
            {
                gShaderProgram->UnsetColorPointer();
            }

            if (!tm && we)
            {
                gShaderProgram->UnsetWeightPointer(inInfo->wc);
            }
        }

        theVertexBufferObject->Unbind();
        gShaderProgram->Unbind();
    }
    else
    {
        struct pspVertex
        {
            float v[3];       
            float n[3];    
            float t[3];        
            float c[4];
        };

        static pspVertex vertex_buffer[65536];

        if (tm)
        {
            for (u32 i = 0; i < inCount; i++)
            {
                // copy info
                memcpy(vertex_buffer[i].v, inVertices[i].v, sizeof(float)*3);

                if (ce)
                {
                    memcpy(vertex_buffer[i].c, inVertices[i].c, sizeof(float)*4);
                }

                if (te)
                {
                    memcpy(vertex_buffer[i].t, inVertices[i].t, sizeof(float)*2);
                }
            }

            theVertexBufferObject->Bind(vertex_buffer, inCount*sizeof(pspVertex));

            theVertexBufferObject->SetVertexPointer(3, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, v[0]));

            if (ce)
            {
                theVertexBufferObject->SetColorPointer(4, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, c[0]));
            }

            if (te && theGeContext.texture_mapping_enable)
            {
                theVertexBufferObject->SetTexCoordPointer(2, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, t[0]));
            }

            theVertexBufferObject->DrawPrimitiveArray(inType, inCount);

            theVertexBufferObject->UnsetVertexPointer();

            if (ce)
            {
                theVertexBufferObject->UnsetColorPointer();
            }

            if (te && theGeContext.texture_mapping_enable)
            {
                theVertexBufferObject->UnsetTexCoordPointer();
            }

            theVertexBufferObject->Unbind();
        }
        else
        {
            for (u32 i = 0; i < inCount; i++)
            {
                // copy info
                if (we)
                {
                    CalcSkinningPosition(vertex_buffer[i].v, inVertices[i]);
                }
                else
                {
                    memcpy(vertex_buffer[i].v, inVertices[i].v, sizeof(float)*3);
                }

                if (ne)
                {
                    if (we)
                    {
                        CalcSkinningNormal(vertex_buffer[i].n, inVertices[i]);
                    }
                    else
                    {
                        memcpy(vertex_buffer[i].n,inVertices[i].n, sizeof(float)*3);
                    }

                    if (theGeContext.reverse_normals)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            vertex_buffer[i].n[j] = -vertex_buffer[i].n[j];
                        }
                    }
                }

                switch (texture_projection_map_mode)
                {
                case TEXTURE_PROJECTION_MAPPING_XYZ: // XYZ coordinates (X, Y, Z)
                    {
                        memcpy(vertex_buffer[i].t, inVertices[i].v, sizeof(float)*3);
                    }
                    break;
                case TEXTURE_PROJECTION_MAPPING_UV0: // texture coordinates (U, V, 0)
                    {
                        memcpy(vertex_buffer[i].t, inVertices[i].t, sizeof(float)*2);
                        vertex_buffer[i].t[2] = 0.0f;
                    }
                    break;
                case TEXTURE_PROJECTION_MAPPING_NN: // Normalized normal coordinates
                    {
                        //glEnable(GL_RESCALE_NORMAL);
                        float s = inVertices[i].n[0]; 
                        float t = inVertices[i].n[1]; 
                        float q = inVertices[i].n[2];
                        float d = sqrtf(s*s + t*t + q*q);
                        float stq[3] = { s/d, t/d, q/d }; 
                        memcpy(vertex_buffer[i].t, stq, sizeof(float)*3);
                    }
                    break;
                case TEXTURE_PROJECTION_MAPPING_N: // Non-normalized normal coordinates
                    {
                        memcpy(vertex_buffer[i].t, inVertices[i].n, sizeof(float)*3);
                    }
                    break;
                case TEXTURE_UV_MAPPING: // texture coordinates (U, V, 1) with UV Scaling/Translation
                    {
                        memcpy(vertex_buffer[i].t, inVertices[i].t, sizeof(float)*2);
                    }
                }

                if (ce)
                {
                    memcpy(vertex_buffer[i].c, inVertices[i].c, sizeof(float)*4);
                }
            }

            //if (ce && theGPUState.lighting_enable && (theGPUState.material_flags & 2))
            //{
            //    f32 aa = theGPUState.light_ac[3];
            //    for (u32 i = 0; i < inCount; i++)
            //    {
            //        f32 alpha = vertex_buffer[i].c[3] * aa;
            //        vertex_buffer[i].c[3] = min(max(alpha, 0.0f), 1.0f);
            //    }
            //}

            theVertexBufferObject->Bind(vertex_buffer, inCount*sizeof(pspVertex));

            theVertexBufferObject->SetVertexPointer(3, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, v[0]));

            if (ce)
            {
                theVertexBufferObject->SetColorPointer(4, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, c[0]));
            }

            if (ne)
            {
                theVertexBufferObject->SetNormalPointer(GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, n[0]));
            }

            if (texture_projection_map_mode == 4)
            {
                theVertexBufferObject->SetTexCoordPointer(2, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, t[0]));
            }
            else if (u32(texture_projection_map_mode) < 4)
            {
                theVertexBufferObject->SetTexCoordPointer(3, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, t[0]));
            }

            theVertexBufferObject->DrawPrimitiveArray(inType, inCount);

            if (texture_projection_map_mode >= 0)
            {
                theVertexBufferObject->UnsetTexCoordPointer();
            }

            if (ne)
            {
                theVertexBufferObject->UnsetNormalPointer();
            }

            if (ce)
            {
                theVertexBufferObject->UnsetColorPointer();
            }

            theVertexBufferObject->UnsetVertexPointer();

            theVertexBufferObject->Unbind();
        }
    }
}

#undef UNIFORM_CHANGED
#undef UNIFORM_UPDATED


void Renderer::SynchronizeShaders(u32 key)
{
    static int last_key = -1;

    if (last_use_shaders)
    {
        glUseProgram(0);
    }

    if (use_shaders != last_use_shaders)
    {
        last_use_shaders = use_shaders;

        //Disable(LIGHT0);
        //Disable(LIGHT1);
        //Disable(LIGHT2);
        //Disable(LIGHT3);
        Disable(LIGHTING);
        Disable(COLOR_MATERIAL);
        Disable(CULL_FACE);
        Disable(TEXTURE_2D);
        theFogging.enabled = false;
        theScissorTest.enabled = false;
        theDepthBoundsTest.enabled = false;
        theAlphaTest.enabled = false;
        theStencilTest.enabled = false;
        theDepthTest.enabled = false;
        theBlending.enabled = false;
        theLogicalOperation.enabled = false;
        theDithering.enabled = false;
        theLineSmoothing.enabled = false;
        Disable(TEXTURE_GEN_S);
        Disable(TEXTURE_GEN_T);

        MatrixMode(MODELVIEW);
        LoadIdentity();
        MatrixMode(PROJECTION);
        LoadIdentity();
        MatrixMode(TEXTURE);
        LoadIdentity();
        glActiveTexture(GL_TEXTURE0);

        last_key = -1;
    }

    if (key != last_key)
    {
        for (int i = 0; i < 64; ++i)
        {
            theGeContext.ChangeUniform(i);
        }
        last_key = key;

        if (last_use_shaders)
        {
            if (gShaderProgram)
            {
                gShaderProgram->Unbind();
            }
            gShaderProgram = theShaderProgram[key];
        }
        else
        {
            gShaderProgram = 0;
        }
    }
}

void Renderer::DrawPrimitives(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inType, u32 inCount, bool inRepeatDraw)
{
    bool cm = theGeContext.clear_mode_enable;
    bool tm = (theGeContext.transform_mode & GE_VTYPE_THROUGH_MASK) != 0;

    bool ce = (theGeContext.transform_mode & GE_VTYPE_COL_MASK)     != 0;
    bool te = (theGeContext.transform_mode & GE_VTYPE_TC_MASK)      != 0;

    if (!inRepeatDraw)
    {
        SynchronizeShaders(theGeContext.transform_mode & (GE_VTYPE_ALL_MASK));

        if (tm) if (cm) if (ce) if (te) PrepareDraw< 1, 1, 1, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 1, 1, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) PrepareDraw< 1, 1, 0, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 1, 1, 0, 0 >(&inInfo, inType);
        /*    */else    if (cm) if (te) PrepareDraw< 1, 0, 1, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 1, 0, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) PrepareDraw< 1, 0, 0, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 1, 0, 0, 0 >(&inInfo, inType);
        else    if (cm) if (ce) if (te) PrepareDraw< 0, 1, 1, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 0, 1, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) PrepareDraw< 0, 1, 0, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 0, 1, 0, 0 >(&inInfo, inType);
        /*    */else    if (cm) if (te) PrepareDraw< 0, 0, 1, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 0, 0, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) PrepareDraw< 0, 0, 0, 1 >(&inInfo, inType);
        /*                    */else    PrepareDraw< 0, 0, 0, 0 >(&inInfo, inType);
    }

    if (tm)
    {
        if (ce) if (te) Draw< 1, 1, 1, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount); 
        /*    */else    Draw< 1, 1, 0, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        else    if (te) Draw< 1, 0, 1, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        /*    */else    Draw< 1, 0, 0, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount);
    }
    else
    {
        bool we = (theGeContext.transform_mode & GE_VTYPE_WEIGHT_MASK)  != 0;
        bool ne = (theGeContext.transform_mode & GE_VTYPE_NRM_MASK)     != 0;

        if (ce) if (te) if (we) if (ne) Draw< 0, 1, 1, 1, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 1, 1, 1, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        /*            */else    if (ne) Draw< 0, 1, 1, 0, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 1, 1, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        /*    */else    if (we) if (ne) Draw< 0, 1, 0, 1, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 1, 0, 1, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        /*            */else    if (ne) Draw< 0, 1, 0, 0, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 1, 0, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        else    if (te) if (we) if (ne) Draw< 0, 0, 1, 1, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 0, 1, 1, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        /*            */else    if (ne) Draw< 0, 0, 1, 0, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 0, 1, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        /*    */else    if (we) if (ne) Draw< 0, 0, 0, 1, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 0, 0, 1, 0 >(&inInfo, outDecodedVertices, inType, inCount);
        /*            */else    if (ne) Draw< 0, 0, 0, 0, 1 >(&inInfo, outDecodedVertices, inType, inCount);
        /*                    */else    Draw< 0, 0, 0, 0, 0 >(&inInfo, outDecodedVertices, inType, inCount);
    }
}

void Renderer::DrawPatches(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inCount, bool inRepeatDraw)
{
    // [hlide]
    // - tm (through_mode)    : I really doubt it is set when calling BEZIER or SPLINE. 3D Vertex positions are needed to generate UV.
    // - cm (clear_mode)      : any reason to take it into account ? clear mode disables texture mapping but we need it for BEZIER/SPLINE
    // - we (morphing_enable) : is it possible ?
    // - ne (normal_enable)   : does BEZIER/SPLINE transform them ?
    // - te (texture_enable)  : always set to 1, because BEZIER/SPLINE generate them.
    // - ce (color_enable)    : any reason not to take them into account ?

    static u32 primitive[4] = { GE_PRIM_TRIANGLE_STRIP, GE_PRIM_LINE_STRIP, GE_PRIM_POINTS };
    u32 type = primitive[theGeContext.patch_primitive];

    bool cm = theGeContext.clear_mode_enable;
    bool tm = (theGeContext.transform_mode & GE_VTYPE_THROUGH_MASK) != 0;

    bool ce = (theGeContext.transform_mode & GE_VTYPE_COL_MASK) != 0;

    if (!inRepeatDraw)
    {
        SynchronizeShaders(GE_VTYPE_TC_FLOAT | (theGeContext.transform_mode & (GE_VTYPE_ALL_MASK)));

        if (tm) if (cm) if (ce) PrepareDraw< 1, 1, 1, 1 >(&inInfo, type);
        /*            */else    PrepareDraw< 1, 1, 0, 1 >(&inInfo, type);
        /*    */else    if (ce) PrepareDraw< 1, 0, 1, 1 >(&inInfo, type);
        /*            */else    PrepareDraw< 1, 0, 0, 1 >(&inInfo, type);
        else    if (cm) if (ce) PrepareDraw< 0, 1, 1, 1 >(&inInfo, type);
        /*            */else    PrepareDraw< 0, 1, 0, 1 >(&inInfo, type);
        /*    */else    if (ce) PrepareDraw< 0, 0, 1, 1 >(&inInfo, type);
        /*            */else    PrepareDraw< 0, 0, 0, 1 >(&inInfo, type);
    }

    if (tm)
    {
        if (ce) Draw< 1, 1, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount); 
        else    Draw< 1, 0, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount);
    }
    else
    {
        bool we = (theGeContext.transform_mode & GE_VTYPE_WEIGHT_MASK) != 0;
        bool ne = (theGeContext.transform_mode & GE_VTYPE_NRM_MASK)    != 0;

        if (ce) if (we) if (ne) Draw< 0, 1, 1, 1, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 1, 1, 1, 0 >(&inInfo, outDecodedVertices, type, inCount);
        /*    */else    if (ne) Draw< 0, 1, 1, 0, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 1, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount);
        else    if (we) if (ne) Draw< 0, 0, 1, 1, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 0, 1, 1, 0 >(&inInfo, outDecodedVertices, type, inCount);
        /*    */else    if (ne) Draw< 0, 0, 1, 0, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 0, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount);
    }
}

static ge_DecodedVertex VertexArray[65536];

void Renderer::DrawArray(ge_VertexInfo &inInfo, u32 inType, u32 inCount, bool inRepeatDraw)
{
    ge_DecodedVertex        *decodedVertices = (ge_DecodedVertex *)VertexArray;
    void                    *vertex_buffer	 = Memory::addr< void >(theGeContext.vertex_address);
    void                    *index_buffer	 = Memory::addr< void >(theGeContext.index_address);
    u32                      count           = inCount;

    if (!inRepeatDraw) theTextureManager.SetTexture();

    theDecoder.DecodeVertices(inInfo, decodedVertices, vertex_buffer, index_buffer, count);

    if (inType == GE_PRIM_RECTANGLES)
    {
        static ge_DecodedVertex QuadArray[2*65536];
        theDecoder.ConvertToQuads(decodedVertices, (ge_DecodedVertex *)QuadArray, count);
        decodedVertices = (ge_DecodedVertex *)QuadArray;
        count *= 2;
    }
    theRenderer.DrawPrimitives(inInfo, decodedVertices, inType, count, inRepeatDraw);

    switch (inInfo.it)
    {
    case 0: theGeContext.vertex_address += inInfo.vertex_size * inCount; break;
    case 1: theGeContext.index_address  += inCount;                     break;
    case 2: theGeContext.index_address  += 2*inCount;                   break;
    }
}

void Renderer::DrawBezier(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, bool inRepeatDraw)
{
    ge_DecodedVertex        *decodedVertices = (ge_DecodedVertex *)VertexArray;
    void                    *vertex_buffer	 = Memory::addr< void >(theGeContext.vertex_address);
    void                    *index_buffer	 = Memory::addr< void >(theGeContext.index_address);
    u32                      count;

    if (!inRepeatDraw) theTextureManager.SetTexture();

    theDecoder.DecodeBezierSurface(inInfo, decodedVertices, count, vertex_buffer, index_buffer, inUCount, inVCount);

    theRenderer.DrawPatches(inInfo, decodedVertices, count, inRepeatDraw);

    switch (inInfo.it)
    {
    case 0: theGeContext.vertex_address += inInfo.vertex_size * inUCount * inVCount; break;
    case 1: theGeContext.index_address  += inUCount * inVCount;                      break;
    case 2: theGeContext.index_address  += 2 * inUCount * inVCount;                  break;
    }
}

void Renderer::DrawSpline(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, u32 inUFlag, u32 inVFlag, bool inRepeatDraw)
{
    ge_DecodedVertex        *decodedVertices = (ge_DecodedVertex *)VertexArray;
    void                    *vertex_buffer	 = Memory::addr< void >(theGeContext.vertex_address);
    void                    *index_buffer	 = Memory::addr< void >(theGeContext.index_address);
    u32                      count;

    if (!inRepeatDraw) theTextureManager.SetTexture();

    theDecoder.DecodeSplineSurface(inInfo, decodedVertices, count, vertex_buffer, index_buffer, inUCount, inVCount, inUFlag, inVFlag);

    theRenderer.DrawPatches(inInfo, decodedVertices, count, inRepeatDraw);

    switch (inInfo.it)
    {
    case 0: theGeContext.vertex_address += inInfo.vertex_size * inUCount * inVCount; break;
    case 1: theGeContext.index_address  += inUCount * inVCount;                      break;
    case 2: theGeContext.index_address  += 2 * inUCount * inVCount;                  break;
    }
}

void Renderer::SetTexFunc(u32 txf, u32 tcc, u32 cd)
{
    int env_mode = MODULATE;
    switch(txf) 
    {
    case 0: env_mode = MODULATE; break;
    case 1: env_mode = DECAL;    break;
    case 2: env_mode = BLEND;    break;
    case 3: env_mode = REPLACE;  break;
    case 4: env_mode = ADD;      break;
    default:
        errorf(Renderer, "Unsupported tfunc mode");
    }

    int rgbScaleParam = cd;
    float rgbScale = 1.0f;
    if (rgbScaleParam == TFUNC_FRAGMENT_DOUBLE_ENABLE_COLOR_DOUBLED) 
    {
        rgbScale = 2.0f;
    } 

    int alphaParam = tcc;
    bool alphaIsOne = false;

    if (alphaParam == TFUNC_FRAGMENT_DOUBLE_TEXTURE_COLOR_ALPHA_IS_IGNORED) 
    {
        alphaIsOne = true;
    }

    if (rgbScale != 1.0f) 
    {
        switch (env_mode)
        {
        case MODULATE:
            // Cv = Ct * Cf
            // Av = At * Af or Av = Af 
            env_mode = GL_COMBINE;
            TexEnvi(TEXTURE_ENV, GL_COMBINE_RGB,  MODULATE);
            TexEnvi(TEXTURE_ENV, GL_SRC0_RGB,     TEXTURE);
            TexEnvi(TEXTURE_ENV, GL_SRC1_RGB,     GL_PREVIOUS);
            TexEnvi(TEXTURE_ENV, GL_OPERAND0_RGB, SRC_COLOR);
            TexEnvi(TEXTURE_ENV, GL_OPERAND1_RGB, SRC_COLOR);

            if (alphaIsOne)
            {
                TexEnvi(TEXTURE_ENV, GL_COMBINE_RGB,  REPLACE);
                TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,   GL_PREVIOUS);
                TexEnvi(TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_ALPHA);
            }
            else
            {
                TexEnvi(TEXTURE_ENV, GL_COMBINE_ALPHA,  MODULATE);
                TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,     TEXTURE);
                TexEnvi(TEXTURE_ENV, GL_SRC1_ALPHA,     GL_PREVIOUS);
                TexEnvi(TEXTURE_ENV, GL_OPERAND0_ALPHA, SRC_ALPHA);
                TexEnvi(TEXTURE_ENV, GL_OPERAND1_ALPHA, SRC_ALPHA);
            }
            break;
        case GL_DECAL:
            env_mode = GL_COMBINE;
            // Cv = Ct * At + Cf * (1 - At) or Cv = Ct
            // Av = Af
            if (alphaIsOne) 
            {
                TexEnvi(TEXTURE_ENV, GL_COMBINE_RGB,  REPLACE);
                TexEnvi(TEXTURE_ENV, GL_SRC0_RGB,     TEXTURE);
                TexEnvi(TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
            } 
            else 
            {
                TexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB,  GL_INTERPOLATE);
                TexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB,     TEXTURE);
                TexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB,     GL_PREVIOUS);
                TexEnvi(GL_TEXTURE_ENV, GL_SRC2_RGB,     TEXTURE);
                TexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, SRC_COLOR);
                TexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, SRC_COLOR);
                TexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_ALPHA);
            }

            TexEnvi(TEXTURE_ENV, GL_COMBINE_ALPHA,  REPLACE);
            TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,     GL_PREVIOUS);
            TexEnvi(TEXTURE_ENV, GL_OPERAND0_ALPHA, SRC_ALPHA);
            break;
        case GL_BLEND:
            // Cv = Cc * Cs + Cp * (1 - Cs)
            // Av = As * Ap
            env_mode = GL_COMBINE;
            TexEnvi(TEXTURE_ENV, GL_COMBINE_RGB,  GL_INTERPOLATE);
            TexEnvi(TEXTURE_ENV, GL_SRC0_RGB,     GL_CONSTANT);
            TexEnvi(TEXTURE_ENV, GL_OPERAND0_RGB, SRC_COLOR);
            TexEnvi(TEXTURE_ENV, GL_SRC1_RGB,     GL_PREVIOUS);
            TexEnvi(TEXTURE_ENV, GL_OPERAND1_RGB, SRC_COLOR);
            TexEnvi(TEXTURE_ENV, GL_SRC2_RGB,     TEXTURE);
            TexEnvi(TEXTURE_ENV, GL_OPERAND2_RGB, SRC_COLOR);

            if (alphaIsOne)
            {
                TexEnvi(TEXTURE_ENV, GL_COMBINE_ALPHA,  REPLACE);
                TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,     GL_PREVIOUS);
                TexEnvi(TEXTURE_ENV, GL_OPERAND0_ALPHA, SRC_ALPHA);
            }
            else
            {
                TexEnvi(TEXTURE_ENV, GL_COMBINE_ALPHA,  MODULATE);
                TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,     TEXTURE);
                TexEnvi(TEXTURE_ENV, GL_SRC1_ALPHA,     GL_PREVIOUS);
                TexEnvi(TEXTURE_ENV, GL_OPERAND0_ALPHA, SRC_ALPHA);
                TexEnvi(TEXTURE_ENV, GL_OPERAND1_ALPHA, SRC_ALPHA);
            }
            break;
        case GL_REPLACE:
            // Cv = Ct
            // Av = At or Av = Af
            env_mode = GL_COMBINE;
            TexEnvi(TEXTURE_ENV, GL_COMBINE_RGB,  REPLACE);
            TexEnvi(TEXTURE_ENV, GL_SRC0_RGB,     TEXTURE);
            TexEnvi(TEXTURE_ENV, GL_OPERAND0_RGB, SRC_COLOR);

            TexEnvi(TEXTURE_ENV, GL_COMBINE_ALPHA,  REPLACE);
            TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,     alphaIsOne ? GL_PREVIOUS : TEXTURE);
            TexEnvi(TEXTURE_ENV, GL_OPERAND0_ALPHA, SRC_ALPHA);
            break;
        case GL_ADD:
            // Cv = Ct + Cf
            // Av = At * Af or Av = Af
            env_mode = GL_COMBINE;
            TexEnvi(TEXTURE_ENV, GL_COMBINE_RGB,  ADD);
            TexEnvi(TEXTURE_ENV, GL_SRC0_RGB,     TEXTURE);
            TexEnvi(TEXTURE_ENV, GL_OPERAND0_RGB, SRC_COLOR);
            TexEnvi(TEXTURE_ENV, GL_SRC1_RGB,     GL_PREVIOUS);
            TexEnvi(TEXTURE_ENV, GL_OPERAND1_RGB, SRC_COLOR);

            if (alphaIsOne)
            {
                TexEnvi(TEXTURE_ENV, GL_COMBINE_ALPHA,  REPLACE);
                TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,     GL_PREVIOUS);
                TexEnvi(TEXTURE_ENV, GL_OPERAND0_ALPHA, SRC_ALPHA);
            }
            else
            {
                TexEnvi(TEXTURE_ENV, GL_COMBINE_ALPHA,  MODULATE);
                TexEnvi(TEXTURE_ENV, GL_SRC0_ALPHA,     TEXTURE);
                TexEnvi(TEXTURE_ENV, GL_SRC1_ALPHA,     GL_PREVIOUS);
                TexEnvi(TEXTURE_ENV, GL_OPERAND0_ALPHA, SRC_ALPHA);
                TexEnvi(TEXTURE_ENV, GL_OPERAND1_ALPHA, SRC_ALPHA);
            }
            break;
        default:
            errorf(Renderer, "Unimplemented sceGuTexFunc RGB doubled for env_mode=%d", env_mode);
            break;
        }
    }
    TexEnvf(TEXTURE_ENV, GL_RGB_SCALE,     rgbScale);
    TexEnvi(TEXTURE_ENV, TEXTURE_ENV_MODE, env_mode);
}

void Renderer::CalcSkinningPosition(float v[3], ge_DecodedVertex& outDecodedVertice)
{
    float x = 0, y = 0, z = 0;
    float* src = outDecodedVertice.v;    
    int weight_count = ((theGeContext.transform_mode >> 14) & 0x7) + 1;

    for (int i = 0; i < weight_count; i++)
    {
        if (outDecodedVertice.w[i] != 0.f)
        {
            ge_Matrix44& matrix = mBM[i];

            x += (	src[0] * matrix.mData[0]
                 + 	src[1] * matrix.mData[4]
                 + 	src[2] * matrix.mData[8]
                 +           matrix.mData[12]) * outDecodedVertice.w[i];

            y += (	src[0] * matrix.mData[1]
                 + 	src[1] * matrix.mData[5]
                 + 	src[2] * matrix.mData[9]
                 +           matrix.mData[13]) * outDecodedVertice.w[i];

            z += (	src[0] * matrix.mData[2]
                 + 	src[1] * matrix.mData[6]
                 + 	src[2] * matrix.mData[10]
                 +           matrix.mData[14]) * outDecodedVertice.w[i];
        }
    }

    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void Renderer::CalcSkinningNormal(float v[3], ge_DecodedVertex& outDecodedVertice)
{
    float x = 0, y = 0, z = 0;
    float* src = outDecodedVertice.n;
    int weight_count = ((theGeContext.transform_mode >> 14) & 0x7) + 1;

    for (int i = 0; i < weight_count; i++)
    {
        if (outDecodedVertice.w[i] != 0.f)
        {
            ge_Matrix44& matrix = mBM[i];

            x += (	src[0] * matrix.mData[0]
                 + 	src[1] * matrix.mData[4]
                 + 	src[2] * matrix.mData[8]) * outDecodedVertice.w[i];

            y += (	src[0] * matrix.mData[1]
                 + 	src[1] * matrix.mData[5]
                 + 	src[2] * matrix.mData[9]) * outDecodedVertice.w[i];

            z += (	src[0] * matrix.mData[2]
                 + 	src[1] * matrix.mData[6]
                 + 	src[2] * matrix.mData[10]) * outDecodedVertice.w[i];
        }
    }

    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void Renderer::SetDrawingRegion(u16 inRegion[4])
{
    double equ[4];
    equ[2] = +0.0;

    equ[0] = +1.0;       equ[1] = +0.0;    equ[3] = inRegion[0] /* left   */;
    ClipPlane(CLIP_PLANE0, equ);

    equ[0] = -1.0;    /* equ[1] = +0.0; */ equ[3] = inRegion[2] /* right  */;
    ClipPlane(CLIP_PLANE2, equ);

    equ[0] = +0.0;       equ[1] = +1.0;    equ[3] = inRegion[1] /* top    */;
    ClipPlane(CLIP_PLANE1, equ);

    /* equ[1] = +0.0; */ equ[1] = -1.0;    equ[3] = inRegion[3] /* bottom */;
    ClipPlane(CLIP_PLANE3, equ);
}

bool Renderer::IsObjectCulled()
{
    // return true if object is culled
    return theOcclusionQuery->IsOccluded();
}

void Renderer::CullObject(ge_VertexInfo &inInfo, u32 inCount)
{
    // [hlide] note that an object is culled if it is not visible inside the drawing region
    //         so the actual implementation is not complete

    if (inInfo.vt == 0) 
    {
        errorf(Renderer, "No positions for vertex!");
        return;
    } 
    else if ((inCount & 7) != 0) 
    {
        errorf(Renderer, "%d is an invalid vertex count!", inCount);
        return;
    }

    static ge_DecodedVertex decoded_vertices[256];

    void *vertex_buffer	= Memory::addr< void >(theGeContext.vertex_address);
    void *index_buffer	= Memory::addr< void >(theGeContext.index_address);

    theDecoder.DecodeVertices(inInfo, (ge_DecodedVertex*)decoded_vertices, vertex_buffer, index_buffer, inCount);

    theOcclusionQuery->BeginBBOX();

    // The bounding box is a cube defined by 8 vertices.
    // It is not clear if the vertices have to be listed in a pre-defined order.
    // Which primitive should be used?
    // - GL_TRIANGLE_STRIP: we only draw 3 faces of the cube
    // - GL_QUADS: how are organized the 8 vertices to draw all the cube faces?

    f32 bboxVertices[8][3];
    for (u32 i = 0; i < inCount; i++) 
    {
        int vertexIndex = i % 8;

        bboxVertices[vertexIndex][0] = decoded_vertices->v[0];
        bboxVertices[vertexIndex][1] = decoded_vertices->v[1];
        bboxVertices[vertexIndex][2] = decoded_vertices->v[2];

        // Cube from BBOX:
        //
        // BBOX Front face:
        //  2---3
        //  |   |
        //  |   |
        //  0---1
        //
        // BBOX Back face:
        //  6---7
        //  |   |
        //  |   |
        //  4---5
        //
        // OpenGL QUAD:
        //  3---2
        //  |   |
        //  |   |
        //  0---1
        //

        if (vertexIndex == 7) 
        {
            theOcclusionQuery->AddBBOX(bboxVertices);
        }
    }

    theOcclusionQuery->EndBBOX();

    switch (inInfo.it)
    {
    case 0: theGeContext.vertex_address += inInfo.vertex_size * inCount; break;
    case 1: theGeContext.index_address  += inCount;                     break;
    case 2: theGeContext.index_address  += 2*inCount;                   break;
    }
}
