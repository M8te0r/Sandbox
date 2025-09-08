#include "runtime_global/RuntimeGlobal.h"
#include <iostream>

#include "window_system/WindowSystem.h"
#include "camera_system/CameraSystem.h"
#include "input_system/InputSystem.h"
#include "render_system/RenderSystem.h"
#include "asset_system/AssetSystem.h"
namespace Elysian
{
    RuntimeGlobal g_runtime;

    void RuntimeGlobal::initialize()
    {
        printf("= = = = = = = = initialize global context\n");

        // 顺序执行
        // 1.相机
        m_camera_system = std::make_shared<CameraSystem>();
        m_camera_system->initialize();

        // 2.窗口系统
        m_window_system = std::make_shared<WindowSystem>();
        m_window_system->initialize();

        // 3.输入系统
        m_input_system = std::make_shared<InputSystem>();
        m_input_system->initialize();

        // 4.资产系统
        m_asset_system = std::make_shared<AssetSystem>();

        // 5.渲染系统
        m_render_system = std::make_shared<RenderSystem>();
        m_render_system->initialize();
    }

    void RuntimeGlobal::finalize()
    {
        printf("= = = = = = = = finalize global context\n");
        // 窗口
        m_window_system.reset();
        // 输入
        m_camera_system.reset();
        // 输入
        m_input_system.reset();
        // 资产
        m_asset_system.reset();
        // 渲染
        m_render_system.reset();
    }
} // namespace Elysian
