#include "input_system/InputSystem.h"

#include "runtime_global/RuntimeGlobal.h"
#include "window_system/WindowSystem.h"
#include "camera_system/CameraSystem.h"

#include "glm/glm.hpp"

namespace Elysian
{
    unsigned int k_complement_control_command = 0xFFFFFFFF; // 初始化控制指令，32位1，用于给指令置位

    void InputSystem::tick()
    {
        processKeyCommand();
        // processMousePos();
    }

    void InputSystem::onKey(int key, int scancode, int action, int mods)
    {
        // 每次按键后得到新的command，通过该执行processCommand()方法调用command
        auto g_camera = g_runtime.m_camera_system;

        // TODO focus模式置位，记得删除
        m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::hide_mouse);

        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                m_command |= (unsigned int)EditorCommand::exit;
            case GLFW_KEY_A:
                m_command |= (unsigned int)EditorCommand::camera_left;
                break;
            case GLFW_KEY_S:
                m_command |= (unsigned int)EditorCommand::camera_back;
                break;
            case GLFW_KEY_W:
                m_command |= (unsigned int)EditorCommand::camera_foward;
                break;
            case GLFW_KEY_D:
                m_command |= (unsigned int)EditorCommand::camera_right;
                break;
            case GLFW_KEY_Q:
                m_command |= (unsigned int)EditorCommand::camera_up;
                break;
            case GLFW_KEY_E:
                m_command |= (unsigned int)EditorCommand::camera_down;
                break;
            case GLFW_KEY_T:
                m_command |= (unsigned int)EditorCommand::translation_mode;
                break;
            case GLFW_KEY_R:
                m_command |= (unsigned int)EditorCommand::rotation_mode;
                break;
            case GLFW_KEY_C:
                m_command |= (unsigned int)EditorCommand::scale_mode;
                break;
            case GLFW_KEY_DELETE:
                m_command |= (unsigned int)EditorCommand::delete_object;
                break;
            case GLFW_KEY_GRAVE_ACCENT:
                m_command |= (unsigned int)EditorCommand::hide_mouse;
            default:
                break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::exit);
                break;
            case GLFW_KEY_A:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_left);
                break;
            case GLFW_KEY_S:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_back);
                break;
            case GLFW_KEY_W:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_foward);
                break;
            case GLFW_KEY_D:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_right);
                break;
            case GLFW_KEY_Q:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_up);
                break;
            case GLFW_KEY_E:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_down);
                break;
            case GLFW_KEY_T:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::translation_mode);
                break;
            case GLFW_KEY_R:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::rotation_mode);
                break;
            case GLFW_KEY_C:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::scale_mode);
                break;
            case GLFW_KEY_DELETE:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::delete_object);
                break;
            case GLFW_KEY_GRAVE_ACCENT:
                m_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::hide_mouse);
            default:
                break;
            }
        }
    }

    void InputSystem::processKeyCommand()
    {

        std::shared_ptr editor_camera = g_runtime.m_camera_system;
        if ((unsigned int)EditorCommand::exit & m_command)
        {
            glfwSetWindowShouldClose(g_runtime.m_window_system->getWindow(), true);
        }

        if ((unsigned int)EditorCommand::camera_foward & m_command)
        {
            editor_camera->position += editor_camera->front * velocity;
            // TODO 调试用
            // printf("key: W \n");
            // printf("position: [%f, %f, %f]\n", editor_camera->position.x, editor_camera->position.y, editor_camera->position.z);
        }
        if ((unsigned int)EditorCommand::camera_back & m_command)
        {
            editor_camera->position -= editor_camera->front * velocity;
        }
        if ((unsigned int)EditorCommand::camera_left & m_command)
        {
            editor_camera->position -= editor_camera->right * velocity;
        }
        if ((unsigned int)EditorCommand::camera_right & m_command)
        {
            editor_camera->position += editor_camera->right * velocity;
        }
        if ((unsigned int)EditorCommand::camera_up & m_command)
        {
            editor_camera->position += editor_camera->up * velocity;
        }
        if ((unsigned int)EditorCommand::camera_down & m_command)
        {
            editor_camera->position -= editor_camera->up * velocity;
        }
        // if ((unsigned int)EditorCommand::delete_object & m_command)
        // {
        //     g_editor_global_context.m_scene_manager->onDeleteSelectedGObject();
        // }
        if ((unsigned int)EditorCommand::hide_mouse & m_command)
        {

            // g_runtime.m_window_system->setFocusMode(!g_runtime.m_window_system->getFocusMode());
        }

        // editor_camera->move(camera_relative_pos);
    }

    void InputSystem::onCursorPos(double current_cursor_x, double current_cursor_y)
    {
        // TODO 需要完善
        // 右键事件
        if (g_runtime.m_window_system->isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            g_runtime.m_window_system->setFocusMode(true);

            if (firstMouse)
            {
                m_last_cursor_x = current_cursor_x;
                m_last_cursor_y = current_cursor_y;
                firstMouse = false;
            }

            // 获取鼠标两次计算之间的偏移量，准备根据偏移量计算速度
            float xoffset = current_cursor_x - m_last_cursor_x;
            float yoffset = m_last_cursor_y - current_cursor_y; // 反转，因为y坐标轴是从上往下的

            m_last_cursor_x = current_cursor_x;
            m_last_cursor_y = current_cursor_y;

            {
                float sensitivity = 0.05f;
                xoffset *= sensitivity;
                yoffset *= sensitivity;
                std::shared_ptr g_camera = g_runtime.m_camera_system;

                // g_runtime.m_camera_system->yaw += xoffset;
                // g_runtime.m_camera_system->pitch += yoffset;
                g_camera->yaw += xoffset;
                g_camera->pitch += yoffset;

                // 防止自动计算空数组的长度
                if (g_camera->yaw == 0.0f)
                    g_camera->yaw = 0.01f;
                if (g_camera->pitch == 0.0f)
                    g_camera->pitch = 0.01f;
                // 确保俯仰角不会越界，不然屏幕会爆炸
                if (g_camera->pitch > 89.0f)
                    g_camera->pitch = 89.0f;
                if (g_camera->pitch < -89.0f)
                    g_camera->pitch = -89.0f;

                // 计算新的front向量
                g_camera->setFront();

                // 重新计算right向量和up向量
                // 对向量进行归一化，因为向上或向下看得越多，它们的长度就越接近0，这会导致移动速度变慢。
                g_camera->right = glm::normalize(glm::cross(g_camera->front, g_camera->worldup));
                g_camera->up = glm::normalize(glm::cross(g_camera->right, g_camera->front));
            }
        }
        else if (g_runtime.m_window_system->isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            // TODO 左键事件
            g_runtime.m_window_system->setFocusMode(false);
        }
        else
        {
            // g_runtime.m_window_system->setFocusMode(!g_runtime.m_window_system->getFocusMode());
            g_runtime.m_window_system->setFocusMode(false);
        }
    }

    void InputSystem::onMouseButtonClick(int key, int action)
    {
        // TODO 左键选中物体，右键没事
    }

    void InputSystem::onMouseScroll(double xoffset, double yoffset)
    {
        if (g_runtime.m_window_system->isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
// 视野缩放：鼠标滚轮事件依赖于是否点击了右键
#ifdef __APPLE__
            if (yoffset < 0)
            {
                g_runtime.m_camera_system->position += g_runtime.m_camera_system->front * 8.f * velocity;
            }
            else
            {
                g_runtime.m_camera_system->position -= g_runtime.m_camera_system->front * 8.f * velocity;
            }
#else

            if (yoffset > 0)
            {
                g_runtime.m_camera_system->position += g_runtime.m_camera_system->front * 8.f * velocity;
            }
            else
            {
                g_runtime.m_camera_system->position -= g_runtime.m_camera_system->front * 8.f * velocity;
            }
#endif
        }
        else if (g_runtime.m_window_system->isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            // 选中模型大小缩放
        }
    }

    void InputSystem::processMousePos(double xoffset, double yoffset)
    {
    }

    void InputSystem::initialize()
    {

        std::shared_ptr<WindowSystem> window_system = g_runtime.m_window_system;
        assert(window_system);
        // 初始化鼠标位置
        m_last_cursor_x = 0.5 * window_system->getWindowSize()[0];
        m_last_cursor_y = 0.5 * window_system->getWindowSize()[1];

        // OpenGL内置的callback函数所需的static函数名称已在WindowSystem中定义好
        // 此处将InputSystem成员函数注册至WindowSystem的vector中

        // 注册鼠标点击事件
        window_system->registerOnMouseButtonFunc(std::bind(&InputSystem::onMouseButtonClick,
                                                           this,
                                                           std::placeholders::_1,
                                                           std::placeholders::_2));

        // 注册鼠标事件
        window_system->registerOnCursorPosFunc(std::bind(&InputSystem::onCursorPos,
                                                         this,
                                                         std::placeholders::_1,
                                                         std::placeholders::_2));

        // 注册鼠标滚动事件
        window_system->registerOnScrollFunc(std::bind(&InputSystem::onMouseScroll,
                                                      this,
                                                      std::placeholders::_1,
                                                      std::placeholders::_2));

        // 注册键盘事件
        window_system->registerOnKeyFunc(std::bind(&InputSystem::onKey,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2,
                                                   std::placeholders::_3,
                                                   std::placeholders::_4));
    }

    void InputSystem::finalize()
    {
    }
} // namespace Elysian
