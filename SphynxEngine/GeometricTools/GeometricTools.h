//
// Created by andre on 14.09.22.
//

#ifndef GEOMETRICTOOLS_H
#define GEOMETRICTOOLS_H

#include <string>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

namespace GeoTools {

    constexpr std::array<float, 3*2> UnitTriangle2D = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};

    constexpr std::array<float, 4*2> UnitRectangle2D = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};

    constexpr std::array<float, 4*11> UnitRectangle3D = {
            -0.5, 0.0f, -0.5,       1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
             0.5, 0.0f, -0.5,       1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
             0.5, 0.0f,  0.5,       1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
            -0.5, 0.0f,  0.5,       1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
    };

    constexpr std::array<unsigned, 6> UnitRectangle3DTopology{
        1, 0, 2, 0, 3, 2
    };



    constexpr std::array<float, 24*11> UnitCubeVertices  = {
            // y face
            -0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
            //-y face
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
            /// -x face
            -0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
            /// x face
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
            // -z face
            -0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f,  0.0f,-1.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f,-1.0f,
            0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f,  0.0f,-1.0f,
            0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    -0.0f,  0.0f,-1.0f,
            /// z face
            0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f,1.0f,
            -0.5f, -0.5f, 0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f,  0.0f,1.0f,
            -0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  0.0f,1.0f,
    };


    constexpr std::array<float, 24*17> UnitCubeVerticesNorm  = {
            // y face
            -0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f, 1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f, 1.0f, 0.0f,    -1.0f, 0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f, 1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f, 1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            //-y face
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            /// -x face
            -0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,     0.0f, -1.0f, 0.0f,      0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,     0.0f, -1.0f, 0.0f,      0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,     0.0f, -1.0f, 0.0f,      0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,     0.0f, -1.0f, 0.0f,      0.0f, 0.0f, 1.0f,
            /// x face
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            // -z face
            -0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f,  0.0f,-1.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f,-1.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f,  0.0f,-1.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  0.0f,-1.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,
            /// z face
            0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f,1.0f,     0.0f, 1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f,  0.0f,1.0f,     0.0f, 1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  0.0f,1.0f,     0.0f, 1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
    };


    constexpr std::array<unsigned, 6*6> UnitCubeTopology = {
            1, 0, 2, 0, 3, 2,
            5, 4, 6, 4, 7, 6,
            9, 8, 10,8, 11,10,
            13,12,14,12,15,14,
            17,16,18,16,19,18,
            21,20,22,20,23,22
    };

    constexpr std::array<unsigned, 8*6> UnitCubeLineTopology = {
            0, 1, 1, 2, 2, 3, 3, 0,
            4, 5, 5, 6, 6, 7, 7, 4,
            8, 9, 9,10,10,11,11, 8,
            12,13,13,14,14,15,15,12,
            16,17,17,18,18,19,19,16,
            20,21,21,22,22,23,23,20
    };


    /**
     * @tparam X
     * @tparam Y
     * @return
     */
    template <unsigned int X, unsigned int Y>
    constexpr std::array<float, X*Y*4* 11> UnitGrid3DVertices() {
        struct Vertex{
            glm::vec3 pos;
            glm::vec3 col;
            glm::vec2 st;
            glm::vec3 nor;
        };
        Vertex v;
        Vertex vertices[X*Y*4];
        float dX = 1.0f / static_cast<float>(X);
        float dY = 1.0f / static_cast<float>(Y);

        for (int i = 0; i < Y; i++) {
            for (int j = 0; j < X; j++) {
                v.pos = { -0.5f + dX * j, -0., -0.5f + dY * i};
                v.col = {1.0f, 1.0f, 1.0f};
                v.st = {0.0f, 0.0f};
                v.nor = {0.0f, 1.0f, 0.0f};
                vertices[i*X*4 + (j*4)] = v;
                v.pos = { -0.5f + dX * j, -0., -0.5f + dY * (i+1)};
                v.st = {0.0f, 1.0f};
                vertices[i*X*4 + (j*4)+1] = v;
                v.pos = { -0.5f + ((j==X-1)? 1.0f : (dX * (j+1))), -0., -0.5f + dY * (i+1)};
                v.st = {1.0f, 1.0f};
                vertices[i*X*4 + (j*4)+2] = v;
                v.pos = { -0.5f + ((j==X-1)? 1.0f : (dX * (j+1))), -0., -0.5f + dY * i};
                v.st = {1.0f, 0.0f};
                vertices[i*X*4 + (j*4)+3] = v;
            }
        }
        std::array<float, X*Y*4*11> ret;
        memcpy(ret.data(), (float*)vertices, sizeof(vertices));
        return ret;
    };

    /**
     * @tparam X
     * @tparam Y
     * @return
     */
    template <unsigned int X, unsigned int Y>
    constexpr std::array<float, X*Y*4* 17> UnitGrid3DVerticesNorm() {
        struct Vertex{
            glm::vec3 pos;
            glm::vec3 col;
            glm::vec2 st;
            glm::vec3 nor;
            glm::vec3 tangent;
            glm::vec3 bitangent;
        };
        Vertex v;
        Vertex vertices[X*Y*4];
        float dX = 1.0f / static_cast<float>(X);
        float dY = 1.0f / static_cast<float>(Y);


        for (int i = 0; i < Y; i++) {
            for (int j = 0; j < X; j++) {
                v.pos = { -0.5f + dX * j, -0., -0.5f + dY * i};
                v.col = {1.0f, 1.0f, 1.0f};
                v.st = {0.0f, 0.0f};
                v.nor = {0.0f, 1.0f, 0.0f};
                v.tangent = { 1.0f, 0.0f, 0.0f};
                v.bitangent = {0.0f, 0.0f, -1.0f};
                vertices[i*X*4 + (j*4)] = v;
                v.pos = { -0.5f + dX * j, -0., -0.5f + dY * (i+1)};
                v.st = {0.0f, 1.0f};
                vertices[i*X*4 + (j*4)+1] = v;
                v.pos = { -0.5f + ((j==X-1)? 1.0f : (dX * (j+1))), -0., -0.5f + dY * (i+1)};
                v.st = {1.0f, 1.0f};
                vertices[i*X*4 + (j*4)+2] = v;
                v.pos = { -0.5f + ((j==X-1)? 1.0f : (dX * (j+1))), -0., -0.5f + dY * i};
                v.st = {1.0f, 0.0f};
                vertices[i*X*4 + (j*4)+3] = v;
            }
        }
        std::array<float, X*Y*sizeof(Vertex)> ret;
        memcpy(ret.data(), (float*)vertices, sizeof(vertices));
        return ret;
    };

    /**
     * Creates an array with indexes for a corresponding UnitGridGeometry2D array
     *
     * @tparam X
     * @tparam Y
     * @return
     */
    template<unsigned int X, unsigned int Y>
    constexpr std::array<unsigned int, 6 * X * Y> UnitGridIndices () {
        std::array<unsigned int,6 * X*Y> ret;
        for(int i = 0; i < X*Y; i++) {
            ret[i*6] = 0 + i*4;
            ret[i*6+1] = 1 + i*4;
            ret[i*6+2] = 2 + i*4;
            ret[i*6+3] = 3 + i*4;
            ret[i*6+4] = 0 + i*4;
            ret[i*6+5] = 2 + i*4;
        }
        return ret;
    }

    /**
     * Creates an array with indexes for a corresponding UnitGridGeometry2D array
     *
     * @tparam X
     * @tparam Y
     * @return
     */
    template<unsigned int X, unsigned int Y>
    constexpr std::array<unsigned int, 8 * X * Y> UnitGridLineIndices () {
        std::array<unsigned int, 8 * X*Y> ret;
        for(int i = 0; i < X*Y; i++) {
            ret[i*8] = 0 + i*4;
            ret[i*8+1] = 1 + i*4;
            ret[i*8+2] = 1 + i*4;
            ret[i*8+3] = 2 + i*4;
            ret[i*8+4] = 2 + i*4;
            ret[i*8+5] = 3 + i*4;
            ret[i*8+6] = 3 + i*4;
            ret[i*8+7] = 0 + i*4;
        }
        return ret;
    }


    /**
     * @tparam X
     * @tparam Y
     * @return
     */
    template <unsigned int X, unsigned int Y>
    std::array<float, (Y+1) * (X+1) * 11> UnitGridGeometry3DChessVersion() {
        std::array<float, (Y+1) * (X+1) * 11> ret;
        glm::vec3 positions[Y+1][X+1];
        float dX = 1.0f / static_cast<float>(X);
        float dY = 1.0f / static_cast<float>(Y);
        int block = 0;
        int nrElements = 11; // vec3 pos, vec3 col, vec2 uv, vec3 normals
        for (int i = 0; i < Y+1; i++) {
            if(X%2)block++;
            for (int j = 0; j < X+1; j++) { // X = 4
                int offset = (nrElements*(X+1))*i + j*nrElements;
                ret[offset] = -0.5f + dX * j;  // x koordinat
                ret[offset+1] = -0.5f + dY * i;// y koordinat
                ret[offset+2] = 0.0f;//-floor(5.0f* dY * i)*1.0f+5 -floor(5.0f* dX * j)*1.0f;//-rand_f();     // Z koordinat
                if(dX * i > 0.5f) ret[offset+2] = 0.0f;
                positions[i][j] = glm::vec3(ret[offset], ret[offset+1], ret[offset+2]);
                float col = (block%2)? 0.0f : 1.0f;
                block++;
                ret[offset+3] = col;
                ret[offset+4] = col;
                ret[offset+5] = col;
                ret[offset+6] = dX * j; // Texture coordinates
                ret[offset+7] = dY * i;
                ret[offset+8] = 0.0f; //normals
                ret[offset+9] = 0.0f;
                ret[offset+10] = 0.0f;
            }
        }

        // Calculation of vertex normals based on the surrounding face normals
        for(int i = 0;  i < Y+1; i++) {
            for (int j = 0; j < X+1; j++) {

                glm::vec3 v0, v1, v2, v3, v4, v5;

                if(j != 0)          v0 = positions[i][j-1] - positions[i][j];
                if(i != Y)          v1 = positions[i+1][j] - positions[i][j];
                if(i!= Y && j != X) v2 = positions[i+1][j+1] - positions[i][j];
                if(j!=X)            v3 = positions[i][j+1]  - positions[i][j];
                if(i!= 0)           v4 = positions[i-1][j] - positions[i][j];
                if(j!= 0 && i != 0) v5 = positions[i-1][j-1] - positions[i][j];

                std::vector<glm::vec3> normals;

                if(j != 0 && i != Y) normals.push_back(glm::normalize(glm::cross(v1, v0)));
                if(i != Y && j!= X) {
                    normals.push_back(glm::normalize(glm::cross(v2, v1)));
                    normals.push_back(glm::normalize(glm::cross(v3, v2)));
                }
                if(i != 0 && j != X) normals.push_back(glm::normalize(glm::cross(v4, v3)));
                if(i != 0 && j != 0) {
                    normals.push_back(glm::normalize(glm::cross(v5, v4)));
                    normals.push_back(glm::normalize(glm::cross(v0, v5)));
                }

                glm::vec3 normal(0.0f, 0.0f, 0.0f);
                for(auto const &n : normals) {
                    normal += n;
                }
                normal = glm::normalize(normal);
                int offset = (nrElements*(X+1))*i + j*nrElements;
                ret[offset+8] = normal.x;
                ret[offset+9] = normal.y;
                ret[offset+10] = normal.z;
            }
        }
        return ret;
    };
}

#endif //GEOMETRICTOOLS_H
