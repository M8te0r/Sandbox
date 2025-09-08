#pragma once
#include "render_system/render_pool/RenderPool.h"
#include <memory>
namespace Elysian
{
    class PassBase
    {
    protected:

        // std::shared_ptr<RHI> m_rhi;

        std::shared_ptr<RenderPool> m_datas;

    public:
        virtual void initialize(std::shared_ptr<RenderPool> datas) = 0;
        // virtual void postInitialize();
        // virtual void setCommonInfo(std::shared_ptr<RenderPool> common_datas);
        // virtual void preparePassData(std::shared_ptr<RenderPool> datas);
        // virtual void initializeUIRenderBackend(WindowUI *window_ui);
    };

} // namespace Elysian
