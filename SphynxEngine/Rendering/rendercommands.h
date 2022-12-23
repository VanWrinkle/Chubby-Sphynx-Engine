//
// Created by anmar on 10/1/2022.
//

#ifndef PROG2002_RENDERCOMMANDS_H
#define PROG2002_RENDERCOMMANDS_H

#include <glad/glad.h>
#include "indexbuffer.h"
#include "vertexarray.h"
#include <glm/glm.hpp>

namespace RenderCommands {

    // Turns off rendering of back faces
    inline void enableFaceCulling() { glEnable(GL_CULL_FACE); }

    // Enables rendering of back faces
    inline void disableFaceCulling() { glDisable(GL_CULL_FACE); }

    inline void enableDepthTest() { glEnable(GL_DEPTH_TEST); }

    inline void disableDepthTest() { glDisable(GL_DEPTH_TEST); }


    inline void clear(GLuint mode = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) { glClear(mode); }

    inline void setPolygonMode(const GLenum &face, const GLenum &mode) {glPolygonMode(face, mode); }

    inline void drawIndex(const std::shared_ptr<VertexArray>& vao, const GLenum &primitive) {
        vao->bind();
        glDrawElements(primitive, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }

    inline void drawArray(const std::shared_ptr<VertexArray>& vao, const GLenum &primitive) {
        vao->bind();
        glDrawArrays(primitive, 0, vao->getSize());
    }

    inline int getMaxFragmentTextureUnits(){
        int max;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max);
        return max;
    }

    inline int getMaxTotalTextureUnits(){
        int max;
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
        return max;
    }

    inline void setWireframeMode() {glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    inline void setSolidMode() {glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

    inline void setClearColor( const glm::vec3 &col ) { glClearColor(col[0], col[1], col[2], 1.0f); }

    inline void enableAlphaMode() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    inline void disableAlphaMode() {
        glDisable(GL_BLEND);
    }
}


#endif //PROG2002_RENDERCOMMANDS_H
