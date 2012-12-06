
#include "stdafx.h"

#include "opengl/gl_Core.h"

#define LOAD_FUNC1(f)       f = (gl_Core::f##FUNC)(gl##f)
#define LOAD_FUNC2(f, name) f = (gl_Core::f##FUNC)(name)

gl_Core gl;

bool gl_Core::framebuffer_object;
bool gl_Core::texture_lod_bias;
bool gl_Core::depth_bounds_test;
bool gl_Core::version_1_5;

gl_Core::IsRenderbufferFUNC                      gl_Core::IsRenderbuffer;
gl_Core::BindRenderbufferFUNC                    gl_Core::BindRenderbuffer;
gl_Core::DeleteRenderbuffersFUNC                 gl_Core::DeleteRenderbuffers;
gl_Core::GenRenderbuffersFUNC                    gl_Core::GenRenderbuffers;
gl_Core::RenderbufferStorageFUNC                 gl_Core::RenderbufferStorage;
gl_Core::RenderbufferStorageMultisampleFUNC      gl_Core::RenderbufferStorageMultisample;
gl_Core::GetRenderbufferParameterivFUNC          gl_Core::GetRenderbufferParameteriv;
gl_Core::IsFramebufferFUNC                       gl_Core::IsFramebuffer;
gl_Core::BindFramebufferFUNC                     gl_Core::BindFramebuffer;
gl_Core::DeleteFramebuffersFUNC                  gl_Core::DeleteFramebuffers;
gl_Core::GenFramebuffersFUNC                     gl_Core::GenFramebuffers;
gl_Core::CheckFramebufferStatusFUNC              gl_Core::CheckFramebufferStatus;
gl_Core::FramebufferTexture1DFUNC                gl_Core::FramebufferTexture1D;
gl_Core::FramebufferTexture2DFUNC                gl_Core::FramebufferTexture2D;
gl_Core::FramebufferTexture3DFUNC                gl_Core::FramebufferTexture3D;
gl_Core::FramebufferTextureLayerFUNC             gl_Core::FramebufferTextureLayer;
gl_Core::FramebufferRenderbufferFUNC             gl_Core::FramebufferRenderbuffer;
gl_Core::GetFramebufferAttachmentParameterivFUNC gl_Core::GetFramebufferAttachmentParameteriv;
gl_Core::BlitFramebufferFUNC                     gl_Core::BlitFramebuffer;
gl_Core::GenerateMipmapFUNC                      gl_Core::GenerateMipmap;

void gl_Core::init_framebuffer_object()
{
    version_1_5 = __GLEW_VERSION_1_5 != 0;

    framebuffer_object = false;
    {
        IsRenderbuffer                      = NULL;
        BindRenderbuffer                    = NULL;
        DeleteRenderbuffers                 = NULL;
        GenRenderbuffers                    = NULL;
        RenderbufferStorage                 = NULL;
        RenderbufferStorageMultisample      = NULL;
        GetRenderbufferParameteriv          = NULL;
        IsFramebuffer                       = NULL;
        BindFramebuffer                     = NULL;
        DeleteFramebuffers                  = NULL;
        GenFramebuffers                     = NULL;
        CheckFramebufferStatus              = NULL;
        FramebufferTexture1D                = NULL;
        FramebufferTexture2D                = NULL;
        FramebufferTexture3D                = NULL;
        FramebufferTextureLayer             = NULL;
        FramebufferRenderbuffer             = NULL;
        GetFramebufferAttachmentParameteriv = NULL;
        BlitFramebuffer                     = NULL;
        GenerateMipmap                      = NULL;
    }

    if (__GLEW_ARB_framebuffer_object)
    {
        framebuffer_object = true;

        LOAD_FUNC1(IsRenderbuffer);
        LOAD_FUNC1(BindRenderbuffer);
        LOAD_FUNC1(DeleteRenderbuffers);
        LOAD_FUNC1(GenRenderbuffers);
        LOAD_FUNC1(RenderbufferStorage);
        LOAD_FUNC1(RenderbufferStorageMultisample);
        LOAD_FUNC1(GetRenderbufferParameteriv);
        LOAD_FUNC1(IsFramebuffer);
        LOAD_FUNC1(BindFramebuffer);
        LOAD_FUNC1(DeleteFramebuffers);
        LOAD_FUNC1(GenFramebuffers);
        LOAD_FUNC1(CheckFramebufferStatus);
        LOAD_FUNC1(FramebufferTexture1D);
        LOAD_FUNC1(FramebufferTexture2D);
        LOAD_FUNC1(FramebufferTexture3D);
        LOAD_FUNC1(FramebufferTextureLayer);
        LOAD_FUNC1(FramebufferRenderbuffer);
        LOAD_FUNC1(GetFramebufferAttachmentParameteriv);
        LOAD_FUNC1(BlitFramebuffer);
        LOAD_FUNC1(GenerateMipmap);
    }
    else
    {
        int extensions = 0;

        if (__GLEW_EXT_framebuffer_object)
        {
            extensions++;

            LOAD_FUNC2(IsRenderbuffer, glIsRenderbufferEXT);
            LOAD_FUNC2(BindRenderbuffer, glBindRenderbufferEXT);
            LOAD_FUNC2(DeleteRenderbuffers, glDeleteRenderbuffersEXT);
            LOAD_FUNC2(GenRenderbuffers, glGenRenderbuffersEXT);
            LOAD_FUNC2(RenderbufferStorage, glRenderbufferStorageEXT);
            LOAD_FUNC2(GetRenderbufferParameteriv, glGetRenderbufferParameterivEXT);
            LOAD_FUNC2(IsFramebuffer, glIsFramebufferEXT);
            LOAD_FUNC2(BindFramebuffer, glBindFramebufferEXT);
            LOAD_FUNC2(DeleteFramebuffers, glDeleteFramebuffersEXT);
            LOAD_FUNC2(GenFramebuffers, glGenFramebuffersEXT);
            LOAD_FUNC2(CheckFramebufferStatus, glCheckFramebufferStatusEXT);
            LOAD_FUNC2(FramebufferTexture1D, glFramebufferTexture1DEXT);
            LOAD_FUNC2(FramebufferTexture2D, glFramebufferTexture2DEXT);
            LOAD_FUNC2(FramebufferTexture3D, glFramebufferTexture3DEXT);
            LOAD_FUNC2(FramebufferRenderbuffer, glFramebufferRenderbufferEXT);
            LOAD_FUNC2(GetFramebufferAttachmentParameteriv, glGetFramebufferAttachmentParameterivEXT);
            LOAD_FUNC2(GenerateMipmap, glGenerateMipmapEXT);
        }
        if (__GLEW_EXT_framebuffer_multisample)
        {
            extensions++;

            LOAD_FUNC2(RenderbufferStorageMultisample, glRenderbufferStorageMultisampleEXT);
        }
        if (__GLEW_ARB_geometry_shader4)
        {
            extensions++;

            LOAD_FUNC2(FramebufferTextureLayer, glFramebufferTextureLayerARB);
        }
        else if (__GLEW_EXT_geometry_shader4)
        {
            extensions++;

            LOAD_FUNC2(FramebufferTextureLayer, glFramebufferTextureLayerEXT);
        }
        if (__GLEW_EXT_framebuffer_blit)
        {
            extensions++;

            LOAD_FUNC2(BlitFramebuffer, glBlitFramebufferEXT);
        }

        framebuffer_object = (extensions == 5);
    }
}

gl_Core::DepthBoundsFUNC gl_Core::DepthBounds;

#if 0
static void APIENTRY DepthBoundDEFAULT(GLclampd, GLclampd)
{
    // do nothing :/
}
#endif

void gl_Core::init_depth_bounds_test()
{
    depth_bounds_test = false;
    {
        DepthBounds = 0;
    }

    if (__GLEW_EXT_depth_bounds_test)
    {
        depth_bounds_test = true;

        LOAD_FUNC2(DepthBounds, glDepthBoundsEXT);
    }
}


void gl_Core::Initialize()
{
    glewInit();
    init_framebuffer_object();
    init_depth_bounds_test();

    // DrawRectangleArrays
    for (int i = 0, p = 0; i < 65536/4; ++i, p += 4)
    {
        rectangle_arrays_i[i] = p;
        rectangle_arrays_c[i] = 4;
    }
}

void gl_Core::Terminate()
{

}

GLint   gl_Core::rectangle_arrays_i[65536/4];
GLsizei gl_Core::rectangle_arrays_c[65536/4];
