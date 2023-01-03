//
// Created by andre on 23.09.22.
//
#include "indexbuffer.h"
#include <iostream>


IndexBuffer::IndexBuffer(const void *data, GLsizei count) : m_indexBufferID(0), m_count(count) {
    glGenBuffers(1, &m_indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned), data, GL_DYNAMIC_DRAW);

}


void IndexBuffer::bind() const{
    if(m_indexBufferID) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
    } else {
        std::cout << "[IBO Error]: Tried to bind invalid IndexBuffer" << std::endl;
    }
}

