#include "asset_system/AssetSystem.h"

#include "asset_system/mesh/inner_mesh/Triangle.h"
#include "asset_system/mesh/inner_mesh/Cube.h"
#include "asset_system/mesh/inner_mesh/Quad.h"

namespace Elysian
{
    void AssetSystem::initialize()
    {
    }

    void AssetSystem::loadShader(const char *vertexPath, const char *fragmentPath, const char *geometryPath, std::string name)
    {
        shaderAssets[name] = std::make_shared<Shader>(vertexPath, fragmentPath, geometryPath);
    }
    void AssetSystem::loadTexture(const char *path, std::string name)
    {
        textureAssets[name] = std::make_shared<Texture>(path);
    }
    void AssetSystem::loadTexture(std::vector<std::string> faces, std::string name)
    {
        textureAssets[name] = std::make_shared<Texture>(faces);
    }
    void AssetSystem::loadMesh(std::string name)
    {
        auto tempMesh = std::make_shared<Mesh>();
        tempMesh->setMesh();
        meshAssets[name] = tempMesh;
    }

    void AssetSystem::loadMesh(static_mesh_type type, std::string name)
    {
        switch (type)
        {
        case static_triangle_mesh:
        {
            std::shared_ptr<Mesh> tempMesh = std::make_shared<Triangle>();
            tempMesh->setMesh();
            meshAssets[name] = tempMesh;
            break;
        }
        case static_cube_mesh:
        {
            std::shared_ptr<Mesh> tempMesh = std::make_shared<Cube>();
            tempMesh->setMesh();
            meshAssets[name] = tempMesh;
            break;
        }
        case static_quad_mesh:
        {
            std::shared_ptr<Mesh> tempMesh = std::make_shared<Quad>();
            tempMesh->setMesh();
            meshAssets[name] = tempMesh;
            break;
        }

        default:
            break;
        }
    }
} // namespace Elysian
