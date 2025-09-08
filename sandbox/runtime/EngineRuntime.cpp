#include "EngineRuntime.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include "runtime_global/RuntimeGlobal.h"
#include "input_system/InputSystem.h"
#include "window_system/WindowSystem.h"
#include "asset_system/AssetSystem.h"
#include "render_system/RenderSystem.h"

namespace Elysian
{

    void EngineRuntime::startEngine()
    {
        printf("= = = = = = = = start Engine\n");
        g_runtime.initialize();
    }

    void EngineRuntime::run()
    {
        printf("= = = = = = = = run Engine\n");
        auto mainWindow = g_runtime.m_window_system;
        // TODO 测试架构的渲染流程

        // TODO 永久循环，不会退出的窗口？
        while (!mainWindow->shouldClose())
        {
            const float delta_time = calculateDeltaTime();
            calculateFPS(delta_time);
            g_runtime.m_input_system->tick();
            render();

            glfwPollEvents();

            // 窗口设置标题，显示FPS
            mainWindow->setTitle(std::string("Elysian - " + std::to_string(this->FPS) + " FPS").c_str());
        }
    }

    void EngineRuntime::shutdownEngine()
    {
        g_runtime.finalize();
        printf("= = = = = = = = shutdown Engine\n");
    }

    // 初始化静态变量
    const float EngineRuntime::fpsAlpha = 1.f / 100;

    float EngineRuntime::calculateDeltaTime()
    {
        float deltaTime;

        std::chrono::steady_clock::time_point currentFrame = std::chrono::steady_clock::now();
        std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(currentFrame - lastFrame);
        deltaTime = time_span.count();

        lastFrame = currentFrame;

        return deltaTime;
    }

    void EngineRuntime::calculateFPS(float delta_time)
    {
        frameCount++;

        if (frameCount == 1)
        {
            averageDuration = delta_time;
        }
        else
        {
            // 在averageDuration和delta_time之间做线性插值
            averageDuration = averageDuration * (1 - fpsAlpha) + delta_time * fpsAlpha;
        }

        FPS = static_cast<int>(1.f / averageDuration);
    }

    void EngineRuntime::render()
    {
        // 每次渲染前清空屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glViewport(0, 0, g_runtime.m_window_system->getWindowSize()[0], g_runtime.m_window_system->getWindowSize()[1]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        g_runtime.m_render_system->tick();

        glfwSwapBuffers(g_runtime.m_window_system->getWindow());
    }
} // namespace Elysian
