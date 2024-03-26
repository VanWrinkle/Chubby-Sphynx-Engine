//This is the TextureManager.h file

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

// SphynxEngine / Project headers
#include "modelsystem/model.h"

// External libraries
#include "glad/glad.h"
#include "stb_image.h"

// STD includes
#include <string>
#include <vector>
#include <unordered_map>



class TextureManager
{
public:
    enum TextureType {Texture2D, Texture3D, CubeMap, SkyBox};

    struct Texture
    {
        GLuint id;
        bool uploaded;
        bool mipMap;
        int width, height, bpp;
        std::string name;
        std::string filePath;
        GLuint unit;
        TextureManager::TextureType type;
    };

private:
    struct TextureUnit {
        std::string name;
        GLuint id {};
        bool referenced {};
    };

public:
    static TextureManager* GetInstance()
    {
        return TextureManager::Instance != nullptr ? TextureManager::Instance: TextureManager::Instance = new TextureManager(); }

public:
    bool LoadTexture2DRGBA(const std::string& name, const std::string& filepath, bool mipMap=true);
    bool LoadCubeMapRGBA(const std::string& name, const std::string& filePath, bool mipMap=true);
    bool LoadModelTextures( Model &model , const std::string &filePath);
    GLuint GetUnitByName(const std::string& name) const;

private:
    GLuint findTextureUnit();
    unsigned char* LoadTextureImage(const std::string& filepath, int& width, int& height, int& bpp, int format)const;
    void FreeTextureImage(unsigned char* data) const;

private:
    TextureManager() { m_textureUnits.resize(48);};
    ~TextureManager();
    TextureManager(const TextureManager&) = delete;
    void operator = (const TextureManager&) = delete;

private:
    inline static TextureManager* Instance = nullptr;

private:
    std::unordered_map<std::string, TextureManager::Texture> m_textures;
    std::vector<TextureUnit> m_textureUnits;
    int m_unitIndex {-1};

};

#endif // TEXTUREMANAGER_H_
