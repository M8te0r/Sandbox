#pragma once
#include "asset_system/material/Material.h"
namespace Elysian
{
    class PbrMaterial : public Material
    {
    public:
        float metallic;
        float roughness;
        float specular_tint;
        float anisotropy;
        float sheen;
        float sheen_tint;
        float clearcoat;
        float clearcoat_gloss;

    public:
        void setShaderUniforms(std::shared_ptr<Shader> shader) override;
    };

} // namespace Elysian
