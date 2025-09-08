#pragma once
#include <memory>

namespace Elysian
{
    class WindowSystem;
    class AssetSystem;
    class CameraSystem;
    class RenderSystem;
    class InputSystem;

    class RuntimeGlobal
    {
    public:
        std::shared_ptr<WindowSystem> m_window_system;
        std::shared_ptr<AssetSystem> m_asset_system;
        std::shared_ptr<CameraSystem> m_camera_system;
        std::shared_ptr<RenderSystem> m_render_system;
        std::shared_ptr<InputSystem> m_input_system;

    public:
        void initialize();
        void finalize();
    };

    extern RuntimeGlobal g_runtime;

} // namespace Elysian
