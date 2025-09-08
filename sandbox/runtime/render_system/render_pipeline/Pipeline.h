#pragma once
#include "render_system/render_pool/RenderPool.h"
// #include "render_system/render_pipeline/passes/PassBase"
#include "render_system/render_pipeline/passes/MainCameraPass.h"
#include <memory>
namespace Elysian
{
    class Pipeline
    {
    public:
        void initialize(std::shared_ptr<RenderPool> datas);

        void forwardRender(std::shared_ptr<RenderPool> datas);

        void deferredRender(std::shared_ptr<RenderPool> datas);

        void preparePassData(std::shared_ptr<RenderPool> datas);

    protected:
        std::shared_ptr<MainCameraPass> m_main_camera_pass;
    };

} // namespace Elysian
