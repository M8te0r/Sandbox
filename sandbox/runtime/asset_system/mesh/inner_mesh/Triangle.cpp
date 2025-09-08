#include "asset_system/mesh/inner_mesh/Triangle.h"
namespace Elysian
{
    Triangle::Triangle()
    {
        positions = std::vector<glm::vec3>{
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(0.0f, 0.5f, 0.0f),

            // 直角
            // glm::vec3(0.5f, 0.0f, 0.0f),
            // glm::vec3(0.0f, 0.5f, 0.0f),
            // glm::vec3(0.0f, 0.0f, 0.0f),
        };

        uvs = std::vector<glm::vec2>{
            glm::vec2(0.5f, -0.5f),
            glm::vec2(-0.5f, -0.5f),
            glm::vec2(0.0f, 0.5f),
        };

        normals = std::vector<glm::vec3>{
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
        };

        setMesh();
    }
} // namespace Elysian
