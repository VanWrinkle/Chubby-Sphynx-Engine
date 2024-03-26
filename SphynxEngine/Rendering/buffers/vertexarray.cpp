//
// Created by andre on 23.09.22.
//
#include "vertexarray.h"
#include <iostream>

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);
}


void VertexArray::bind() const {
    if(m_vertexArrayID) {
        glBindVertexArray(m_vertexArrayID);
    } else {
        std::cout << "[VAO Error] Attempted to bind invalid VertexArray" << std::endl;
    }
}


void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer){
    bind();
    m_vertexBuffers.push_back(buffer);
    m_vertexBuffers.back()->bind();
    int index = 0;
    for(auto &attribute : buffer->getLayout()) {
        glVertexAttribPointer(index,
                              shaderDataTypeComponentCount(attribute.type),
                              shaderDataTypeToOpenGLBaseType(attribute.type),
                              attribute.normalized,
                              buffer->getLayout().getStride(), (void*)attribute.offset
                              );
        glEnableVertexAttribArray(index);
        index++;
    }
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer){
    this->bind();
    buffer->bind();
    m_indexBuffer = buffer;
}
