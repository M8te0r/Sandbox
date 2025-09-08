#include "asset_system/mesh/Mesh.h"

// TODO 要将该页的gl指令迁移，去耦合

#include "glad/glad.h"

namespace Elysian
{
    Mesh::Mesh()
    {
    }

    // void Mesh::setupMesh()
    // {

    //     // create buffers/arrays
    //     glGenVertexArrays(1, &VAO);
    //     glGenBuffers(1, &VBO);
    //     glGenBuffers(1, &EBO);

    //     glBindVertexArray(VAO);
    //     // 将数据载入进vertex buffer中
    //     glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //     // structs的一个优点是，它们的内存布局对所有项都是顺序的。
    //     // 其效果是，我们可以简单地将指针传递到structs，它可以完美地转换为glm:：vec3/2数组，该数组再次转换为3/2浮点，该浮点转换为字节数组。
    //     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //     // 设置顶点数组
    //     // 顶点坐标
    //     glEnableVertexAttribArray(0);
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    //     // 顶点法线
    //     glEnableVertexAttribArray(1);
    //     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    //     // 顶点纹理坐标
    //     glEnableVertexAttribArray(2);
    //     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
    //     // 顶点切线u（TBN空间）
    //     glEnableVertexAttribArray(3);
    //     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));
    //     // 顶点副切线v（TBN空间）
    //     glEnableVertexAttribArray(4);
    //     glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));
    //     // ids
    //     glEnableVertexAttribArray(5);
    //     glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void *)offsetof(Vertex, m_BoneIDs));

    //     // weights
    //     glEnableVertexAttribArray(6);
    //     glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, m_Weights));
    //     glBindVertexArray(0);
    // }

    // TODO mesh中的buffer和vertex操作需要解耦，单独拎出来

    // 设置mesh，默认为交错存取数据
    void Mesh::setMesh(bool isInterleaved)
    {
        // 如果之前未配置过，则创建VAO对象
        if (!VAO)
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
        }

        std::vector<float> data;

        // 数据存取（交错/连续）
        if (isInterleaved)
        {
            // 交错存取
            for (int i = 0; i < positions.size(); ++i)
            {
                data.push_back(positions[i].x);
                data.push_back(positions[i].y);
                data.push_back(positions[i].z);
                if (uvs.size() > 0)
                {
                    data.push_back(uvs[i].x);
                    data.push_back(uvs[i].y);
                }
                if (normals.size() > 0)
                {
                    data.push_back(normals[i].x);
                    data.push_back(normals[i].y);
                    data.push_back(normals[i].z);
                }
                if (tangents.size() > 0)
                {
                    data.push_back(tangents[i].x);
                    data.push_back(tangents[i].y);
                    data.push_back(tangents[i].z);
                }
                if (bitangents.size() > 0)
                {
                    data.push_back(bitangents[i].x);
                    data.push_back(bitangents[i].y);
                    data.push_back(bitangents[i].z);
                }
            }
        }
        else
        {
            // 连续存取
            for (int i = 0; i < positions.size(); ++i)
            {
                data.push_back(positions[i].x);
                data.push_back(positions[i].y);
                data.push_back(positions[i].z);
            }
            for (int i = 0; i < uvs.size(); ++i)
            {
                data.push_back(uvs[i].x);
                data.push_back(uvs[i].y);
            }
            for (int i = 0; i < normals.size(); ++i)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
            for (int i = 0; i < tangents.size(); ++i)
            {
                data.push_back(tangents[i].x);
                data.push_back(tangents[i].y);
                data.push_back(tangents[i].z);
            }
            for (int i = 0; i < bitangents.size(); ++i)
            {
                data.push_back(bitangents[i].x);
                data.push_back(bitangents[i].y);
                data.push_back(bitangents[i].z);
            }
        }
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // auto tempDataSize = (data.size() - 1) * sizeof(float) + sizeof(int);//5个
        // glBufferData(GL_ARRAY_BUFFER, tempDataSize, &data[0], GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

        // TODO 使用EBO渲染
        if (indices.size() > 0)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        }
        // 数据读取（交错/连续）
        // x,y,z,u,v,nx,ny,nz; x,y
        if (isInterleaved)
        {
            // 整个data的长度
            // 使用sizeof(data)返回的长度是不准确的，是vector容器预先分配的指针大小
            size_t stride = 0ul;
            if (positions.size() > 0)
                stride += 3 * sizeof(float);
            if (uvs.size() > 0)
                stride += 2 * sizeof(float);
            if (normals.size() > 0)
                stride += 3 * sizeof(float);
            if (tangents.size() > 0)
                stride += 3 * sizeof(float);
            if (bitangents.size() > 0)
                stride += 3 * sizeof(float);

            size_t offset = 0;
            // 设置顶点数组

            if (positions.size() > 0)
            { // 顶点坐标
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
                offset += 3 * sizeof(float);
            }
            if (uvs.size() > 0)
            { // 顶点纹理坐标
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)offset);
                offset += 2 * sizeof(float);
            }
            if (normals.size() > 0)
            {
                // 顶点法线
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void *)offset);
                offset += 3 * sizeof(float);
            }
            if (tangents.size() > 0)
            {
                // 顶点切线u（TBN空间）
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void *)offset);
                offset += 3 * sizeof(float);
            }
            if (bitangents.size() > 0)
            {
                // 顶点副切线v（TBN空间）
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void *)offset);
                offset += 3 * sizeof(float);
            }
            glBindVertexArray(0);
        }
        else
        {
            size_t offset = 0;
            if (positions.size() > 0)
            {
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
                offset += positions.size() * sizeof(float);
            }
            if (uvs.size() > 0)
            {
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)offset);
                offset += uvs.size() * sizeof(float);
            }
            if (normals.size() > 0)
            {
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)offset);
                offset += normals.size() * sizeof(float);
            }
            if (tangents.size() > 0)
            {
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)offset);
                offset += tangents.size() * sizeof(float);
            }
            if (bitangents.size() > 0)
            {
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void *)offset);
                offset += bitangents.size() * sizeof(float);
            }
            // 解绑
            glBindVertexArray(0);
        }
    }
} // namespace Elysian
