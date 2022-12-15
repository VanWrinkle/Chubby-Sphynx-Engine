//
// Created by andre on 07.12.22.
//

#ifndef PROG2002_MODEL_H
#define PROG2002_MODEL_H


// Engine / project headers
#include "modelmatrix.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "shader.h"

//External
#include <tiny_obj_loader.h>

//STD
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cassert>

/**
 * Struct for use with the Model class.
 */
struct Material {
    std::string diffuseTexture;
    glm::vec3   diffuseColor {1.0};
    std::string specularTexture;
    glm::vec3   specularColor {1.0};
    float shininess {32};
    int diffuseTextureSlot {-1};
    int specularTextureSlot {-1};
};

/**
 * Wrapper for a mesh model with name, VertexArray pointer pointing to its vertices and indices,
 * as well as its materials. Inherits the ModelMatrix class
 * @see ModelMatrix class
 */
struct Model : public ModelMatrix {
    std::string name;                           ///< Model name
    std::shared_ptr<VertexArray> vao;           ///< VertexArray for draw calls
    std::vector<Material> materials;            ///< Materials organized by ID 0 and upwards

    Model() = default;

    template <unsigned long X, unsigned long Y>
    Model(const std::array<float, X> &vertexData, const std::array<unsigned, Y> &indices,
          const BufferLayout & bufferLayout, const Material &material = {}){

        vao = std::make_shared<VertexArray>();
        auto vbo = std::make_shared<VertexBuffer>(vertexData.data(), sizeof(vertexData), bufferLayout);
        auto ibo = std::make_shared<IndexBuffer>(indices.data(), indices.size());
        vao->setIndexBuffer(ibo);
        vao->addVertexBuffer(vbo);
        materials.push_back(material);
    };

    template <unsigned long long X, unsigned long long Y>
    Model(const std::array<float, X> &vertexData, const std::array<unsigned, Y> &indices,
          const BufferLayout & bufferLayout, const Material &material = {}){

        vao = std::make_shared<VertexArray>();
        auto vbo = std::make_shared<VertexBuffer>(vertexData.data(), sizeof(vertexData), bufferLayout);
        auto ibo = std::make_shared<IndexBuffer>(indices.data(), indices.size());
        vao->setIndexBuffer(ibo);
        vao->addVertexBuffer(vbo);
        materials.push_back(material);
    };

    /**
     * Uploads a Models uniforms to a given shader
     * @param shader - target of uniform upload
     */
    void upload(Shader &shader) {
        int materialSlots = 5;
        for (int i = 0; i < materials.size() && i < materialSlots; i++) {
            shader.uploadUniformInt(std::string("u_matDiffuse[" + std::to_string(i) + "]"),
                                    materials[i].diffuseTextureSlot);
            shader.uploadUniformInt(std::string("u_matSpecular[" + std::to_string(i) + "]"),
                                    materials[i].specularTextureSlot);
            shader.uploadUniformVec3(std::string("u_materials[" + std::to_string(i) + "].diffuseCol"),
                                     materials[i].diffuseColor);
            shader.uploadUniformVec3(std::string("u_materials[" + std::to_string(i) + "].specularCol"),
                                     materials[i].specularColor);
            shader.uploadUniformFloat(std::string("u_materials[" + std::to_string(i) + "].shininess"),
                                      materials[i].shininess);
            shader.uploadUniformMat4("u_modelMatrix", this->getMatrix());
            shader.uploadUniformMat3("u_normalMatrix", this->getNormalMatrix());
        }
    }
};



/**
 * Container for the Model class, handling loading of .obj/.mtl files, storage of Model objects
 * and uploading uniforms of each Model to a given shader.
 */
class ModelManager {
private:
    std::unordered_map<std::string, Model> m_models;
    tinyobj::ObjReader m_reader;
    tinyobj::ObjReaderConfig m_readerConfig;

public:
    ModelManager() {
        m_readerConfig.triangulate = true;
        m_readerConfig.vertex_color = true;
    }

    /**
     * Loads models from a given .obj/.mtl file. Each separate mesh will be given a
     * Model wrapper and inserted into the MonelManagers container.
     * @param path
     * @param fileName
     */
    void loadModelsFromObj(const std::string &path, const std::string &fileName) {

        struct Vertex {
            float data[12] = {};
        };

        if( !m_reader.ParseFromFile(path + fileName, m_readerConfig)) {
            if( !m_reader.Error().empty()) {
                std::cout << "[tiny_obj_reader Error]: " << m_reader.Error();
            }
        }
        if(!m_reader.Warning().empty()) {
            std::cout << "[tiny_obj_reader Error]: " << m_reader.Warning();
        }

        auto& attrib = m_reader.GetAttrib();
        auto& shapes = m_reader.GetShapes();
        auto& materials = m_reader.GetMaterials();

        int vertexCount = 0;
        int previousVertCount = 0;

        for(const auto & shape : shapes) {

            int duplicates = 0;
            int largest = 0;
            for(auto const index : shape.mesh.indices) {
                if(index.vertex_index > largest) largest = index.vertex_index;
            }
            vertexCount = (largest + 1) - vertexCount;

            std::vector<Vertex> vertices;
            vertices.resize(vertexCount*2);

            std::vector<unsigned> freemap;
            freemap.resize(vertexCount, 0);

            std::vector<unsigned> indices;

            std::set<int> matIDs;

            unsigned offset = 0;

            //Iterating through faces for one model
            for(int j = 0; j < shape.mesh.num_face_vertices.size(); j++) {
                unsigned faceVertices = shape.mesh.num_face_vertices[j];
                //Iterating through data for one face
                for(int k = 0; k < faceVertices; k++) {
                    tinyobj::index_t idx = shape.mesh.indices[offset + k]; // Index of current vertex

                    Vertex v;
                    v.data[11] = -1;
                    //Position
                    memcpy(v.data, &attrib.vertices[3 * size_t(idx.vertex_index)], sizeof(float)*3);
                    //Color
                    memcpy(&v.data[3], &attrib.colors[3*size_t(idx.vertex_index)], sizeof(float)*3);
                    //st
                    if (idx.texcoord_index >= 0) {
                        v.data[6]= attrib.texcoords[2 * size_t(idx.texcoord_index)];
                        v.data[7] = 1.0f - attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    }
                    //normal
                    if (idx.normal_index >= 0) {
                        memcpy(&v.data[8], &attrib.normals[3 * size_t(idx.normal_index)], sizeof(float)*3);
                    }
                    // the material ID of the current face placed in provokingq vertex
                    v.data[11] = shape.mesh.material_ids[j];
                    matIDs.insert(v.data[11]);


                    if(!freemap[idx.vertex_index - previousVertCount]) {
                        vertices[idx.vertex_index - previousVertCount] = v;
                        indices.push_back(idx.vertex_index - previousVertCount);
                        freemap[idx.vertex_index - previousVertCount] = 1;
                    } else if (memcmp(&vertices[idx.vertex_index - previousVertCount], v.data, sizeof(float) * 12) != 0) {
                        bool found = false;
                        for(int i = vertexCount; i < vertexCount + duplicates; i++) {
                            if(memcmp(&vertices[i - previousVertCount], v.data, sizeof(float) * 12) == 0) {
                                indices.push_back(i);
                                found = true;
                                break;
                            }
                        }
                        if(!found) {
                            vertices[vertexCount + duplicates] = v;
                            indices.push_back(vertexCount + duplicates++);
                            if(vertexCount + duplicates >= vertices.size()) {
                                vertices.resize(vertexCount + duplicates * 2);
                            }
                        }
                    } else {
                        indices.push_back(idx.vertex_index - previousVertCount);
                    }
                }
                offset += faceVertices;
            }

            BufferLayout layout({{shaderDataType::Float3, "position"},
                                 {shaderDataType::Float3, "color"},
                                 {shaderDataType::Float2, "texcoord"},
                                 {shaderDataType::Float3, "normal"},
                                 {shaderDataType::Float,  "matID"}});

            std::vector<int> idOffset;
            for( const auto & id : matIDs) {
                idOffset.push_back(id);
            }

            for(int i = 0; i < vertexCount+duplicates; i++) {
                for(int j = 0; j < idOffset.size(); j++) {
                    if(idOffset[j] == vertices[i].data[11]) {
                        vertices[i].data[11] = j;
                        break;
                    }
                }
            }

            auto vao = std::make_shared<VertexArray>();
            auto vbo = std::make_shared<VertexBuffer>(vertices.data(), (vertexCount + duplicates)*12*4, layout);
            auto ibo = std::make_shared<IndexBuffer>(indices.data(), indices.size());

            vao->setIndexBuffer(ibo);
            vao->addVertexBuffer(vbo);

            Model model;
            model.name = shape.name;
            model.vao = vao;

            for( const auto & id : matIDs ) {
                auto & material =  materials[id];
                Material m;
                m.diffuseColor = {material.diffuse[0], material.diffuse[1], material.diffuse[2]};
                m.diffuseTexture = material.diffuse_texname;
                m.specularColor = {material.specular[0], material.specular[1], material.specular[2]};
                m.specularTexture = material.specular_texname;
                m.shininess = material.shininess;
                model.materials.push_back(m);
            }

            m_models.insert({model.name, model});
            previousVertCount = vertexCount;
        }
    };

    /**
     * Adds a model with the given name, vao and materials.
     * @param name - model name
     * @param vao - VertexArray
     * @param materials - Make sure materials are ordered by ID in ascending order
     */
    void addModel(const std::string &name, const std::shared_ptr<VertexArray> &vao,
                  const std::vector<Material> & materials = {Material()}) {
        Model m;
        m.name = name;
        m.vao = vao;
        for (const auto &material: materials) {
            m.materials.push_back(material);
        }
        m_models.insert({name, m});
    }

    /**
     * Returns reference to pair<name, Model> of named Model if valid
     * @param name - name of Model
     * @return - reference to named Model
     */
    Model &operator[](const std::string &name) {
        return m_models[name];
    }

    inline void addModel(const std::string &name, const Model &model) {
        m_models.insert({name, model});
    }

    std::unordered_map<std::string, Model>::iterator begin() { return m_models.begin(); }
    std::unordered_map<std::string, Model>::iterator end() { return m_models.end(); }
    std::unordered_map<std::string, Model>::const_iterator begin() const { return m_models.begin(); }
    std::unordered_map<std::string, Model>::const_iterator end() const { return m_models.end(); }

};

#endif //PROG2002_MODEL_H
