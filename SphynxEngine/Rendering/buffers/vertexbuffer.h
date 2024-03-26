//
// Created by andre on 23.09.22.
//

#ifndef PROG2002_VERTEXBUFFER_H
#define PROG2002_VERTEXBUFFER_H

#include "glad/glad.h"
#include "buffers/bufferlayout.h"

/**
 * Class wrapping a vertex buffer object
 */
class VertexBuffer {
private:
    GLuint m_vertexBufferID; ///< generated ID of vertex buffer
    int m_bufferSize {};
    BufferLayout m_layout;   ///< layout of data with stride

public:
    /**
     * Constructor: WARNING: Binds vertex buffer during construction.
     * @param data - data representing data
     * @param size - size of data in bytes
     */
    //VertexBuffer(const void* data, GLsizei size);
    VertexBuffer(const void *data, const GLsizei &size, BufferLayout layout = {});


    /**
     * Destructor: Deletes buffer data with glDeleteBuffers()
     */
    ~VertexBuffer() { glDeleteBuffers(1, &m_vertexBufferID);};


    /**
     * Binds VBO if it has a valid ID/name
     */
    void bind() const;


    /**
     * Unbinds any bound VBO
     */
    static void unbindVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }


    /**
     *
     * @param offset
     * @param data
     */
    void subData(const GLintptr &offset, const void *data) const;


    /**
     *
     * @return
     */
    const BufferLayout& getLayout() const  {return m_layout;}


    /**
     * Sets layout of data in buffer
     * @param layout - bufferLayout object
     */
    inline void setLayout (const BufferLayout &layout) { m_layout = layout;}

    /**
     * Returns the number of indices in buffer
     * @return
     */
    [[nodiscard]] inline int getSize() const {
        return m_bufferSize;
    }
};

#endif //PROG2002_VERTEXBUFFER_H
