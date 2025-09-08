#include "render_system/render_target/RenderTarget.h"
namespace Elysian
{
    RenderTarget::~RenderTarget()
    {
        targetMesh.reset();
        targetShader.reset();
        targetTexture.reset();
    }
    void RenderTarget::initialize(std::shared_ptr<Mesh> _targetMesh, std::shared_ptr<Shader> _targetShader, std::shared_ptr<Texture> _targetTexture)
    {
        targetMesh = _targetMesh;
        targetShader = _targetShader;
        targetTexture = _targetTexture;
    }
} // namespace Elysian