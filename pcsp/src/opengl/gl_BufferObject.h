#ifndef gl_bo_h__
#define gl_bo_h__

#include "gl_Core.h"

template< GLenum type > class gl_BufferObject : protected gl_Core
{
protected:
    gl_BufferObject()
    :   m_id(0)
    {
        GenBuffers(1, &m_id);
    }

    ~gl_BufferObject()
    {
        DeleteBuffers(1, &m_id);
    }

    __forceinline GLuint Bind()
    {
        BindBuffer(type, m_id);
        return m_id;
    }

    __forceinline GLuint Unbind()
    {
        BindBuffer(type, 0);
        return 0;
    }

    __forceinline void *Map(u32 size)
    {
        BufferData(type, size, 0, DYNAMIC_DRAW);
        return (void *)MapBuffer(type, WRITE_ONLY);
    }

    __forceinline void Unmap()
    {
        UnmapBuffer(type);
    }

    GLuint   m_id;
};

#endif // gl_bo_h__
