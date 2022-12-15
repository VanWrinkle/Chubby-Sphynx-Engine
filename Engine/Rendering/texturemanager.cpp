// This is the TextureManager.cpp
#include "texturemanager.h"

#include <iostream>


bool TextureManager::LoadModelTextures( Model &model , const std::string &filePath) {
    for(auto & material : model.materials) {
        if(!material.diffuseTexture.empty()) {
            auto it = m_textures.find(material.diffuseTexture);
            if(it != m_textures.end()) {
                material.diffuseTextureSlot = it->second.unit;
            } else {
                LoadTexture2DRGBA(material.diffuseTexture, filePath+material.diffuseTexture);
                material.diffuseTextureSlot = GetUnitByName(material.diffuseTexture);
            }
        }

        if(!material.specularTexture.empty()) {
            auto it = m_textures.find(material.specularTexture);
            if(it != m_textures.end()) {
                material.specularTextureSlot = it->second.unit;
            } else {
                LoadTexture2DRGBA(material.specularTexture, filePath+material.specularTexture);
                material.specularTextureSlot = GetUnitByName(material.specularTexture);
            }
        }
    }
}

/**
 * Returns the first free or non vital texture unit after deleting the old texture
 * @return
 */
GLuint TextureManager::findTextureUnit(){
    for(int i = 0; i < m_textureUnits.size(); i++) {
        m_unitIndex = ++m_unitIndex % m_textureUnits.size();
        if(!m_textureUnits[m_unitIndex].referenced) {
            if(m_textureUnits[m_unitIndex].id) {
                glDeleteTextures(1, &m_textureUnits[m_unitIndex].id);
                m_textures[m_textureUnits[m_unitIndex].name].uploaded = false;
            }
            return m_unitIndex;
        }
    }
};

bool TextureManager::LoadTexture2DRGBA(const std::string& name, const std::string& filePath, bool mipMap)
{
    auto it = m_textures.find(name);
    if(it != m_textures.end()) {
        return true; // Data already present, won't be reuploaded
    } else {
        int width, height, bpp;
        auto data = this->LoadTextureImage(filePath, width, height, bpp, STBI_rgb_alpha);

        if (!data)
        {
            return false;
        }

        GLuint tex;
        GLuint unit = findTextureUnit();
        glGenTextures(1, &tex);
        glActiveTexture(GL_TEXTURE0 + unit); // Texture Unit
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        if (mipMap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        // Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Texture texture;
        texture.id = tex;
        texture.uploaded = true;
        texture.mipMap = mipMap;
        texture.width = width;
        texture.height = height;
        texture.bpp = bpp;
        texture.name = name;
        texture.filePath = filePath;
        texture.unit = unit;
        texture.type = Texture2D;

        m_textureUnits[unit].id = tex;
        m_textureUnits[unit].name = name;

        this->m_textures.insert({texture.name, texture});

        this->FreeTextureImage(data);

        return true;
    }
}




bool TextureManager::LoadCubeMapRGBA(const std::string& name, const std::string& filePath, bool mipMap)
{
    auto it = m_textures.find(name);
    if(it != m_textures.end()) {
        return true; // Data about texture already present, won't be uploaded anew
    } else {
        int width, height, bpp;
        auto data = this->LoadTextureImage(filePath, width, height, bpp, STBI_rgb_alpha);

        if (!data) {
            return false;
        }


        GLuint tex;
        GLuint unit = findTextureUnit();
        glGenTextures(1, &tex);
        glActiveTexture(GL_TEXTURE0 + unit); // Texture Unit
        glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

        for (unsigned int i = 0; i < 6; i++) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }

        if (mipMap) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }


        // Wrapping
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
        // Filtering
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Texture texture;
        texture.id = tex;
        texture.uploaded = true;
        texture.mipMap = mipMap;
        texture.width = width;
        texture.height = height;
        texture.bpp = bpp;
        texture.name = name;
        texture.filePath = filePath;
        texture.unit = unit;
        texture.type = CubeMap;

        m_textureUnits[unit].id = tex;
        m_textureUnits[unit].name = name;

        this->m_textures.insert({texture.name, texture});

        this->FreeTextureImage(data);


        return true;
    }
}


GLuint TextureManager::GetUnitByName(const std::string& name) const
{
    auto it = m_textures.find(name);
    if(it != m_textures.end()) {
        return it->second.unit;
    }
    return -1;
}

unsigned char* TextureManager::LoadTextureImage(const std::string& filepath, int& width, int& height, int& bpp, int format) const
{
    return stbi_load(filepath.c_str(), &width, &height, &bpp, format);
}


void TextureManager::FreeTextureImage(unsigned char* data) const
{
    if (data)
    {
        stbi_image_free(data);
    }
}
