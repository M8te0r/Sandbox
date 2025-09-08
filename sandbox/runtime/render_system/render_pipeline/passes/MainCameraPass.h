#pragma once
#include "render_system/render_pipeline/passes/PassBase.h"
namespace Elysian
{
    class MainCameraPass : public PassBase
    {
    public:
        void initialize(std::shared_ptr<RenderPool> datas) override final;
        // virtual void postInitialize();
        // virtual void setCommonInfo(RenderPassCommonInfo common_info);
        // void preparePassData(std::shared_ptr<RenderPool> datas) override final;
        // virtual void initializeUIRenderBackend(WindowUI *window_ui);
        void drawScene();

        void drawLights();

        void drawSkybox();

        void drawTargets();

        
    };

} // namespace Elysian
