#include "render_system/render_pipeline/passes/MainCameraPass.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "runtime_global/RuntimeGlobal.h"

#include <iostream>

namespace Elysian
{
    void MainCameraPass::initialize(std::shared_ptr<RenderPool> datas)
    {
        this->m_datas = datas;
    }

    // void MainCameraPass::preparePassData(std::shared_ptr<RenderPool> datas)
    // {
    // }

    void MainCameraPass::drawSkybox()
    {

        auto skyboxTarget = m_datas->staticTargets.back();

        // 最后渲染skybox
        glDepthFunc(GL_LEQUAL); // 设置depth函数，当值等于深度缓冲时，允许其通过depth test

        skyboxTarget->targetShader->use();
        // i->targetShader->setMat4("MVP", i->targetMvpMat); // TODO 可以为RenderTarget对象添加一个setUniform方法
        skyboxTarget->targetShader->setMat4("view", glm::mat4(glm::mat3(g_runtime.m_camera_system->matView)));
        skyboxTarget->targetShader->setMat4("projection", g_runtime.m_camera_system->matProjection);

        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // 位移变换，放置屏幕中央
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); // 缩放一下
        skyboxTarget->targetShader->setMat4("model", model);

        skyboxTarget->targetShader->setInt("skybox", 0);

        skyboxTarget->targetShader->use();

        glBindVertexArray(skyboxTarget->targetMesh->VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTarget->targetTexture->ID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0); // TODO 测试
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // 将depth函数恢复原样（小于深度值的时候通过depth test
    }

    void MainCameraPass::drawScene()
    {
        for (auto i = m_datas->staticTargets.begin(); i != m_datas->staticTargets.end() - 1; i++)
        {
            auto staticTarget = (*i);

            // printf("size[%lu]\n", staticTarget->targetMesh->positions.size());
            staticTarget->targetShader->use();
            staticTarget->targetShader->setMat4("view", g_runtime.m_camera_system->matView);
            staticTarget->targetShader->setMat4("projection", g_runtime.m_camera_system->matProjection);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));                          // 位移变换，放置屏幕中央
            model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));                           // 缩放一下
            model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 旋转90度
            staticTarget->targetShader->setMat4("model", model);

            staticTarget->targetShader->use();

            glBindVertexArray(staticTarget->targetMesh->VAO);
            // FIXME 有问题
            //  glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, staticTarget->targetTexture->ID);
            glDrawArrays(GL_TRIANGLES, 0, staticTarget->targetMesh->positions.size());
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindVertexArray(0);
        }
    }

    void MainCameraPass::drawLights()
    {
        Lights m_lights();
    }

    void MainCameraPass::drawTargets()
    {
        float posOffset = 0.01f;

        // printf(m_datas.get());
        // std::cout << std::endl;
        // std::cout << m_datas.get() << std::endl;
        // std::cout << std::endl;

        for (auto &i : m_datas->renderTargets)
        {
            // mvp变换

            i->targetShader->use();

            // i->targetShader->setMat4("projection", g_runtime.m_camera_system->matProjection);
            // i->targetMvpMat =
            i->targetShader->setMat4("view", g_runtime.m_camera_system->matView);
            i->targetShader->setMat4("projection", g_runtime.m_camera_system->matProjection);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.5f + posOffset, 0.0f)); // 位移变换，放置屏幕中央
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));                 // 缩放一下
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
            i->targetShader->setMat4("model", model);

            i->targetShader->setVec3("viewPos", g_runtime.m_camera_system->position);
            i->targetShader->setVec3("lightPos", glm::vec3(3.0f, 4.0f, 5.0f));

            glBindVertexArray(i->targetMesh->VAO);
            glBindTexture(GL_TEXTURE_2D, i->targetTexture->ID);
            glDrawArrays(GL_TRIANGLES, 0, i->targetMesh->positions.size());
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindVertexArray(0);
        }
    }

} // namespace Elysian
