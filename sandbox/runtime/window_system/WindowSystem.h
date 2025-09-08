#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <vector>
#include <functional>
namespace Elysian
{
    class WindowSystem
    {
    private:
        GLFWwindow *windowInstance;
        int mWidth;
        int mHeight;
        bool isFocus = false;

    public:
        void initialize();
        void createWindow(int width, int height, const char *title);

        void setTitle(const char *title);
        bool shouldClose();
        GLFWwindow *getWindow();
        std::vector<int> getWindowSize();
        void setFocusMode(bool mode);
        bool getFocusMode() const;
        bool isMouseButtonDown(int button) const;

    private:
        void bindCallbacks();

    public:
        // 定义函数泛型模版
        typedef std::function<void(int, int, int, int)> onKeyFunc;
        typedef std::function<void(int, int, int)> onMouseButtonFunc;
        typedef std::function<void(double, double)> onCursorPosFunc;
        typedef std::function<void(double, double)> onScrollFunc;
        typedef std::function<void(int, int)> onWindowSizeFunc;
        typedef std::function<void()> onWindowCloseFunc;
        typedef std::function<void(int,int)> onFramebufferSizeFunc;

    private:
        // 事件函数列表
        std::vector<onKeyFunc> m_onKeyFunc;
        std::vector<onMouseButtonFunc> m_onMouseButtonFunc;
        std::vector<onCursorPosFunc> m_onCursorPosFunc;
        std::vector<onScrollFunc> m_onScrollFunc;
        std::vector<onWindowSizeFunc> m_onWindowSizeFunc;
        std::vector<onWindowCloseFunc> m_onWindowCloseFunc;
        std::vector<onFramebufferSizeFunc> m_onFramebufferSizeFunc;

    public:
        // 事件函数注册
        void registerOnKeyFunc(onKeyFunc func) { m_onKeyFunc.push_back(func); }
        void registerOnMouseButtonFunc(onMouseButtonFunc func) { m_onMouseButtonFunc.push_back(func); }
        void registerOnCursorPosFunc(onCursorPosFunc func) { m_onCursorPosFunc.push_back(func); }
        void registerOnScrollFunc(onScrollFunc func) { m_onScrollFunc.push_back(func); }
        void registerOnWindowSizeFunc(onWindowSizeFunc func) { m_onWindowSizeFunc.push_back(func); }
        void registerOnWindowCloseFunc(onWindowCloseFunc func) { m_onWindowCloseFunc.push_back(func); }
        void registerOnFramebufferSizeFunc(onFramebufferSizeFunc func) { m_onFramebufferSizeFunc.push_back(func); }

    protected:
        // GLFW callback函数包装函数
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
        static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
        static void windowSizeCallback(GLFWwindow *window, int width, int height);
        static void windowCloseCallback(GLFWwindow *window);
        static void framebufferSizeCallback(GLFWwindow *window,int width,int height);

        void onKey(int key, int scancode, int action, int mods);
        void onMouseButton(int button, int action, int mods);
        void onCursorPos(double xpos, double ypos);
        void onScroll(double xoffset, double yoffset);
        void onWindowSize(int width, int height);
        void onFramebufferSize(int width, int height);
    };

} // namespace Elysian
