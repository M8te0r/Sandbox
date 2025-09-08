#pragma once
#include "asset_system/shader/Shader.h"
#include "asset_system/texture/Texture.h"
#include "asset_system/mesh/Mesh.h"
#include <map>
#include <string>
#include <memory>
namespace Elysian
{
    class AssetSystem
    {
    public:
        // TODO 搞清楚这个AssetSystem到底是干嘛的
        std::map<std::string, std::shared_ptr<Shader>> shaderAssets;
        std::map<std::string, std::shared_ptr<Texture>> textureAssets;
        std::map<std::string, std::shared_ptr<Mesh>> meshAssets;

    public:
        void initialize();
        void loadShader(const char *vertexPath, const char *fragmentPath, const char *geometryPath, std::string name);
        void loadTexture(const char *path, std::string name);
        void loadTexture(std::vector<std::string> faces, std::string name);
        void loadMesh(std::string name);
        void loadMesh(static_mesh_type type, std::string name);
    };

} // namespace Elysian
