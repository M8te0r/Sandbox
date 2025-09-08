#pragma once
#include "glm/glm.hpp"
#include "asset_system/shader/Shader.h"
#include <memory>
#include "asset_system/shader/Shader.h"

namespace Elysian
{
    class Material
    {
    public:
        glm::vec3 albedo;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

    public:
        virtual ~Material() {}

        virtual void setShaderUniforms(std::shared_ptr<Shader> shader);
    };

} // namespace Elysian
