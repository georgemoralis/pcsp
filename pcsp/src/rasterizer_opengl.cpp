#include "stdafx.h"

#ifndef USE_SHADERS

#include "emulator.h"
#include "rasterizer.h"
#include "log.h"
#include "qpspscreen.h"

#include "hle/modules/ge/ge_State.h"
#include "hle/modules/ge/ge_Types.h"
#include "hle/modules/ge/ge_Constants.h"

#include <QtOpenGL>

#include "opengl/gl_VertexBufferObject.h"
#include "opengl/gl_OcclusionQuery.h"

Rasterizer	theRasterizer;
DeviceCaps  theRasterizerCaps;

struct pspVertex
{
    float v[3];       
    float n[3];    
    float t[3];        
    float c[4];
};

extern volatile int vsync_limiter;

// Utility functions

void SetSwapInterval(int swap_interval)
{
#ifdef _WIN32
    if (wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(swap_interval);
    }
#endif
}


gl_VertexBufferObject *theVertexBufferObject[2] = { 0, 0 };
gl_OcclusionQuery     *theOcclusionQuery        = 0;

Rasterizer::Rasterizer()
:   mHasVertexBuffer(false)
,   mInitialized(false)
{
}

Rasterizer::~Rasterizer()
{
}

bool Rasterizer::Initialize()
{
    thePspScreen->makeCurrent();

    if (GL_FALSE == GLeeInit())
    {
        return false;
    }

    if (!mInitialized)
    {
        theRasterizerCaps = CheckDeviceCapabilities();

        SetSwapInterval(vsync_limiter);

        if (!theOcclusionQuery)
        {
            theOcclusionQuery = new gl_OcclusionQuery;
        }

        if (theRasterizerCaps.VertexBuffer)
        {
            theVertexBufferObject[0] = new gl_VertexBufferObject;
            theVertexBufferObject[1] = new gl_VertexBufferObject;
            mHasVertexBuffer = true;
        }
        else
        {
            infof(Rasterizer, "Sorry, VBO is mandatory.");
            return false;
        }

        SetSwapInterval(0);

        mInitialized = true;
        SaveScreenshot = false;
    }
    else
    {
        return false;
    }

    return true;
}

void Rasterizer::Terminate()
{
    if (theVertexBufferObject[0])
    {
        delete theVertexBufferObject[0];
        theVertexBufferObject[0] = 0;
    }

    if (theVertexBufferObject[1])
    {
        delete theVertexBufferObject[1];
        theVertexBufferObject[1] = 0;
    }

    if (theOcclusionQuery)
    {
        delete theOcclusionQuery;
        theOcclusionQuery = 0;
    }
}

void Rasterizer::Swap()
{
    static int old_vsync_limiter = -1;
    if (old_vsync_limiter != vsync_limiter)
    {
        SetSwapInterval(old_vsync_limiter = vsync_limiter);        
    }

    thePspScreen->swapBuffers();

    if (SaveScreenshot)
    {
        thePspScreen->SaveScreenshot();
        SaveScreenshot = false;
    }

    CalcFps();
}

__forceinline bool Rasterizer::CalcFps()
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

void Rasterizer::SetTexture(ge_DecodedTexture *inTexture)
{
    static u32 filter[] = { GL_NEAREST, GL_LINEAR, 0, 0, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR };

    GLuint Texture = (GLuint)(long long)inTexture->Resource;
    glBindTexture(GL_TEXTURE_2D, Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     theGPUState.texture_wrap_mode_s ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     theGPUState.texture_wrap_mode_t ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, theGPUState.texture_mag_filter ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter[theGPUState.texture_min_filter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,  theGPUState.texture_num_mip_maps);
}

void Rasterizer::CreateTexture(ge_DecodedTexture* inTexture)
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

    static u32 tpf2cpf[] =
    {
        GL_COLOR_INDEX4_EXT,
        GL_COLOR_INDEX8_EXT,
        GL_COLOR_INDEX16_EXT,
        GL_COLOR_INDEX,
    };

    u32 tpf = inTexture->Parameters.texture_storage;
    u32 tcf = tpf2tcf[tpf];

    if (tpf == 0xFFFFFFFF)
    {
        errorf(Rasterizer, "Error: unsupported texture pixel format (%01X)", tpf);
    }
    else
    {
        GLuint Texture;
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        // opengl does not handle a null texture alignment well.
        if (inTexture->TextureByteAlignment)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, inTexture->TextureByteAlignment);
        }

        if (tpf >= GE_TFMT_DXT1)
        {
            int bs = (tpf == GE_TFMT_DXT1) ? 8 : 16;
            for (u32 level = 0; level <= inTexture->Parameters.texture_mipmap_max; ++level)
            {
                int w   = inTexture->Parameters.texture_width[level];
                int h   = inTexture->Parameters.texture_height[level];
                int cts = ((w+3)/4)*((h+3)/4)*bs;
                glPixelStorei(GL_UNPACK_ROW_LENGTH, inTexture->Parameters.texture_buffer_width[level]);
                glCompressedTexImage2D(GL_TEXTURE_2D, level, tcf, w, h, 0, cts, (GLvoid*)tempTexture[level]);
            }
        }
        else
        {
            if (tpf >= GE_TFMT_CLUT4)
            {
                tcf = tpf2tcf[inTexture->Parameters.texture_clut_mode];
            }

            u32 ipf = (tcf == GL_UNSIGNED_SHORT_5_6_5_REV) ? GL_RGB : GL_RGBA; 
            for (u32 level = 0; level <= inTexture->Parameters.texture_mipmap_max; ++level)
            {
                glPixelStorei(GL_UNPACK_ROW_LENGTH, inTexture->Parameters.texture_buffer_width[level]);
                glTexImage2D(GL_TEXTURE_2D, level, ipf, (inTexture->Parameters.texture_width[level]), (inTexture->Parameters.texture_height[level]), 0, ipf, tcf, (GLvoid*)tempTexture[level]);
            }
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT,  4);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

        inTexture->Resource = (void*)Texture;
    }
}

void Rasterizer::DeleteTexture(void* inResource)
{
    glDeleteTextures(1, (const GLuint *)inResource);
}

DeviceCaps	Rasterizer::CheckDeviceCapabilities()
{
    DeviceCaps	caps;

    if (GLEE_ARB_framebuffer_object) {
        caps.RenderTarget = true;
    } else {
        caps.RenderTarget = false;
    }

    if(glGenBuffersARB && glBindBufferARB && glBufferDataARB && glBufferSubDataARB && glMapBufferARB && glUnmapBufferARB && glDeleteBuffersARB && glGetBufferParameterivARB) {
        caps.VertexBuffer = true;
    } else {
        caps.VertexBuffer = false;
    }

    if (!caps.VertexBuffer) {
        infof(Rasterizer,"WARNING: Running in software vertex processing!");
    }

    if (GL_VERSION_1_5) {
        infof(Rasterizer,"Vertex mode: post 1.5");
    } else {
        infof(Rasterizer,"Vertex mode: ARB pre 1.5");
    }
    return caps;
}

void Rasterizer::SetMatrix(ge_matrix_type inType, ge_Matrix44*	inMatrix)
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

ge_Matrix44* Rasterizer::GetMatrix(ge_matrix_type inType)
{
   switch(inType)
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
    TEXTURE_NO_MAPPING             = -2,
    TEXTURE_SHADE_MAPPING          = -1,
    TEXTURE_PROJECTION_MAPPING_XYZ = 0,     // (X, Y, Z)
    TEXTURE_PROJECTION_MAPPING_UV0 = 1,     // (U, V, 0)
    TEXTURE_PROJECTION_MAPPING_NN  = 2,     // (Nx/|N|, Ny/|N|, Nz/|N|)
    TEXTURE_PROJECTION_MAPPING_N   = 3,     // (Nx, Ny, Nz)
    TEXTURE_UV_MAPPING             = 4,
};

template< bool tm, bool cm, bool ce, bool te >
__forceinline void Rasterizer::BeginDraw(ge_VertexInfo *inInfo, u32 inType)
{
    static const GLuint tfunc[8] = { GL_NEVER, GL_ALWAYS, GL_EQUAL, GL_NOTEQUAL, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL };

    texture_projection_map_mode = TEXTURE_NO_MAPPING;

    // World to View Coordinate Transformation
    glMatrixMode(GL_MODELVIEW);
    if (tm)
    {
        glLoadIdentity();
    }
    else
    {
        glLoadMatrixf(mVM.mData);
    }

    // Lighting
    if (tm || !theGPUState.lighting_enable)
    {
        glDisable(GL_LIGHTING);
    }
    else
    {
        int lights = 0;
        for (int i = 0; i < 4; i++) 
        {
            if (theGPUState.light_enabled & (1<<i)) 
            {
                lights++;

                glLightfv(GL_LIGHT0 + i, GL_POSITION,       theGPUState.light_lv[i]);

                if (theGPUState.light_type[i] == LIGHT_SPOT)
                {
                    float cutoff = 180.0f * acosf(theGPUState.light_lko[i]) / M_PI_2;
                    glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF,     cutoff);
                    glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT,   theGPUState.light_lks[i]);
                    glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, theGPUState.light_ld[i]);	
                }
                else
                {
                    glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180.0f);
                    glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, 0.0f);
                }

                if (theGPUState.light_kind[i] == LIGHT_DIFFUSE_ONLY) 
                {
                    static float default_specular[] = { 0.0, 0.0, 0.0, 1.0 };
                    glLightfv(GL_LIGHT0 + i, GL_SPECULAR, default_specular);
                }
                else
                {
                    glLightfv(GL_LIGHT0 + i, GL_SPECULAR, theGPUState.light_lsc[i]);
                }
            }	
        }
        if (lights)
        {
            glEnable(GL_LIGHTING);
        }
        else
        {
            glDisable(GL_LIGHTING);
        }
    }

    // Model to World Coordinate Transformation
    if (!tm)
    {
        glMultMatrixf(mWM.mData);
    }

    // View to Clip Coordinate Transformation & Viewport Transformation
    glMatrixMode(GL_PROJECTION);
    if (tm)
    {
        glLoadIdentity();

        glViewport(0, 0, thePspScreen->width(), thePspScreen->height());
        glDepthRange(0.0, 1.0);

        glOrtho(0, 480, 272, 0, 0, -0xFFFF);
    }
    else
    {
        f32 viewport_width  = theGPUState.viewport_width;
        f32 viewport_height = theGPUState.viewport_height;
        f32 viewport_x      = theGPUState.viewport_cx - theGPUState.offset_x - viewport_width / 2.0f;
        f32 viewport_y      = 272.0f - (theGPUState.viewport_cy - theGPUState.offset_y) - viewport_height / 2.0f;
        f32 ratiox          = thePspScreen->width() / 480.0f;
        f32 ratioy          = thePspScreen->height() / 272.0f;
        f32 minz            = theGPUState.minz;
        f32 maxz            = theGPUState.maxz;
        f32 offset          = 0; //theGPUState.zpos - (minz + maxz) / 2;
        minz                = theGPUState.zpos - theGPUState.zscale - offset;
        maxz                = theGPUState.zpos + theGPUState.zscale - offset;

        //if (viewport_x == 0 && viewport_y == 0 && viewport_height == 0 && viewport_width == 0)
        //{
        //    viewport_x      = 2048 - theGPUState.offset_x - 480 / 2;
        //    viewport_y      = 272 - (2048 - theGPUState.offset_y) - 272 / 2;
        //    viewport_width  = thePspScreen->width();
        //    viewport_height = thePspScreen->height();
        //}

        glViewport(GLint(viewport_x * ratiox), GLint(viewport_y * ratioy), GLsizei(viewport_width * ratiox), GLsizei(viewport_height * ratioy));
        glDepthRange(minz, maxz);

        glLoadMatrixf(mPM.mData);
    }

    // Texture projection
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    if (!cm && theGPUState.texture_mapping_enable) // No texture mapping whatever te is set or not
    {
        if (tm)
        {
            if (te)
            {
                glScalef(1.0f / theGPUState.texture_width[0], 1.0f / theGPUState.texture_height[0], 1.f);
                texture_projection_map_mode = TEXTURE_UV_MAPPING;
            }
        }
        else
        {
            switch (theGPUState.texture_mapping_mode) 
            {
            case 0: // TMAP_TEXTURE_MAP_MODE_TEXTURE_COORDINATES_UV
                {
                    if (te)
                    {
                        texture_projection_map_mode = TEXTURE_UV_MAPPING;
                        glTranslatef(theGPUState.texture_offset_u, theGPUState.texture_offset_v, 0.f);
                        glScalef(theGPUState.texture_scale_u, theGPUState.texture_scale_v, 1.f);
                    }
                }
                break;

            case 1: // TMAP_TEXTURE_MAP_MODE_TEXTURE_MATRIX
                {
                    if (theGPUState.texture_projection_mapping != 1 || te)
                    {
                        texture_projection_map_mode = theGPUState.texture_projection_mapping;

                        glMultMatrixf(mTM.mData);
                    }
                }
                break;

            case 2: // TMAP_TEXTURE_MAP_MODE_ENVIRONMENT_MAP
                {
                    texture_projection_map_mode = TEXTURE_SHADE_MAPPING;

                    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

                    glEnable(GL_TEXTURE_GEN_S);
                    glEnable(GL_TEXTURE_GEN_T);

                    for (int i = 0; i < 3; i++)
                    {
                        theGPUState.texture_matrix[0] = theGPUState.light_lv[theGPUState.texture_shade.u][i];
                        theGPUState.texture_matrix[4] = theGPUState.light_lv[theGPUState.texture_shade.v][i];
                    }

                    glMultMatrixf(theGPUState.texture_matrix);
                }
                break;
            }
        }
    }

    // Shading

    // Material
    if (!inInfo->ct)
    {
        glColor4fv(theGPUState.material_mac);
    }
    glMaterialfv(GL_FRONT, GL_AMBIENT,  theGPUState.material_mac);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  theGPUState.material_mdc);
    glMaterialfv(GL_FRONT, GL_SPECULAR, theGPUState.material_msc);
    if (!tm && theGPUState.lighting_enable && theGPUState.light_enabled && theGPUState.material_flags)
    {
        switch (theGPUState.material_flags)
        {
        case 1:
        case 5: glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);             break;
        case 2: 
        case 6: glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);             break;     
        case 3:
        case 7: glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); break;
        case 4: glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);            break;
        }

        glEnable(GL_COLOR_MATERIAL);
    }
    else 
    {
        glDisable(GL_COLOR_MATERIAL);
    }

    // Face culling
    if (cm || inType == GE_PRIM_RECTANGLES || !theGPUState.face_culling_enable)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
    }

    // Texture mapping
    if (cm || !theGPUState.texture_mapping_enable || (!tm ? (texture_projection_map_mode < TEXTURE_SHADE_MAPPING) : false))
    {
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        theRasterizer.SetTexFunc(theGPUState.texture_function.txf, theGPUState.texture_function.tcc, theGPUState.texture_function.cd);
        glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, theGPUState.texture_function.rgba);
    }

    // Fogging
    if (cm || tm || !theGPUState.fogging_enable)
    {
        glDisable(GL_FOG);
    }
    else
    {
        float ze = theGPUState.fog_far;
        float zs = ze - (theGPUState.fog_dist != 0.0f) ? (1.0f / theGPUState.fog_dist) : 0.0f;
        glFogi(GL_FOG_MODE, GL_LINEAR);
        glFogf(GL_FOG_START, zs);
        glFogf(GL_FOG_END,   ze);
        glEnable(GL_FOG);
    }

    // Scissoring
    if (cm)
    {
        glDisable(GL_SCISSOR_TEST);
    }
    else
    {
        glEnable(GL_SCISSOR_TEST);
        UpdateScissoringArea();
    }

    // Alpha test
    if (!cm && theGPUState.alpha_test_enable)
    {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(tfunc[theGPUState.alpha_test_function], theGPUState.alpha_test_color_ref);
    }
    else if (cm)
    {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_ALWAYS, 1.0f);
    }
    else
    {
        glDisable(GL_ALPHA_TEST);
    }

    // Stencil test
    if (cm || !theGPUState.stencil_test_enable)
    {
        glDisable(GL_STENCIL_TEST);
    }
    else
    {
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(theGPUState.stencil_test_function, theGPUState.stencil_test_ref, theGPUState.stencil_test_msk);
        glStencilOp(theGPUState.stencil_sfail, theGPUState.stencil_zfail, theGPUState.stencil_zpass);
    }

    // Depth test
    if (!cm && theGPUState.depth_test_enable)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(tfunc[theGPUState.depth_test_function]);
    }
    else if (cm)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    // Alpha blending
    if (cm || !theGPUState.alpha_blending_enable)
    {
        glDisable(GL_BLEND);
    }
    else
    {
        glEnable(GL_BLEND);
        theRasterizer.SetAlphaBlending(theGPUState.alpha_blending_a, theGPUState.alpha_blending_b, theGPUState.alpha_blending_equ);
    }

    // Dithering
    if (cm || !theGPUState.dithering_enable)
    {
        glDisable(GL_DITHER);
    }
    else
    {
        glEnable(GL_DITHER);
    }

    // Logical operation
    if (cm || !theGPUState.logical_operation_enable)
    {
        glDisable(GL_COLOR_LOGIC_OP);
    }
    else
    {
        glEnable(GL_COLOR_LOGIC_OP);
    }

    // Masking
    if (cm)
    {
        glColorMask(theGPUState.clear_color_masked, theGPUState.clear_color_masked, theGPUState.clear_color_masked, theGPUState.clear_alpha_masked);
        glDepthMask(theGPUState.clear_depth_masked);
    }
    else
    {
        glColorMask(theGPUState.color_mask[0], theGPUState.color_mask[1], theGPUState.color_mask[2], theGPUState.alpha_mask);
        glDepthMask(theGPUState.depth_mask);
    }

    // Line anti-aliasing
    if (cm || !theGPUState.antialiasing_enable)
    {
        glDisable(GL_LINE_SMOOTH);
    }
    else
    {
        glEnable(GL_LINE_SMOOTH);
    }
}

template< bool tm, bool ce, bool te, bool we, bool ne >
__forceinline void Rasterizer::Draw(ge_VertexInfo *inInfo, ge_DecodedVertex *outDecodedVertices, u32 inType, u32 inCount)
{
    GLuint prim[8] = { GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS };

    static pspVertex vertex_buffer[65536];

    if (tm)
    {
        for (u32 i = 0; i < inCount; i++)
        {
            // copy info
            memcpy(vertex_buffer[i].v, outDecodedVertices[i].v, sizeof(float)*3);

            if (ce)
            {
                memcpy(vertex_buffer[i].c, outDecodedVertices[i].c, sizeof(float)*4);
            }

            if (te)
            {
                memcpy(vertex_buffer[i].t, outDecodedVertices[i].t, sizeof(float)*2);
            }
        }

        theVertexBufferObject[tm]->Bind(vertex_buffer, inCount*sizeof(pspVertex));

        theVertexBufferObject[tm]->SetVertexPointer(3, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, v[0]));

        if (ce)
        {
            theVertexBufferObject[tm]->SetColorPointer(4, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, c[0]));
        }

        if (te && theGPUState.texture_mapping_enable)
        {
            theVertexBufferObject[tm]->SetTexCoordPointer(2, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, t[0]));
        }

        glDrawArrays(prim[inType], 0, inCount);

        theVertexBufferObject[tm]->UnsetVertexPointer();
 
        if (ce)
        {
            theVertexBufferObject[tm]->UnsetColorPointer();
        }

        if (te && theGPUState.texture_mapping_enable)
        {
            theVertexBufferObject[tm]->UnsetTexCoordPointer();
        }
    }
    else
    {
        for (u32 i = 0; i < inCount; i++)
        {
            // copy info
            if (we)
            {
                CalcSkinningPosition(vertex_buffer[i].v, outDecodedVertices[i]);
            }
            else
            {
                memcpy(vertex_buffer[i].v, outDecodedVertices[i].v, sizeof(float)*3);
            }

            if (ne)
            {
                if (we)
                {
                    CalcSkinningNormal(vertex_buffer[i].n, outDecodedVertices[i]);
                }
                else
                {
                    memcpy(vertex_buffer[i].n,outDecodedVertices[i].n, sizeof(float)*3);
                }

                if (theGPUState.reverse_normals)
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
                    memcpy(vertex_buffer[i].t, outDecodedVertices[i].v, sizeof(float)*3);
                }
                break;
            case TEXTURE_PROJECTION_MAPPING_UV0: // texture coordinates (U, V, 0)
                {
                    memcpy(vertex_buffer[i].t, outDecodedVertices[i].t, sizeof(float)*2);
                    vertex_buffer[i].t[2] = 0.0f;
                }
                break;
            case TEXTURE_PROJECTION_MAPPING_NN: // Normalized normal coordinates
                {
                    //glEnable(GL_RESCALE_NORMAL);
                    float s = outDecodedVertices[i].n[0]; 
                    float t = outDecodedVertices[i].n[1]; 
                    float q = outDecodedVertices[i].n[2];
                    float d = sqrtf(s*s + t*t + q*q);
                    float stq[3] = { s/d, t/d, q/d }; 
                    memcpy(vertex_buffer[i].t, stq, sizeof(float)*3);
                }
                break;
            case TEXTURE_PROJECTION_MAPPING_N: // Non-normalized normal coordinates
                {
                    memcpy(vertex_buffer[i].t, outDecodedVertices[i].n, sizeof(float)*3);
                }
                break;
            case TEXTURE_UV_MAPPING: // texture coordinates (U, V, 1) with UV Scaling/Translation
                {
                    memcpy(vertex_buffer[i].t, outDecodedVertices[i].t, sizeof(float)*2);
                }
            }

            if (ce)
            {
                memcpy(vertex_buffer[i].c, outDecodedVertices[i].c, sizeof(float)*4);
            }
        }

        theVertexBufferObject[tm]->Bind(vertex_buffer, inCount*sizeof(pspVertex));

        theVertexBufferObject[tm]->SetVertexPointer(3, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, v[0]));

        if (ce)
        {
            theVertexBufferObject[tm]->SetColorPointer(4, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, c[0]));
        }

        if (ne)
        {
            theVertexBufferObject[tm]->SetNormalPointer(GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, n[0]));
        }

        if (texture_projection_map_mode >= 0)
        {
            theVertexBufferObject[tm]->SetTexCoordPointer((texture_projection_map_mode == 4) ? 2 : 3, GL_FLOAT, sizeof(pspVertex), offsetof(pspVertex, t[0]));
        }

        glDrawArrays(prim[inType], 0, inCount);

        if (texture_projection_map_mode >= 0)
        {
            theVertexBufferObject[tm]->UnsetTexCoordPointer();
        }

        if (ne)
        {
            theVertexBufferObject[tm]->UnsetNormalPointer();
        }

        if (ce)
        {
            theVertexBufferObject[tm]->UnsetColorPointer();
        }

        //glDisable(GL_CULL_FACE);
        //glColor4f(1.0f, 0.25f, 0.25f, 0.75f);
        //glDrawArrays(GL_LINES, 0, inCount);

        theVertexBufferObject[tm]->UnsetVertexPointer();
    }
}

template< bool tm, bool cm, bool ce, bool te >
__forceinline void Rasterizer::EndDraw(ge_VertexInfo *inInfo, u32 inType)
{
}

void Rasterizer::DrawPrimitives(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inType, u32 inCount, bool inRepeatDraw)
{
    bool cm = theGPUState.clear_mode_enable;
    bool tm = (theGPUState.transform_mode & GE_VTYPE_THROUGH_MASK) != 0;

    bool ce = (theGPUState.transform_mode & GE_VTYPE_COL_MASK) != 0;
    bool te = (theGPUState.transform_mode & GE_VTYPE_TC_MASK)  != 0;

    if (!inRepeatDraw)
    {
        if (tm) if (cm) if (ce) if (te) BeginDraw< 1, 1, 1, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 1, 1, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) BeginDraw< 1, 1, 0, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 1, 1, 0, 0 >(&inInfo, inType);
        /*    */else    if (cm) if (te) BeginDraw< 1, 0, 1, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 1, 0, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) BeginDraw< 1, 0, 0, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 1, 0, 0, 0 >(&inInfo, inType);
        else    if (cm) if (ce) if (te) BeginDraw< 0, 1, 1, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 0, 1, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) BeginDraw< 0, 1, 0, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 0, 1, 0, 0 >(&inInfo, inType);
        /*    */else    if (cm) if (te) BeginDraw< 0, 0, 1, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 0, 0, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) BeginDraw< 0, 0, 0, 1 >(&inInfo, inType);
        /*                    */else    BeginDraw< 0, 0, 0, 0 >(&inInfo, inType);
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
        bool we = (theGPUState.transform_mode & GE_VTYPE_WEIGHT_MASK) != 0;
        bool ne = (theGPUState.transform_mode & GE_VTYPE_NRM_MASK)    != 0;

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

    if (!inRepeatDraw)
    {
        if (tm) if (cm) if (ce) if (te) EndDraw< 1, 1, 1, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 1, 1, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) EndDraw< 1, 1, 0, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 1, 1, 0, 0 >(&inInfo, inType);
        /*    */else    if (cm) if (te) EndDraw< 1, 0, 1, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 1, 0, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) EndDraw< 1, 0, 0, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 1, 0, 0, 0 >(&inInfo, inType);
        else    if (cm) if (ce) if (te) EndDraw< 0, 1, 1, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 0, 1, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) EndDraw< 0, 1, 0, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 0, 1, 0, 0 >(&inInfo, inType);
        /*    */else    if (cm) if (te) EndDraw< 0, 0, 1, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 0, 0, 1, 0 >(&inInfo, inType);
        /*            */else    if (te) EndDraw< 0, 0, 0, 1 >(&inInfo, inType);
        /*                    */else    EndDraw< 0, 0, 0, 0 >(&inInfo, inType);
    }
}

void Rasterizer::DrawPatches(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inCount, bool inRepeatDraw)
{
    // [hlide]
    // - tm (through_mode)    : I really doubt it is set when calling BEZIER or SPLINE. 3D Vertex positions are needed to generate UV.
    // - cm (clear_mode)      : any reason to take it into account ? clear mode disables texture mapping but we need it for BEZIER/SPLINE
    // - we (morphing_enable) : is it possible ?
    // - ne (normal_enable)   : does BEZIER/SPLINE transform them ?
    // - te (texture_enable)  : always set to 1, because BEZIER/SPLINE generate them.
    // - ce (color_enable)    : any reason not to take them into account ?

    static u32 primitive[4] = { GE_PRIM_TRIANGLE_STRIP, GE_PRIM_LINE_STRIP, GE_PRIM_POINTS };
    u32 type = primitive[theGPUState.patch_primitive];

    bool cm = theGPUState.clear_mode_enable;
    bool tm = (theGPUState.transform_mode & GE_VTYPE_THROUGH_MASK) != 0;

    bool ce = (theGPUState.transform_mode & GE_VTYPE_COL_MASK) != 0;

    if (!inRepeatDraw)
    {
        if (tm) if (cm) if (ce) BeginDraw< 1, 1, 1, 1 >(&inInfo, type);
        /*            */else    BeginDraw< 1, 1, 0, 1 >(&inInfo, type);
        /*    */else    if (ce) BeginDraw< 1, 0, 1, 1 >(&inInfo, type);
        /*            */else    BeginDraw< 1, 0, 0, 1 >(&inInfo, type);
        else    if (cm) if (ce) BeginDraw< 0, 1, 1, 1 >(&inInfo, type);
        /*            */else    BeginDraw< 0, 1, 0, 1 >(&inInfo, type);
        /*    */else    if (ce) BeginDraw< 0, 0, 1, 1 >(&inInfo, type);
        /*            */else    BeginDraw< 0, 0, 0, 1 >(&inInfo, type);
    }

    if (tm)
    {
        if (ce) Draw< 1, 1, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount); 
        else    Draw< 1, 0, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount);
    }
    else
    {
        bool we = (theGPUState.transform_mode & GE_VTYPE_WEIGHT_MASK) != 0;
        bool ne = (theGPUState.transform_mode & GE_VTYPE_NRM_MASK)    != 0;

        if (ce) if (we) if (ne) Draw< 0, 1, 1, 1, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 1, 1, 1, 0 >(&inInfo, outDecodedVertices, type, inCount);
        /*    */else    if (ne) Draw< 0, 1, 1, 0, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 1, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount);
        else    if (we) if (ne) Draw< 0, 0, 1, 1, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 0, 1, 1, 0 >(&inInfo, outDecodedVertices, type, inCount);
        /*    */else    if (ne) Draw< 0, 0, 1, 0, 1 >(&inInfo, outDecodedVertices, type, inCount);
        /*            */else    Draw< 0, 0, 1, 0, 0 >(&inInfo, outDecodedVertices, type, inCount);
    }

    if (!inRepeatDraw)
    {
        if (tm) if (cm) if (ce) EndDraw< 1, 1, 1, 1 >(&inInfo, type);
        /*            */else    EndDraw< 1, 1, 0, 1 >(&inInfo, type);
        /*    */else    if (ce) EndDraw< 1, 0, 1, 1 >(&inInfo, type);
        /*            */else    EndDraw< 1, 0, 0, 1 >(&inInfo, type);
        else    if (cm) if (ce) EndDraw< 0, 1, 1, 1 >(&inInfo, type);
        /*            */else    EndDraw< 0, 1, 0, 1 >(&inInfo, type);
        /*    */else    if (ce) EndDraw< 0, 0, 1, 1 >(&inInfo, type);
        /*            */else    EndDraw< 0, 0, 0, 1 >(&inInfo, type);
    }
}

static ge_DecodedVertex VertexArray[65536];

void Rasterizer::DrawArray(ge_VertexInfo &inInfo, u32 inType, u32 inCount, bool inRepeatDraw)
{
    ge_DecodedVertex        *decodedVertices = (ge_DecodedVertex *)VertexArray;
    void                    *vertex_buffer	 = Memory::addr< void >(theGPUState.vertex_address);
    void                    *index_buffer	 = Memory::addr< void >(theGPUState.index_address);
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
    theRasterizer.DrawPrimitives(inInfo, decodedVertices, inType, count, inRepeatDraw);

    switch (inInfo.it)
    {
    case 0: theGPUState.vertex_address += inInfo.vertex_size * inCount; break;
    case 1: theGPUState.index_address  += inCount;                     break;
    case 2: theGPUState.index_address  += 2*inCount;                   break;
    }
}

void Rasterizer::DrawBezier(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, bool inRepeatDraw)
{
    ge_DecodedVertex        *decodedVertices = (ge_DecodedVertex *)VertexArray;
    void                    *vertex_buffer	 = Memory::addr< void >(theGPUState.vertex_address);
    void                    *index_buffer	 = Memory::addr< void >(theGPUState.index_address);
    u32                      count;

    if (!inRepeatDraw) theTextureManager.SetTexture();

    theDecoder.DecodeBezierSurface(inInfo, decodedVertices, count, vertex_buffer, index_buffer, inUCount, inVCount);

    theRasterizer.DrawPatches(inInfo, decodedVertices, count, inRepeatDraw);

    switch (inInfo.it)
    {
    case 0: theGPUState.vertex_address += inInfo.vertex_size * inUCount * inVCount; break;
    case 1: theGPUState.index_address  += inUCount * inVCount;                      break;
    case 2: theGPUState.index_address  += 2 * inUCount * inVCount;                  break;
    }
}

void Rasterizer::DrawSpline(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, u32 inUFlag, u32 inVFlag, bool inRepeatDraw)
{
    ge_DecodedVertex        *decodedVertices = (ge_DecodedVertex *)VertexArray;
    void                    *vertex_buffer	 = Memory::addr< void >(theGPUState.vertex_address);
    void                    *index_buffer	 = Memory::addr< void >(theGPUState.index_address);
    u32                      count;

    if (!inRepeatDraw) theTextureManager.SetTexture();

    theDecoder.DecodeSplineSurface(inInfo, decodedVertices, count, vertex_buffer, index_buffer, inUCount, inVCount, inUFlag, inVFlag);

    theRasterizer.DrawPatches(inInfo, decodedVertices, count, inRepeatDraw);

    switch (inInfo.it)
    {
    case 0: theGPUState.vertex_address += inInfo.vertex_size * inUCount * inVCount; break;
    case 1: theGPUState.index_address  += inUCount * inVCount;                      break;
    case 2: theGPUState.index_address  += 2 * inUCount * inVCount;                  break;
    }
}

void Rasterizer::SetUpMaterials(ge_VertexInfo *inInfo)
{
    if (!theGPUState.lighting_enable)
    {
        glDisable(GL_COLOR_MATERIAL);
        if (inInfo->ct == 0)
        {
            glColor4fv(theGPUState.material_mac);
        }
    }
    else if (inInfo->ct != 0 && theGPUState.material_flags != 0)
    {
        if ((theGPUState.material_flags & 1) == 0) glMaterialfv(GL_FRONT, GL_AMBIENT,  theGPUState.material_mac);
        if ((theGPUState.material_flags & 2) == 0) glMaterialfv(GL_FRONT, GL_DIFFUSE,  theGPUState.material_mdc);
        if ((theGPUState.material_flags & 4) == 0) glMaterialfv(GL_FRONT, GL_SPECULAR, theGPUState.material_msc);

        u32 flags = 0;
        
        if ((theGPUState.material_flags & 1) != 0 && (theGPUState.material_flags & 2) != 0)
        {
            flags = GL_AMBIENT_AND_DIFFUSE;
        }
        else if((theGPUState.material_flags & 1) != 0) 
        {
            flags = GL_AMBIENT;
        }
        else if((theGPUState.material_flags & 2) != 0) 
         {
            flags = GL_DIFFUSE;
        }
        else if ((theGPUState.material_flags & 4) != 0) 
        {
            flags = GL_SPECULAR;
        }
        glColorMaterial(GL_FRONT_AND_BACK, flags);
        glEnable(GL_COLOR_MATERIAL);
    }
    else 
    {
        glDisable(GL_COLOR_MATERIAL);
        glMaterialfv(GL_FRONT, GL_AMBIENT, theGPUState.material_mac);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, theGPUState.material_mdc);
        glMaterialfv(GL_FRONT, GL_SPECULAR, theGPUState.material_msc);
    }
}

void Rasterizer::EnableAlphaTest(bool inOn)
{
    if (inOn) 
    {
        glEnable(GL_ALPHA_TEST);
    }
    else
    {
        glDisable(GL_ALPHA_TEST);
    }
}

void Rasterizer::EnableAlphaBlend(bool inOn)
{
    if (inOn) 
    {
        glEnable(GL_BLEND);
    }
    else
    {
        glDisable(GL_BLEND);	
    }
}

void Rasterizer::EnableStencilTest(bool inOn)
{
    if (inOn) 
    {
        glEnable(GL_STENCIL_TEST);
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }
}

void Rasterizer::EnableLogicOp(bool inOn)
{
    if (inOn) 
    {
        glEnable(GL_COLOR_LOGIC_OP);
    }
    else
    {
        glDisable(GL_COLOR_LOGIC_OP);
    }
}

void Rasterizer::EnableDepthTest(bool inOn)
{
    if (inOn) 
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

void Rasterizer::EnableTextureMap(bool inOn)
{
    if (inOn) 
    {
        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }
}

void Rasterizer::EnableLighting(bool inOn)
{
    if (inOn) 
    {
        glEnable(GL_LIGHTING);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }
}

void Rasterizer::EnableAntiAlias(bool inOn)
{
    if (inOn)
    {
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    }
    else
    {
        glDisable(GL_LINE_SMOOTH);
    }
}

void Rasterizer::EnableFog(bool inOn)
{
    if (inOn)
    {
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_LINEAR);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
    }
    else
    {
        glDisable(GL_FOG);
    }
}

void Rasterizer::EnableLightX(bool inOn, int inNumber)
{
    if (inOn) 
    {
        glEnable(GL_LIGHT0 + inNumber);
    }
    else
    {
        glDisable(GL_LIGHT0 + inNumber);
    }
}

void Rasterizer::EnableClipPlane(bool inOn)
{
#if 0
    if (inOn)
    { 
        glEnable(GL_CLIP_PLANE0);
        glEnable(GL_CLIP_PLANE1);
        glEnable(GL_CLIP_PLANE2);
        glEnable(GL_CLIP_PLANE3);
        glEnable(GL_CLIP_PLANE4);
        glEnable(GL_CLIP_PLANE5);
    }
    else
    {
        glDisable(GL_CLIP_PLANE0);
        glDisable(GL_CLIP_PLANE1);
        glDisable(GL_CLIP_PLANE2);
        glDisable(GL_CLIP_PLANE3);
        glDisable(GL_CLIP_PLANE4);
        glDisable(GL_CLIP_PLANE5);
    }	
#endif
}

void Rasterizer::EnableFaceCulling(bool inOn)
{
    if (inOn)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
    }
}

void Rasterizer::SetCullDir(bool inDir)
{
    glFrontFace(inDir ? GL_CW : GL_CCW);
}

void Rasterizer::SetTexFunc(u32 txf, u32 tcc, u32 cd)
{
    int env_mode = GL_MODULATE;
    switch(txf) 
    {
    case 0: env_mode = GL_MODULATE; break;
    case 1: env_mode = GL_DECAL;    break;
    case 2: env_mode = GL_BLEND;    break;
    case 3: env_mode = GL_REPLACE;  break;
    case 4: env_mode = GL_ADD;      break;
    default:
        errorf(Rasterizer,"Unsupported tfunc mode");
    }

    int rgbScaleParam = cd;
    float rgbScale = 1.0f;
    if (rgbScaleParam == TFUNC_FRAGMENT_DOUBLE_ENABLE_COLOR_DOUBLED) 
    {
        rgbScale = 2.0f;
    } 
    else if (rgbScaleParam != TFUNC_FRAGMENT_DOUBLE_ENABLE_COLOR_UNTOUCHED) 
    {
        errorf(Rasterizer,"sceGuTexFunc unknown RGB scale parameter %d",cd);
    }

    int alphaParam = tcc;
    bool alphaIsOne = false;

    if (alphaParam == TFUNC_FRAGMENT_DOUBLE_TEXTURE_COLOR_ALPHA_IS_IGNORED) 
        alphaIsOne = true;
    else if (alphaParam != TFUNC_FRAGMENT_DOUBLE_TEXTURE_COLOR_ALPHA_IS_READ) 
    {
        errorf(Rasterizer,"sceGuTexFunc unknown alpha parameter %d",tcc);
    }

    if (rgbScale != 1.0f || alphaIsOne) 
    {
        switch (env_mode)
        {
        case GL_MODULATE:
            // Cv = Cp * Cs
            // Av = Ap * As
            env_mode = GL_COMBINE;
            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);

            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_MODULATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_ALPHA, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
            break;
        case GL_DECAL:
            env_mode = GL_COMBINE;
            // Cv = Cs * As + Cp * (1 - As)
            // Av = Ap
            if (alphaIsOne) 
            {
                // Simplified version when As == 1:
                // Cv = Cs
                glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
                glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
                glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
            } 
            else 
            {
                glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
                glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
                glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
                glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB, GL_PREVIOUS);
                glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
                glTexEnvi(GL_TEXTURE_ENV, GL_SRC2_RGB, GL_TEXTURE);
                glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_ALPHA);
            }

            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
            break;
        case GL_BLEND:
            // Cv = Cc * Cs + Cp * (1 - Cs)
            // Av = As * Ap
            env_mode = GL_COMBINE;
            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_CONSTANT);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC2_RGB, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_COLOR);

            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_MODULATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_ALPHA, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
            break;
        case GL_REPLACE:
            // Cv = Cs
            // Av = As
            env_mode = GL_COMBINE;
            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);

            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
            break;
        case GL_ADD:
            // Cv = Cp + Cs
            // Av = Ap * As
            env_mode = GL_COMBINE;
            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_ADD);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);

            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_MODULATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
            glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_ALPHA, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
            break;
        default:
            errorf(Rasterizer,"Unimplemented sceGuTexFunc RGB doubled for env_mode=" + env_mode);
            break;
        }
    }
    glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, rgbScale);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, env_mode);
}

void Rasterizer::SetFogColor(float *inData)
{
    glFogfv(GL_FOG_COLOR, inData);
}

void Rasterizer::SetFogDist(float inStart, float inEnd)
{
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, inStart);
    glFogf(GL_FOG_END,   inEnd);
}

void Rasterizer::EnableDither(bool inOn)
{
    if(inOn)
        glEnable(GL_DITHER);
    else
        glDisable(GL_DITHER);
}

__forceinline int BlendFix(float* fix_color)
{
    if (fix_color[0] == 0 && fix_color[1] == 0 && fix_color[2] == 0) 
        return GL_ZERO;
    else if (fix_color[0] == 1 && fix_color[1] == 1 && fix_color[2] == 1)
        return GL_ONE;
    return GL_CONSTANT_COLOR;
}

void Rasterizer::SetAlphaBlending(u8 inA, u8 inB, u8 inEqu)
{
    GLenum efunc[] = { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX, GL_FUNC_ADD };

    u32	gl_blend_a = GL_SRC_COLOR;
    u32 gl_blend_b = GL_DST_COLOR;

    glBlendEquation(efunc[inEqu]);

    switch (inA)
    {
    case  0: gl_blend_a = GL_DST_COLOR;			                     break;
    case  1: gl_blend_a = GL_ONE_MINUS_DST_COLOR;                    break;
    case  2: gl_blend_a = GL_SRC_ALPHA;			                     break;
    case  3: gl_blend_a = GL_ONE_MINUS_SRC_ALPHA;                    break;
    case  4: gl_blend_a = GL_DST_ALPHA;			                     break;
    case  5: gl_blend_a = GL_ONE_MINUS_DST_ALPHA;                    break;
    case  6: gl_blend_a = GL_SRC_ALPHA;			                     break;
    case  7: gl_blend_a = GL_ONE_MINUS_SRC_ALPHA;                    break;
    case  8: gl_blend_a = GL_DST_ALPHA;			                     break;
    case  9: gl_blend_a = GL_ONE_MINUS_DST_ALPHA;                    break;
    case 10: gl_blend_a = BlendFix(theGPUState.alpha_blending_fixa); break;
    default: errorf(Rasterizer,"Unsupported src blending mode");
    }

    switch (inB) 
    {
    case  0: gl_blend_b = GL_SRC_COLOR;			                     break;
    case  1: gl_blend_b = GL_ONE_MINUS_SRC_COLOR;                    break;
    case  2: gl_blend_b = GL_SRC_ALPHA;                              break;
    case  3: gl_blend_b = GL_ONE_MINUS_SRC_ALPHA;                    break;
    case  4: gl_blend_b = GL_DST_ALPHA;                              break;
    case  5: gl_blend_b = GL_ONE_MINUS_DST_ALPHA;                    break;
    case  6: gl_blend_b = GL_SRC_ALPHA;                              break;
    case  7: gl_blend_b = GL_ONE_MINUS_SRC_ALPHA;                    break;
    case  8: gl_blend_b = GL_DST_ALPHA;                              break;
    case  9: gl_blend_b = GL_ONE_MINUS_DST_ALPHA;                    break;
    case 10: gl_blend_b = BlendFix(theGPUState.alpha_blending_fixb); break;
    default: errorf(Rasterizer,"Unsupported dst blending mode");
    }

    if (gl_blend_a == GL_CONSTANT_COLOR) 
    {
        glBlendColor(theGPUState.alpha_blending_fixa[0], theGPUState.alpha_blending_fixa[1], theGPUState.alpha_blending_fixa[2], 1.0f);    
    }
    else if (gl_blend_b == GL_CONSTANT_COLOR) 
    {
        glBlendColor(theGPUState.alpha_blending_fixb[0], theGPUState.alpha_blending_fixb[1], theGPUState.alpha_blending_fixb[2], 1.0f);
    }

    //glBlendFuncSeparate(gl_blend_a, gl_blend_b, GL_ONE, GL_ZERO); 
    glBlendFunc(gl_blend_a, gl_blend_b); 
}

void Rasterizer::SetStencilTest(u32 inSource, u32 inRef, u32 inMask)
{
    int function = GL_ALWAYS;

    switch (inSource) 
    {
    case STST_FUNCTION_NEVER_PASS_STENCIL_TEST:			function = GL_NEVER;	break;
    case STST_FUNCTION_ALWAYS_PASS_STENCIL_TEST:		function = GL_ALWAYS;	break;
    case STST_FUNCTION_PASS_TEST_IF_MATCHES:			function = GL_EQUAL;	break;
    case STST_FUNCTION_PASS_TEST_IF_DIFFERS:			function = GL_NOTEQUAL; break;
    case STST_FUNCTION_PASS_TEST_IF_LESS:				function = GL_LESS;		break;
    case STST_FUNCTION_PASS_TEST_IF_LESS_OR_EQUAL:		function = GL_LEQUAL;	break;
    case STST_FUNCTION_PASS_TEST_IF_GREATER:			function = GL_GREATER;	break;
    case STST_FUNCTION_PASS_TEST_IF_GREATER_OR_EQUAL:	function = GL_GEQUAL;	break;
    }

    glStencilFunc (function, inRef, inMask);
}

u32 Rasterizer::TranslateStencilOp(u32 inOperation)
{
    switch (inOperation) 
    {
    case SOP_KEEP_STENCIL_VALUE:		return GL_KEEP;
    case SOP_ZERO_STENCIL_VALUE:		return GL_ZERO;
    case SOP_REPLACE_STENCIL_VALUE:		return GL_REPLACE;
    case SOP_INVERT_STENCIL_VALUE:		return GL_INVERT;
    case SOP_INCREMENT_STENCIL_VALUE:	return GL_INCR;
    case SOP_DECREMENT_STENCIL_VALUE:   return GL_DECR;
    }

    return GL_KEEP;
}

void Rasterizer::SetStencilOp(u32 sfail,u32 zfail,u32 zpass)
{
    glStencilOp(sfail, zfail, zpass);
}

u32 Rasterizer::TranslateLogicalOp(u32 inOperation)
{
    switch (inOperation) 
    {
    case 0:		return GL_CLEAR;
    case 1:		return GL_AND;
    case 2:		return GL_AND_REVERSE;
    case 3:		return GL_COPY;
    case 4:	    return GL_AND_INVERTED;
    case 5:     return GL_NOOP;
    case 6:     return GL_XOR;
    case 7:     return GL_OR;
    case 8:     return GL_NOR;
    case 9:     return GL_EQUIV;
    case 10:    return GL_INVERT;
    case 11:    return GL_OR_REVERSE;
    case 12:    return GL_COPY_INVERTED;
    case 13:    return GL_OR_INVERTED;
    case 14:    return GL_NAND;
    case 15:    return GL_SET;
    }

    return GL_COPY;
}

void Rasterizer::SetLogicalOp(u32 LOP)
{
    glLogicOp(LOP);
}

void Rasterizer::SetAmbientModelLight(float* inModel)
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, inModel);
}

void Rasterizer::SetEmmisiveModelLight(float* inModel)
{
    glMaterialfv(GL_FRONT, GL_EMISSION, inModel);
}

void Rasterizer::SetQuadricAtten(int inLight, float inData)
{
    glLightf(GL_LIGHT0 + inLight, GL_QUADRATIC_ATTENUATION, inData);
}

void Rasterizer::SetLinearAtten(int inLight, float inData)
{
    glLightf(GL_LIGHT0 + inLight, GL_LINEAR_ATTENUATION, inData);
}

void Rasterizer::SetConstantAtten(int inLight, float inData)
{
    glLightf(GL_LIGHT0 + inLight, GL_CONSTANT_ATTENUATION, inData);
}     

void Rasterizer::SetLightColorAmbient(int inLight, float* inData)
{
    glLightfv(GL_LIGHT0 + inLight, GL_AMBIENT, inData);
}

void Rasterizer::SetLightColorDiffuse(int inLight, float* inData)
{
    glLightfv(GL_LIGHT0 + inLight, GL_DIFFUSE, inData);
}

void Rasterizer::SetLightColorSpecular(int inLight, float* inData)
{
    glLightfv(GL_LIGHT0 + inLight, GL_SPECULAR, inData);
}

void Rasterizer::SetDepthMask(bool inOn)
{
    glDepthMask(inOn);
}

void Rasterizer::SetShadeModel(u32 inData)
{
    bool model = (inData & 1) != 0;
    glShadeModel(model ? GL_SMOOTH : GL_FLAT);
}

void Rasterizer::SetSpecularPower(float* inPower)
{
    glMaterialf(GL_FRONT, GL_SHININESS, *inPower);
}

void Rasterizer::SetLightMode(bool inOn)
{
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, inOn ? GL_SEPARATE_SPECULAR_COLOR : GL_SINGLE_COLOR);
}

void Rasterizer::SetAlphaTest(int inFunc, int inRef)
{
    int glFunc = GL_ALWAYS;
    switch(inFunc) 
    {
    case ATST_NEVER_PASS_PIXEL:					glFunc = GL_NEVER;		break;
    case ATST_ALWAYS_PASS_PIXEL:				glFunc = GL_ALWAYS;		break;
    case ATST_PASS_PIXEL_IF_MATCHES:			glFunc = GL_EQUAL;		break;
    case ATST_PASS_PIXEL_IF_DIFFERS:			glFunc = GL_NOTEQUAL;	break;	
    case ATST_PASS_PIXEL_IF_LESS:				glFunc = GL_LESS;		break;
    case ATST_PASS_PIXEL_IF_LESS_OR_EQUAL:		glFunc = GL_LEQUAL;		break;
    case ATST_PASS_PIXEL_IF_GREATER:			glFunc = GL_GREATER;	break;
    case ATST_PASS_PIXEL_IF_GREATER_OR_EQUAL:	glFunc = GL_GEQUAL;		break;

    default: infof(dList,"CMD_CMSK: unhandled func");					break;
    }

    glAlphaFunc(glFunc, inRef);
}

void Rasterizer::CalcSkinningPosition(float v[3], ge_DecodedVertex &outDecodedVertice)
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    float *src = outDecodedVertice.v;    
    int weight_count = ((theGPUState.transform_mode >> 14) & 0x7) + 1;

    for (int i = 0; i < weight_count; i++)
    {
        float w = outDecodedVertice.w[i];

        if (w != 0.0f)
        {
            float *BM = mBM[i].mData;

            x += (src[0] * BM[ 0]
              +   src[1] * BM[ 4]
              +   src[2] * BM[ 8]
              +            BM[12]) * w;

            y += (src[0] * BM[ 1]
              +   src[1] * BM[ 5]
              +   src[2] * BM[ 9]
              +            BM[13]) * w;

            z += (src[0] * BM[ 2]
              +   src[1] * BM[ 6]
              +   src[2] * BM[10]
              +            BM[14]) * w;
        }
    }

    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void Rasterizer::CalcSkinningNormal(float n[3], ge_DecodedVertex &outDecodedVertice)
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    float *src = outDecodedVertice.n;
    int weight_count = ((theGPUState.transform_mode >> 14) & 0x7) + 1;

    for (int i = 0; i < weight_count; i++)
    {
        float w = outDecodedVertice.w[i];

        if (w != 0.0f)
        {
            float *BM = mBM[i].mData;

            x += (src[0] * BM[ 0]
              +   src[1] * BM[ 4]
              +   src[2] * BM[ 8]) * w;

            y += (src[0] * BM[ 1]
              +   src[1] * BM[ 5]
              +   src[2] * BM[ 9]) * w;

            z += (src[0] * BM[ 2]
              +   src[1] * BM[ 6]
              +   src[2] * BM[10]) * w;
        }
    }

    n[0] = x;
    n[1] = y;
    n[2] = z;
}

void Rasterizer::SetColorMask(bool inData[4])
{
    glColorMask(inData[0], inData[1], inData[2], inData[3]);
}

void Rasterizer::SetLightType(int inType[4])
{
}
void Rasterizer::SetLightKind(int inKind[4])
{
}


void Rasterizer::SetScissoringArea(u16 inScissor[4])
{
    mScissorW = 1 + u32(inScissor[2]) - u32(inScissor[0]);
    mScissorH = 1 + u32(inScissor[3]) - u32(inScissor[1]);
    mScissorX = u32(inScissor[0]); 
    mScissorY = 272 - u32(inScissor[1]) - mScissorH; 
    UpdateScissoringArea();
}

void Rasterizer::UpdateScissoringArea()
{
    glScissor(mScissorX * thePspScreen->width() / 480, mScissorY * thePspScreen->height() / 272, mScissorW * thePspScreen->width() / 480, mScissorH * thePspScreen->height() / 272);
}

void Rasterizer::SetDrawingRegion(u16 inRegion[4])
{
    double equ[4];
    equ[2] = +0.0;

    equ[0] = +1.0;       equ[1] = +0.0;    equ[3] = inRegion[0] /* left   */;
    glClipPlane(GL_CLIP_PLANE0, equ);
    
    equ[0] = -1.0;    /* equ[1] = +0.0; */ equ[3] = inRegion[2] /* right  */;
    glClipPlane(GL_CLIP_PLANE2, equ);

    equ[0] = +0.0;       equ[1] = +1.0;    equ[3] = inRegion[1] /* top    */;
    glClipPlane(GL_CLIP_PLANE1, equ);
    
    /* equ[1] = +0.0; */ equ[1] = -1.0;    equ[3] = inRegion[3] /* bottom */;
    glClipPlane(GL_CLIP_PLANE3, equ);
}

bool Rasterizer::IsObjectCulled()
{
    // return true if object is culled
    int result = 0;
    glGetQueryObjectiv(mQueryIds, GL_QUERY_RESULT, &result);
    return (0 == result);
}

void Rasterizer::CullObject(ge_VertexInfo &inInfo, u32 inCount)
{
    // [hlide] note that an object is culled if it is not visible inside the drawing region
    //         so the actual implementation is not complete

    if (inInfo.vt == 0) 
    {
        errorf(Rasterizer, "No positions for vertex!");
        return;
    } 
    else if (!(glBeginQuery && glEndQuery))
    {
        errorf(Rasterizer, "No support for glBeginQuery and glEndQuery");
        return;
    } 
    else if ((inCount & 7) != 0) 
    {
        errorf(Rasterizer, "We are not sure how to deal with this multiple yet, if you hit this case then tell us what game and we will fix this!(Otenki)");
    }

    // ADD BEGINRENDERING

    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColorMask(false, false, false, false);
    glDepthMask(false);
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_FOG);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LOGIC_OP);
    glDisable(GL_CULL_FACE);
    glDisable(GL_SCISSOR_TEST);

    glBeginQuery(GL_SAMPLES_PASSED, mQueryIds);
    //
    // The bounding box is a cube defined by 8 vertices.
    // It is not clear if the vertices have to be listed in a pre-defined order.
    // Which primitive should be used?
    // - GL_TRIANGLE_STRIP: we only draw 3 faces of the cube
    // - GL_QUADS: how are organized the 8 vertices to draw all the cube faces?
    //

    static ge_DecodedVertex decoded_vertices[256];

    void *vertex_buffer	= Memory::addr< void >(theGPUState.vertex_address);
    void *index_buffer	= Memory::addr< void >(theGPUState.index_address);

    theDecoder.DecodeVertices(inInfo, (ge_DecodedVertex*)decoded_vertices, vertex_buffer, index_buffer, inCount);

    glBegin(GL_QUADS);
    float bboxVertices[8][3];
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
            // Front face
            glVertex3fv(bboxVertices[0]);
            glVertex3fv(bboxVertices[1]);
            glVertex3fv(bboxVertices[3]);
            glVertex3fv(bboxVertices[2]);

            // Back face
            glVertex3fv(bboxVertices[4]);
            glVertex3fv(bboxVertices[5]);
            glVertex3fv(bboxVertices[7]);
            glVertex3fv(bboxVertices[6]);

            // Right face
            glVertex3fv(bboxVertices[1]);
            glVertex3fv(bboxVertices[5]);
            glVertex3fv(bboxVertices[7]);
            glVertex3fv(bboxVertices[3]);

            // Left face
            glVertex3fv(bboxVertices[0]);
            glVertex3fv(bboxVertices[4]);
            glVertex3fv(bboxVertices[6]);
            glVertex3fv(bboxVertices[2]);

            // Top face
            glVertex3fv(bboxVertices[2]);
            glVertex3fv(bboxVertices[3]);
            glVertex3fv(bboxVertices[7]);
            glVertex3fv(bboxVertices[6]);

            // Bottom face
            glVertex3fv(bboxVertices[0]);
            glVertex3fv(bboxVertices[1]);
            glVertex3fv(bboxVertices[5]);
            glVertex3fv(bboxVertices[4]);
        }
    }
    glEnd();
    glEndQuery(GL_SAMPLES_PASSED);
    glPopAttrib();

    // ADD ENDRENDERING

    switch (inInfo.it)
    {
    case 0: theGPUState.vertex_address += inInfo.vertex_size * inCount; break;
    case 1: theGPUState.index_address  += inCount;                     break;
    case 2: theGPUState.index_address  += 2*inCount;                   break;
    }
}

#if 0 // software object culling using bbox

/*
 * matrix and math utility routines and macros
 */

static void matrixConcatenate (float *result, float *ma, float *mb)
{
    int i;
    float mb00, mb01, mb02, mb03,
          mb10, mb11, mb12, mb13,
          mb20, mb21, mb22, mb23,
          mb30, mb31, mb32, mb33;
    float mai0, mai1, mai2, mai3;

    mb00 = mb[0];  mb01 = mb[1];
    mb02 = mb[2];  mb03 = mb[3];
    mb10 = mb[4];  mb11 = mb[5];
    mb12 = mb[6];  mb13 = mb[7];
    mb20 = mb[8];  mb21 = mb[9];
    mb22 = mb[10];  mb23 = mb[11];
    mb30 = mb[12];  mb31 = mb[13];
    mb32 = mb[14];  mb33 = mb[15];

    for (i = 0; i < 4; i++) {
        mai0 = ma[i*4+0];  mai1 = ma[i*4+1];
	    mai2 = ma[i*4+2];  mai3 = ma[i*4+3];

        result[i*4+0] = mai0 * mb00 + mai1 * mb10 + mai2 * mb20 + mai3 * mb30;
        result[i*4+1] = mai0 * mb01 + mai1 * mb11 + mai2 * mb21 + mai3 * mb31;
        result[i*4+2] = mai0 * mb02 + mai1 * mb12 + mai2 * mb22 + mai3 * mb32;
        result[i*4+3] = mai0 * mb03 + mai1 * mb13 + mai2 * mb23 + mai3 * mb33;
    }
}

#define vectorLength(nin) \
    sqrt((nin)[0]*(nin)[0] + (nin)[1]*(nin)[1] + (nin)[2]*(nin)[2])
#define distanceFromPlane(peq,p) \
    ((peq)[0]*(p)[0] + (peq)[1]*(p)[1] + (peq)[2]*(p)[2] + (peq)[3])




/*
 * View volume plane storage and calculation
 */

/* Storage for the six planes, left right top bottom near far */
float planeEqs[6][4];

/* Calculates the six view volume planes in object coordinate (OC) space.
       
       Algorithm:
       
       A view volume plane in OC is transformed into CC by multiplying it by
       the inverse of the combined ModelView and Projection matrix (M).
       Algebraically, this is written:
              -1
         P   M   = P
          oc        cc
       
       The resulting six view volume planes in CC are:
         [ -1  0  0  1 ]
         [  1  0  0  1 ]
         [  0 -1  0  1 ]
         [  0  1  0  1 ]
         [  0  0 -1  1 ]
         [  0  0  1  1 ]
       
       To transform the CC view volume planes into OC, we simply multiply
       the CC plane equations by the combined ModelView and Projection matrices
       using standard vector-matrix multiplication. Algebraically, this is written:  
         P   M = P
          cc      oc
       
       Since all of the CC plane equation components are 0, 1, or -1, full vector-
       matrix multiplication is overkill. For example, the first element of the
       first OC plane equation is computed as:
         A = -1 * m0 + 0 * m1 + 0 * m2 + 1 * m3
       This simplifies to:
         A = m3 - m0
       
       Other terms simplify similarly. In fact, all six plane equations can be
       computed as follows:
         [ m3-m0  m7-m4  m11-m8  m15-m12 ]
         [ m3+m0  m7+m4  m11+m8  m15+m12 ]
         [ m3-m1  m7-m5  m11-m9  m15-m13 ]
         [ m3+m1  m7+m5  m11+m9  m15+m13 ]
         [ m3-m2  m7-m6  m11-m10 m15-m14 ]
         [ m3+m2  m7+m6  m11+m10 m15+m14 ]
     */
static void calcViewVolumePlanes ()
{
    GLfloat ocEcMat[16], ecCcMat[16], ocCcMat[16];


    /* Get the modelview and projection matrices */
    glGetFloatv (GL_MODELVIEW_MATRIX, ocEcMat);
    glGetFloatv (GL_PROJECTION_MATRIX, ecCcMat);

    /* ocCcMat transforms from OC (object coordinates) to CC (clip coordinates) */
    matrixConcatenate (ocCcMat, ocEcMat, ecCcMat);

    /* Calculate the six OC plane equations. */
    planeEqs[0][0] = ocCcMat[3] - ocCcMat[0]; 
    planeEqs[0][1] = ocCcMat[7] - ocCcMat[4]; 
    planeEqs[0][2] = ocCcMat[11] - ocCcMat[8]; 
    planeEqs[0][3] = ocCcMat[15] - ocCcMat[12]; 

    planeEqs[1][0] = ocCcMat[3] + ocCcMat[0]; 
    planeEqs[1][1] = ocCcMat[7] + ocCcMat[4]; 
    planeEqs[1][2] = ocCcMat[11] + ocCcMat[8]; 
    planeEqs[1][3] = ocCcMat[15] + ocCcMat[12]; 

    planeEqs[2][0] = ocCcMat[3] + ocCcMat[1]; 
    planeEqs[2][1] = ocCcMat[7] + ocCcMat[5]; 
    planeEqs[2][2] = ocCcMat[11] + ocCcMat[9]; 
    planeEqs[2][3] = ocCcMat[15] + ocCcMat[13]; 

    planeEqs[3][0] = ocCcMat[3] - ocCcMat[1]; 
    planeEqs[3][1] = ocCcMat[7] - ocCcMat[5]; 
    planeEqs[3][2] = ocCcMat[11] - ocCcMat[9]; 
    planeEqs[3][3] = ocCcMat[15] - ocCcMat[13]; 

    planeEqs[4][0] = ocCcMat[3] + ocCcMat[2]; 
    planeEqs[4][1] = ocCcMat[7] + ocCcMat[6]; 
    planeEqs[4][2] = ocCcMat[11] + ocCcMat[10]; 
    planeEqs[4][3] = ocCcMat[15] + ocCcMat[14]; 

    planeEqs[5][0] = ocCcMat[3] - ocCcMat[2]; 
    planeEqs[5][1] = ocCcMat[7] - ocCcMat[6]; 
    planeEqs[5][2] = ocCcMat[11] - ocCcMat[10]; 
    planeEqs[5][3] = ocCcMat[15] - ocCcMat[14]; 
}

static int culled(float *bbox)
{
    int i, j;
    int out, in;

    for (i = 0; i < 6; i++)
    {
        in = 0;
        out = 0;
        for (j = 0; j < 8; j++)
        {
            if (distanceFromPlane(planeEqs[i], bbox[j]) < 0.0f)
            {
                out++;
                if (in) break;
            }
            else
            {
                in++;
                if (out) break;
            }
        }
        if (!in)
        {
            // all of the eight vertices are trivially culled
            return 1;
        }
    }
    return 0;
}

#endif

#endif // USE_SHADERS
