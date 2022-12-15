//
// Created by andre on 23.09.22.
//
#include "vertexbuffer.h"
#include <iostream>
#include <utility>


VertexBuffer::VertexBuffer(const void *data, const GLsizei &size, BufferLayout layout) :
                                                                            m_vertexBufferID(0),
                                                                            m_layout(std::move(layout))
{
    m_bufferSize = size;
    glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}


void VertexBuffer::bind() const {
    if(m_vertexBufferID) {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    } else {
        std::cout << "[VBO Error]: Tried to bind invalid VertexBuffer" << std::endl;
    }
};


void VertexBuffer::subData(const GLintptr &offset, const void *data) const {
    glNamedBufferSubData(m_vertexBufferID, offset, sizeof(*(float*)data), data);
};