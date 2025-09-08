#include "asset_system/material/PbrMaterial.h"
namespace Elysian
{
void PbrMaterial::setShaderUniforms(std::shared_ptr<Shader> shader) 
        {
            shader->setVec3("material.albedo", albedo);
            shader->setFloat("material.metallic", metallic);
            shader->setFloat("material.roughness", roughness);
            shader->setFloat("material.specular_tint", specular_tint);
            shader->setFloat("material.anisotropy", anisotropy);
            shader->setFloat("material.sheen", sheen);
            shader->setFloat("material.sheen_tint", sheen_tint);
            shader->setFloat("material.clearcoat", clearcoat);
            shader->setFloat("material.clearcoat_gloss", clearcoat_gloss);
        }

} // namespace Elysian