#pragma once
#include <memory>
#include "render_system/interface/opengl_rhi/RHI.h"

namespace Elysian
{
    class RHI;
    class RenderPool;
    class CameraSystem;
    class Pipeline;

    class RenderSystem
    {
    private:
        std::shared_ptr<RHI> m_rhi;
        std::shared_ptr<RenderPool> m_pool;
        std::shared_ptr<CameraSystem> m_camera;
        std::shared_ptr<Pipeline> m_pipeline;
        // std::shared_ptr<RenderTarget> m_target;

    public:
        void initialize();
        void finalize();

        void tick();
    };

} // namespace Elysian
