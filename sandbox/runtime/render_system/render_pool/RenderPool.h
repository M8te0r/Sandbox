#pragma once
#include "render_system/render_target/RenderTarget.h"
#include <vector>
#include <memory>

namespace Elysian
{
    class RenderPool
    {
    public:
        // TODO 不要使用这种结构，最好使用heap，从而可以优先渲染不透明的物体，在渲染透明物体
        std::vector<std::shared_ptr<RenderTarget>> staticTargets;
        std::vector<std::shared_ptr<RenderTarget>> renderTargets;

    public:
        void initialize();
        void sortTarget();
        void addTarget(std::shared_ptr<RenderTarget> t);
        void loadStaticTarget();

    private:
        void addStaticTarget(std::shared_ptr<RenderTarget> t);
    };

} // namespace Elysian
