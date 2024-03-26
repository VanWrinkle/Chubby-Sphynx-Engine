//
// Created by andre on 23.09.22.
//

#ifndef PROG2002_BUFFERLAYOUT_H
#define PROG2002_BUFFERLAYOUT_H

#include "shader/shadersdatatype.h"
#include <string>
#include <vector>


/**
 *
 */
struct bufferAttribute {
    std::string    name;            ///< name of attribute
    shaderDataType type;            ///< data type of attribute
    unsigned       size;            ///< size of attribute in bytes
    unsigned       offset;          ///< offset of attribute in relation to stride
    GLboolean      normalized;      ///<

    bufferAttribute(shaderDataType type, std::string name, GLboolean normalized = false)
            : name(std::move(name)),
            type(type),
            size(shaderDataTypeSize(type)),
            offset(0),
            normalized(normalized)
            {};
};




/**
 *
 */
class BufferLayout {
private:
    GLsizei m_stride;                               ///< stride of buffer in bytes
    std::vector<bufferAttribute> m_attributes;      ///< vector with all the attributes of the buffer


    /// Calculates the total stride of the buffer along with individual offset of each attribute.
    void calculateOffsetAndStride() {
        GLsizei offset = 0;
        m_stride = 0;
        for ( auto &attribute: m_attributes) {
            attribute.offset = offset;
            offset += attribute.size;
            m_stride += attribute.size;
        }
    }

public:
    /**
     *
     */
    BufferLayout() { m_stride = 0;}

    /**
     *
     * @param attributes
     */
    BufferLayout(const std::initializer_list<bufferAttribute> &attributes)
    : m_attributes(attributes),
    m_stride(0)
    {
        calculateOffsetAndStride();
    }

    std::vector<bufferAttribute>::iterator begin() { return m_attributes.begin(); }
    std::vector<bufferAttribute>::iterator end() { return m_attributes.end(); }
    std::vector<bufferAttribute>::const_iterator begin() const {return m_attributes.begin();}
    std::vector<bufferAttribute>::const_iterator end() const {return m_attributes.end();}
    inline const std::vector<bufferAttribute> &getAttributes() const {return m_attributes;}
    inline GLsizei getStride()  const { return m_stride;}


};

#endif //PROG2002_BUFFERLAYOUT_H
