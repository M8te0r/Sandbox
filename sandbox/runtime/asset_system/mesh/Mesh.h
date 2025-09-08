#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"

#include "asset_system/texture/Texture.h"

namespace Elysian
{
    enum static_mesh_type
    {
        static_triangle_mesh,
        static_cube_mesh,
        static_quad_mesh
    };

    class Mesh
    {
    private:
    public:
        // 渲染数据
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        // EBO数据
        std::vector<unsigned int> indices;
        // mesh顶点数据
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;

        // std::vector<Vertex> vertices;
        // std::vector<unsigned int> indices;
        // std::vector<Texture> textures;

    public:
        Mesh();
        void setMesh(bool isInterleaved = true);
    };

} // namespace Elysian
