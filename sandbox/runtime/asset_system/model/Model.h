#pragma once
#include <string>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
namespace Elysian
{
    class Model
    {
    public:
        unsigned int ID;

    public:
        Model(std::string const &path);

    private:
        void processNode(aiNode *node, const aiScene *scene);
    };

} // namespace Elysian
