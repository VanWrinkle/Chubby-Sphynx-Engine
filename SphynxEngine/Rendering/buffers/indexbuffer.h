//
// Created by andre on 23.09.22.
//

#ifndef PROG2002_INDEXBUFFER_H
#define PROG2002_INDEXBUFFER_H

#include "glad/glad.h"

/**
 * Class wrapping an index/element buffer
 */
class IndexBuffer {
private:
    GLuint m_indexBufferID; ///< ID of IndexBuffer
    GLuint m_count;         ///< Nr of elements in buffer

public:
    /**
     * Constructor.
     * WARNING: Binds IndexBuffer by default during construction.
     * @param data - pointer to
     * @param count
     */
    IndexBuffer(const void *data, GLsizei count);


    /**
     * Deletes data using glDeleteBuffers()
     */
    inline ~IndexBuffer(){ glDeleteBuffers(1, &m_indexBufferID); }


    /**
     * Binds IndexBuffer
     */
    void bind() const;


    /**
     * Unbinds any bound index buffer object
     */
    static inline void unbindIBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }


    /**
     * @return - nr of elements in buffer
     */
    inline GLuint getCount() const {return m_count;}

};

#endif //PROG2002_INDEXBUFFER_H
