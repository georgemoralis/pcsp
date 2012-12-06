#ifndef gl_ibo_h__
#define gl_ibo_h__

#include "gl_BufferObject.h"

class gl_IndexBufferObject : public gl_BufferObject< gl_Core::ELEMENT_ARRAY_BUFFER >
{
public:
    gl_IndexBufferObject()
    {
    }

    ~gl_IndexBufferObject()
    {
        if (m_active_ibo == m_id)
        {
            Unbind();
        }
    }

    __forceinline void Bind()
    {
        m_active_ibo = gl_BufferObject::Bind();
    }

    __forceinline void Unbind()
    {
        assert(m_active_ibo == m_id);

        m_active_ibo = gl_BufferObject::Unbind();
    }

    __forceinline void Bind(void *data, u32 size)
    {
        Bind();
        BufferData(ELEMENT_ARRAY_BUFFER, size, data, DYNAMIC_DRAW);
    }

    __forceinline void Bind(u32 size)
    {
        Bind(0, size);
    }

    __forceinline void *Map(u32 size)
    {
        assert(m_active_ibo == m_id);

        return gl_BufferObject::Map(size);
    }

    __forceinline void Unmap()
    {
        assert(m_active_ibo == m_id);

        gl_BufferObject::Unmap();
    }

private:
    static GLuint m_active_ibo;
};

weaksymbol GLuint gl_IndexBufferObject::m_active_ibo = 0;

#endif // gl_ibo_h__
