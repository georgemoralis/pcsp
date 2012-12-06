#ifndef gl_fbo_h__
#define gl_fbo_h__

#include "gl_Core.h"
#include "gl_Attributes.h"

class gl_FrameBufferObject : protected gl_Core
{
public:
    gl_FrameBufferObject()
    :   m_fbo(0)
    {
        GenFramebuffers(1, &m_fbo);
    }

    ~gl_FrameBufferObject()
    {
        if (m_active_fbo == m_fbo)
        {
            Unbind();
        }
        DeleteFramebuffers(1, &m_fbo);
    }

    __forceinline void Bind()
    {
        BindFramebuffer(FRAMEBUFFER, m_fbo);
        m_active_fbo = m_fbo;
    }

    __forceinline void Unbind()
    {
        assert(m_active_fbo == m_fbo);

        BindFramebuffer(FRAMEBUFFER, 0);
        m_active_fbo = 0;
    }

    __forceinline void AttachTexture2DColor(u32 texID, u32 index)
    {
        assert(m_active_fbo == m_fbo);

        FramebufferTexture2D(FRAMEBUFFER, COLOR_ATTACHMENT0 + index, TEXTURE_2D, (GLuint)texID, 0);
    }

    __forceinline void AttachTexture2DDepth(u32 texID)
    {
        assert(m_active_fbo == m_fbo);

        //glBindTexture(GL_TEXTURE_2D, texID);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, fbWidth, fbHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        //glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer1);

        FramebufferTexture2D(FRAMEBUFFER, DEPTH_ATTACHMENT, TEXTURE_2D, (GLuint)texID, 0);
    }

    __forceinline void AttachRenderbufferColor(u32 rboID, u32 index)
    {
        assert(m_active_fbo == m_fbo);

        FramebufferRenderbuffer(FRAMEBUFFER, COLOR_ATTACHMENT0 + index, RENDERBUFFER, (GLuint)rboID);
    }

    __forceinline void AttachRenderbufferDepth(u32 rboID)
    {
        assert(m_active_fbo == m_fbo);

        FramebufferRenderbuffer(FRAMEBUFFER, DEPTH_ATTACHMENT, RENDERBUFFER, (GLuint)rboID);
    }

    __forceinline bool CheckStatus()
    {
        GLenum status = glCheckFramebufferStatus(m_fbo);

        switch(status)
        {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            tracef(Renderer, "Framebuffer complete.");
            return true;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            errorf(Renderer, "Framebuffer incomplete: Attachment is NOT complete.");
            return false;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            errorf(Renderer, "Framebuffer incomplete: No image is attached to FBO.");
            return false;

        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            errorf(Renderer, "Framebuffer incomplete: Attached images have different dimensions.");
            return false;

        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            errorf(Renderer, "Framebuffer incomplete: Color attached images have different internal formats.");
            return false;

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            errorf(Renderer, "Framebuffer incomplete: Draw buffer.");
            return false;

        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            errorf(Renderer, "Framebuffer incomplete: Read buffer.");
            return false;

        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            errorf(Renderer, "Unsupported by FBO implementation.");
            return false;

        default:
            errorf(Renderer, "Unknow error.");
            return false;
        }
    }

private:
    GLuint m_fbo;

    static GLuint m_active_fbo;

/*
    static GLboolean IsRenderbuffer(GLuint renderbuffer);
    static void      BindRenderbuffer(GLenum target, GLuint renderbuffer);
    static void      DeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers);
    static void      GenRenderbuffers(GLsizei n, GLuint *renderbuffers);

    static void      RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);

    static void      RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);

    static void      GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params);

    static boolean   IsFramebuffer(GLuint framebuffer);
    static void      BindFramebuffer(GLenum target, GLuint framebuffer);
    static void      DeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
    static void      GenFramebuffers(GLsizei n, GLuint *framebuffers);

    static GLenum    CheckFramebufferStatus(GLenum target);

    static void      FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    static void      FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    static void      FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer);
    static void      FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);

    static void      FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

    static void      GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params);

    static void      BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

    static void      GenerateMipmap(GLenum target);
*/

};

weaksymbol GLuint gl_FrameBufferObject::m_active_fbo = 0;

#endif // gl_fbo_h__
