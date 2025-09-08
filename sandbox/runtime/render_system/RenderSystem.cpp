#include "render_system/RenderSystem.h"
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>

#include "runtime_global/RuntimeGlobal.h"
#include "asset_system/AssetSystem.h"
#include "render_system/render_pool/RenderPool.h"
#include "asset_system/mesh/inner_mesh/Cube.h"
#include "camera_system/CameraSystem.h"
#include "window_system/WindowSystem.h"
#include "render_system/render_target/RenderTarget.h"

#include "render_system/render_pipeline/Pipeline.h"

// TODO 测试用，打印glm
// #include "glm/ext.hpp"
// #include "glm/gtx/string_cast.hpp"
// std::cout << glm::to_string(m_camera->matView) << std::endl;

namespace Elysian
{
    void RenderSystem::initialize()
    {
        // 载入所有GL函数指针
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // 获取全局的资源指针
        auto m_asset_sys = g_runtime.m_asset_system;

        // TODO 初始化摄像头设置
        auto windowSize = g_runtime.m_window_system->getWindowSize();
        g_runtime.m_camera_system->setPerspective(glm::radians(45.0f), (float)windowSize[0] / (float)windowSize[1], 0.1f, 100.0f);

        // 初始化全局渲染指令队列
        m_pool = std::make_shared<RenderPool>();

        // FIXME Z-buffer深度测试，用于处理图像的自遮挡效果
        glEnable(GL_DEPTH_TEST);

        // 装载引擎的静态资源（天空盒等）
        {
            m_pool->loadStaticTarget();
        }

        // TODO 这其实算作一个pipeline？？？？
        {
            // 载入资源
            m_asset_sys->loadShader("../sandbox/assets/shaders/test_camera.vs",
                                    "../sandbox/assets/shaders/test_camera.fs",
                                    nullptr,
                                    "testShader");

            m_asset_sys->loadTexture("../sandbox/assets/textures/textureTriangle/container.jpg",
                                     "testTexture");

            m_asset_sys->loadMesh(static_cube_mesh, "testCube");

            // 新建一个target
            auto m_target = std::make_shared<RenderTarget>();
            m_target->targetShader = m_asset_sys->shaderAssets["testShader"];
            m_target->targetTexture = m_asset_sys->textureAssets["testTexture"];
            m_target->targetMesh = m_asset_sys->meshAssets["testCube"];

            // 装载进入指令队列
            m_pool->addTarget(m_target);

            // TODO:新建cube形状的光源

            // m_pool->addTarget(light_target);
        }

        // 初始化Pipeline
        m_pipeline = std::make_shared<Pipeline>();
        m_pipeline->initialize(m_pool);
    }

    void RenderSystem::tick()
    {
#ifdef __APPLE__
        // FIXME not elegent
        int tWidth, tHeight;
        glfwGetFramebufferSize(g_runtime.m_window_system->getWindow(), &tWidth, &tHeight);
        glViewport(0, 0, tWidth, tHeight);

#endif
        g_runtime.m_camera_system->setView();

        // m_pipeline->forwardRender(m_pool);
        m_pipeline->forwardRender(m_pool);
    }

    void RenderSystem::finalize()
    {
        // TODO 1.释放所有share_ptr

        // TODO 2.delete所有gl资源
        //  glDeleteVertexArrays(1, &VAO);
        //  glDeleteBuffers(1, &VBO);
    }
} // namespace Elysian
