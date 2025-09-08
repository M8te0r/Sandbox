#include "window_system/WindowSystem.h"

#include "iostream"

namespace Elysian
{
    void WindowSystem::initialize()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        // 主窗口
        createWindow(1280, 768, "main window");
        bindCallbacks();
    }

    void WindowSystem::createWindow(int width, int height, const char *title)
    {
        GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        mWidth = width;
        mHeight = height;
        windowInstance = window;
    }

    void WindowSystem::bindCallbacks()
    {
        // std::shared_ptr g_window = g_runtime.m_window_system;
        // 为当前窗口绑定GLFW回传函数(初始化时绑定的是空函数池，待到inputSystem初始化时，函数池内才有函数)
        glfwSetWindowUserPointer(windowInstance, this);
        glfwSetKeyCallback(windowInstance, keyCallback);
        glfwSetMouseButtonCallback(windowInstance, mouseButtonCallback);
        glfwSetCursorPosCallback(windowInstance, cursorPosCallback);
        glfwSetScrollCallback(windowInstance, scrollCallback);
        glfwSetWindowSizeCallback(windowInstance, windowSizeCallback);
        glfwSetWindowCloseCallback(windowInstance, windowCloseCallback);
        glfwSetFramebufferSizeCallback(windowInstance, framebufferSizeCallback);

        // 默认不器用鼠标模式
        // glfwSetInputMode(windowInstance, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    }

    bool WindowSystem::shouldClose()
    {
        return glfwWindowShouldClose(windowInstance);
    }

    GLFWwindow *WindowSystem::getWindow()
    {
        return windowInstance;
    }

    void WindowSystem::setTitle(const char *title)
    {
        glfwSetWindowTitle(windowInstance, title);
    }

    std::vector<int> WindowSystem::getWindowSize()
    {
        return std::vector<int>{mWidth, mHeight};
    }

    void WindowSystem::setFocusMode(bool mode)
    {
        isFocus = mode;
        glfwSetInputMode(windowInstance, GLFW_CURSOR, isFocus ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        // glfwSetCursorPosCallback(windowInstance, isFocus ? cursorPosCallback : NULL);
        // glfwSetScrollCallback(windowInstance, isFocus ? scrollCallback : NULL);
    }

    bool WindowSystem::getFocusMode() const
    {
        return isFocus;
    }

    bool WindowSystem::isMouseButtonDown(int button) const
    {
        if (button < GLFW_MOUSE_BUTTON_1 || button > GLFW_MOUSE_BUTTON_LAST)
        {
            return false;
        }
        return glfwGetMouseButton(windowInstance, button) == GLFW_PRESS;
    }

    // = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
    // = = = = = = = = = = = = = = = = = = = = = callback具体实现 = = = = = = = = = = = = = = = = = = = = =
    // = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    void WindowSystem::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        WindowSystem *app = (WindowSystem *)glfwGetWindowUserPointer(window);
        if (app)
        {
            app->onKey(key, scancode, action, mods);
        }
    }
    void WindowSystem::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        WindowSystem *app = (WindowSystem *)glfwGetWindowUserPointer(window);
        if (app)
        {
            app->onMouseButton(button, action, mods);
        }
    }
    void WindowSystem::cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
    {
        WindowSystem *app = (WindowSystem *)glfwGetWindowUserPointer(window);
        if (app)
        {
            app->onCursorPos(xpos, ypos);
        }
    }
    void WindowSystem::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
    {
        WindowSystem *app = (WindowSystem *)glfwGetWindowUserPointer(window);
        if (app)
        {
            app->onScroll(xoffset, yoffset);
        }
    }

    void WindowSystem::windowSizeCallback(GLFWwindow *window, int width, int height)
    {
        WindowSystem *app = (WindowSystem *)glfwGetWindowUserPointer(window);
        if (app)
        {
            // 更新私有的mWidth和mHeight
            app->mWidth = width;
            app->mHeight = height;
            // 执行其他函数
            app->onWindowSize(width, height);
        }
    }

    void WindowSystem::windowCloseCallback(GLFWwindow *window)
    {
        glfwSetWindowShouldClose(window, true);
    }

    void WindowSystem::framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        WindowSystem *app = (WindowSystem *)glfwGetWindowUserPointer(window);
        if (app)
        {
            app->onFramebufferSize(width, height);
        }
    }

    // = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
    // = = = = = = = = = = = = = = = = = = = = = 函数事件列表查询 = = = = = = = = = = = = = = = = = = = = =
    // = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    void WindowSystem::onKey(int key, int scancode, int action, int mods)
    {
        for (auto &func : m_onKeyFunc)
            func(key, scancode, action, mods);
    }

    void WindowSystem::onMouseButton(int button, int action, int mods)
    {
        for (auto &func : m_onMouseButtonFunc)
            func(button, action, mods);
    }
    void WindowSystem::onCursorPos(double xpos, double ypos)
    {
        for (auto &func : m_onCursorPosFunc)
            func(xpos, ypos);
    }

    void WindowSystem::onScroll(double xoffset, double yoffset)
    {
        for (auto &func : m_onScrollFunc)
            func(xoffset, yoffset);
    }

    void WindowSystem::onWindowSize(int width, int height)
    {
        for (auto &func : m_onWindowSizeFunc)
            func(width, height);
    }
    void WindowSystem::onFramebufferSize(int width, int height)
    {
        for (auto &func : m_onFramebufferSizeFunc)
            func(width, height);
    }
} // namespace Elysian
