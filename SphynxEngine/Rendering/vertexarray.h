//
// Created by andre on 23.09.22.
//

#ifndef PROG2002_VERTEXARRAY_H
#define PROG2002_VERTEXARRAY_H

#include <glad/glad.h>
#include "shadersdatatype.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>





/**
 * Class wrapping a vertex array object
 *
 */
class VertexArray {
private:
    unsigned m_vertexArrayID {};                                ///< ID of vertex array
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers; ///< Vertex buffers associated with array
    std::shared_ptr<IndexBuffer> m_indexBuffer;                 ///< Index buffer used for drawing

    /// Returns m_vertexBuffers
    [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers() const {return m_vertexBuffers;}

public:
    /**
     * Default constructor
     */
    VertexArray();


    /**
     * Deletes vertex array through glDeleteVertexArrays
     */
    ~VertexArray() { glDeleteVertexArrays(1, &m_vertexArrayID);}


    /**
     *
     */
    void bind() const;


    /**
     * Unbinds any bound vertex array object
     */
    static void unbindVAO(){ glBindVertexArray(0);}


    /**
     *
     * @param buffer
     */
    void addVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer);


    /**
     *
     * @param buffer
     */
    void setIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer);


    /**
     *
     * @return
     */
    [[nodiscard]] inline const std::shared_ptr<IndexBuffer> &getIndexBuffer() const {return m_indexBuffer;}

    [[nodiscard]] inline int getSize() const {
        if(!m_vertexBuffers.empty()) {
            return m_vertexBuffers.back()->getSize();
        } else {
            return 0;
        }
    }
};

#endif //PROG2002_VERTEXARRAY_H
