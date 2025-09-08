#include "asset_system/mesh/inner_mesh/Quad.h"
namespace Elysian
{
    Quad::Quad()
    {
        positions = std::vector<glm::vec3>{
            glm::vec3(-1.0f, 1.0f, 0.0f),
            glm::vec3(-1.0f, -1.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 0.0f),

            glm::vec3(1.0f, -1.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 0.0f),
            glm::vec3(-1.0f, -1.0f, 0.0f),
        };
        uvs = std::vector<glm::vec2>{
            glm::vec2(0.0f, 1.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),

            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 0.0f),
        };
        normals = std::vector<glm::vec3>{
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),

            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
        };
        setMesh();
    }

    Quad::Quad(float width, float height)
    {
        positions = std::vector<glm::vec3>{
            glm::vec3(-width, height, 0.0f),
            glm::vec3(-width, -height, 0.0f),
            glm::vec3(width, height, 0.0f),
            glm::vec3(width, -height, 0.0f),
        };
        uvs = std::vector<glm::vec2>{
            glm::vec2(0.0f, 1.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
        };
        setMesh();
    }

} // namespace Elysian
