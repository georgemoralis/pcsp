#ifndef gl_vbo_h__
#define gl_vbo_h__

#include "gl_BufferObject.h"
#include "gl_Attributes.h"

class gl_VertexBufferObject : public gl_BufferObject< gl_Core::ARRAY_BUFFER >
{
public:
    gl_VertexBufferObject()
    {
    }

    ~gl_VertexBufferObject()
    {
        if (m_active_vbo == m_id)
        {
            Unbind();
        }
    }

    __forceinline void Bind()
    {
        m_active_vbo = gl_BufferObject::Bind();
    }

    __forceinline void Unbind()
    {
        assert(m_active_vbo == m_id);

        m_active_vbo = gl_BufferObject::Unbind();
    }

    __forceinline void Bind(u32 size)
    {
        Bind(0, size);
    }

    __forceinline void Bind(void *data, u32 size)
    {
        Bind();
        BufferData(ARRAY_BUFFER, size, data, DYNAMIC_DRAW);
    }

    __forceinline void Bind(void *data, u32 offset, u32 size)
    {
        Bind();
        BufferSubData(ARRAY_BUFFER, offset, size, data);
    }

    __forceinline void *Map(u32 size)
    {
        assert(m_active_vbo == m_id);

        return gl_BufferObject::Map(size);
    }

    __forceinline void Unmap()
    {
        assert(m_active_vbo == m_id);

        gl_BufferObject::Unmap();
    }

    __forceinline void SetTexCoordPointer(u32 size, u32 type, u32 stride, u32 offset)
    {
        assert(m_active_vbo == m_id);

        TexCoordPointer(GLint(size), GLenum(type), GLsizei(stride), (GLvoid const *)offset);
        EnableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    __forceinline void SetColorPointer(u32 size, u32 type, u32 stride, u32 offset)
    {
        assert(m_active_vbo == m_id);

        ColorPointer(GLint(size), GLenum(type), GLsizei(stride), (GLvoid const *)offset);
        EnableClientState(GL_COLOR_ARRAY);
    }

    __forceinline void SetVertexPointer(u32 size, u32 type, u32 stride, u32 offset)
    {
        assert(m_active_vbo == m_id);

        VertexPointer(GLint(size), GLenum(type), GLsizei(stride), (GLvoid const *)offset);
        EnableClientState(GL_VERTEX_ARRAY);
    }

    __forceinline void SetNormalPointer(u32 type, u32 stride, u32 offset)
    {
        assert(m_active_vbo == m_id);

        NormalPointer(GLenum(type), GLsizei(stride), (GLvoid const *)offset);
        EnableClientState(GL_NORMAL_ARRAY);
    }

    __forceinline void SetWeightPointer(u32 size, u32 type, u32 stride, u32 offset)
    {
        assert(m_active_vbo == m_id);

        glWeightPointerARB(GLint(size), GLenum(type), GLsizei(stride), (GLvoid *)offset);
        EnableClientState(GL_WEIGHT_ARRAY_ARB);
    }

    __forceinline void SetVertexAttribPointer(u32 id, u32 size, u32 type, bool normalized, u32 stride, u32 offset)
    {
        assert(m_active_vbo == m_id);

        glVertexAttribPointer(GLuint(id), GLint(size), GLenum(type), GLboolean(normalized), GLsizei(stride), (GLvoid const *)offset);
        glEnableVertexAttribArray(GLuint(id));
    }

    __forceinline void UnsetTexCoordPointer()
    {
        assert(m_active_vbo == m_id);

        DisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    __forceinline void UnsetColorPointer()
    {
        assert(m_active_vbo == m_id);

        DisableClientState(GL_COLOR_ARRAY);
    }

    __forceinline void UnsetVertexPointer()
    {
        assert(m_active_vbo == m_id);

        DisableClientState(GL_VERTEX_ARRAY);
    }

    __forceinline void UnsetNormalPointer()
    {
        assert(m_active_vbo == m_id);

        DisableClientState(GL_NORMAL_ARRAY);
    }

    __forceinline void UnsetWeightPointer()
    {
        assert(m_active_vbo == m_id);

        DisableClientState(GL_WEIGHT_ARRAY_ARB);
    }

    __forceinline void UnsetVertexAttribPointer(u32 id)
    {
        assert(m_active_vbo == m_id);

        glDisableVertexAttribArray(GLuint(id));
    }

    __forceinline void DrawPrimitiveArray(u32 type, u32 count)
    {
        assert(m_active_vbo == m_id);
        assert(type < 7);

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

private:
    static GLuint m_active_vbo;
};

weaksymbol GLuint gl_VertexBufferObject::m_active_vbo = 0;

#endif // gl_vbo_h__
