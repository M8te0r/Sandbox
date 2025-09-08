#include "asset_system/model/Model.h"
#include <iostream>

namespace Elysian
{
    Model::Model(std::string const &path)
    {
        // 使用ASSIMP读取文件
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // 检查错误
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        // 获取文件所在的文件夹路径
        // directory = path.substr(0, path.find_last_of('/'));

        // 递归的处理assimp中的根节点
        processNode(scene->mRootNode, scene);
    }

    // 以递归方式处理节点。处理位于节点处的每个单独网格，并在其子节点（如果有）上重复此过程。
    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        // 处理当前节点下的所有mesh
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // node中只包含场景中物体的索引，用于组织场景中物体的关系。scene中包含所有实在的数据
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            // 获取mesh
            // meshes.push_back(processMesh(mesh, scene));
        }
        // 继续递归的处理child
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
} // namespace Elysian
