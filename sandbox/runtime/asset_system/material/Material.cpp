#include "asset_system/material/Material.h"
namespace Elysian
{
    void Material::setShaderUniforms(std::shared_ptr<Shader> shader)
    {
        shader->setVec3("material.albedo", albedo);
        shader->setVec3("material.ambient", ambient);
        shader->setVec3("material.diffuse", diffuse);
        shader->setVec3("material.specular", specular);
        shader->setFloat("material.shininess", shininess);
    }

} // namespace Elysian
