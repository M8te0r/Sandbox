#include "render_system/render_pipeline/Pipeline.h"

#include "render_system/render_pipeline/passes/MainCameraPass.h"
namespace Elysian
{
    
    void Pipeline::initialize(std::shared_ptr<RenderPool> datas)
    {

        // shared_ptr一定要分配指针！！！
        m_main_camera_pass = std::make_shared<MainCameraPass>();
        // 所有的RenderPass共用一个RenderPool
        m_main_camera_pass->initialize(datas);
    }

    void Pipeline::forwardRender(std::shared_ptr<RenderPool> datas)
    {
        // TODO 记得恢复
        m_main_camera_pass->drawScene();
        m_main_camera_pass->drawTargets();
        m_main_camera_pass->drawSkybox();
    }

    void Pipeline::deferredRender(std::shared_ptr<RenderPool> datas)
    {
    }

    void Pipeline::preparePassData(std::shared_ptr<RenderPool> datas)
    {
    }

} // namespace Elysian
