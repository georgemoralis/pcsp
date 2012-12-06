#ifndef gl_rbo_h__
#define gl_rbo_h__

#include "gl_Core.h"
#include "gl_Attributes.h"

class gl_RenderBufferObject : protected gl_Core
{
public:
    gl_RenderBufferObject()
    :   m_rbo(0)
    {
        GenRenderbuffers(1, &m_rbo);
    }

    ~gl_RenderBufferObject()
    {
        DeleteRenderbuffers(1, &m_rbo);
    }

    __forceinline void Bind()
    {
        BindRenderbuffer(RENDERBUFFER, m_rbo);
    }

	__forceinline void SetColorStorage(u32 width, u32 height)
	{
		RenderbufferStorage(RENDERBUFFER, GL_RGBA32F, (GLsizei)width, (GLsizei)height);
	}

	__forceinline void SetDepthStorage(u32 width, u32 height)
	{
		RenderbufferStorage(RENDERBUFFER, GL_DEPTH32F_STENCIL8, (GLsizei)width, (GLsizei)height);
	}

    __forceinline void Unbind()
    {
        BindRenderbuffer(RENDERBUFFER, 0);
    }

private:
    GLuint m_rbo;
};
#endif // gl_rbo_h__
