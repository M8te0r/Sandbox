#include "render_system/render_pool/RenderPool.h"
#include "runtime_global/RuntimeGlobal.h"
#include "asset_system/AssetSystem.h"
namespace Elysian
{
    void RenderPool::initialize()
    {
    }

    void RenderPool::addTarget(std::shared_ptr<RenderTarget> t)
    {
        renderTargets.push_back(t);
    }
    void RenderPool::addStaticTarget(std::shared_ptr<RenderTarget> t)
    {
        staticTargets.push_back(t);
    }

    void RenderPool::loadStaticTarget()
    {
        auto m_asset_sys = g_runtime.m_asset_system;

        // 载入光照
        {
            

            m_asset_sys->loadShader("/Users/crystalized/cpp_project/mySandbox/sandbox/assets/shaders/g_light.vs",
                                    "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/shaders/g_light.fs",
                                    nullptr,
                                    "gLightShader");
            m_asset_sys->loadMesh(static_cube_mesh,
                                  "gLightMesh");
        }

        // 载入场景资源
        {
            // 载入地板
            m_asset_sys->loadShader("/Users/crystalized/cpp_project/mySandbox/sandbox/assets/shaders/g_floor.vs",
                                    "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/shaders/g_floor.fs",
                                    nullptr,
                                    "gFloorShader");

            m_asset_sys->loadTexture("/Users/crystalized/cpp_project/mySandbox/sandbox/assets/textures/box/marble.jpg",
                                     "gFloorTexture");

            m_asset_sys->loadMesh(static_quad_mesh, "gFloorMesh");

            // 新建一个target
            auto g_floor = std::make_shared<RenderTarget>();
            g_floor->targetShader = m_asset_sys->shaderAssets["gFloorShader"];
            g_floor->targetTexture = m_asset_sys->textureAssets["gFloorTexture"];
            g_floor->targetMesh = m_asset_sys->meshAssets["gFloorMesh"];

            // 装载进入指令队列
            addStaticTarget(g_floor);
        }

        // 载入全局天空盒资源
        // TODO 有点冗长，最好在config文件里配置好这些信息，然后用一条loadByConfig语句精简下述代码
        {
            // texture信息
            std::vector<std::string> skyBoxFaces{"/Users/crystalized/cpp_project/mySandbox/sandbox/assets/textures/skybox/right.jpg",
                                                 "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/textures/skybox/left.jpg",
                                                 "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/textures/skybox/top.jpg",
                                                 "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/textures/skybox/bottom.jpg",
                                                 "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/textures/skybox/front.jpg",
                                                 "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/textures/skybox/back.jpg"};
            m_asset_sys->loadTexture(skyBoxFaces,
                                     "g_skybox_texture");

            // shader信息
            m_asset_sys->loadShader("/Users/crystalized/cpp_project/mySandbox/sandbox/assets/shaders/g_sky_box.vs",
                                    "/Users/crystalized/cpp_project/mySandbox/sandbox/assets/shaders/g_sky_box.fs",
                                    nullptr,
                                    "g_skybox_shader");
            // mesh信息
            m_asset_sys->loadMesh(static_cube_mesh,
                                  "g_skybox_cube");

            // MVP信息
            auto m_veiw = glm::mat4(glm::mat3(g_runtime.m_camera_system->matView)); // 去除view矩阵的变换，从而摄像机位移时，摄像机仍然处于skybox的中心
            auto m_projection = g_runtime.m_camera_system->matProjection;
            auto m_model = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)); // 盒子是0.5，把他放大到1.0
            auto MVP = m_projection * m_veiw * m_model;

            // 新建一个target，并且填充信息
            auto skybox_target = std::make_shared<RenderTarget>();
            skybox_target->targetTexture = m_asset_sys->textureAssets["g_skybox_texture"];
            skybox_target->targetShader = m_asset_sys->shaderAssets["g_skybox_shader"];
            skybox_target->targetMesh = m_asset_sys->meshAssets["g_skybox_cube"];
            skybox_target->targetMvpMat = MVP;

            // 装载进入指令队列
            addStaticTarget(skybox_target);
        }
    }
} // namespace Elysian
