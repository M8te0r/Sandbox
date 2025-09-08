#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
namespace Elysian
{
    enum class EditorCommand : unsigned int
    {
        camera_left = 1 << 0,      // A
        camera_back = 1 << 1,      // S
        camera_foward = 1 << 2,    // W
        camera_right = 1 << 3,     // D
        camera_up = 1 << 4,        // Q
        camera_down = 1 << 5,      // E
        translation_mode = 1 << 6, // T
        rotation_mode = 1 << 7,    // R
        scale_mode = 1 << 8,       // C
        exit = 1 << 9,             // Esc
        delete_object = 1 << 10,   // Delete
        hide_mouse = 1 << 11       // Grave accent
    };

    class InputSystem
    {
    private:
        unsigned int m_command = 0;

    public:
        bool firstMouse = true;
        double m_last_cursor_x = 0;
        double m_last_cursor_y = 0;
        float velocity = 0.05f;

    public:
        void initialize();
        void tick();
        void finalize();

        void processKeyCommand();
        void processMousePos(double xoffset, double yoffset);

    private:
        // custome callbacks
        void onKey(int key, int scancode, int action, int mods);
        void onCursorPos(double current_cursor_x, double current_cursor_y);
        void onMouseButtonClick(int key, int action);
        void onMouseScroll(double xoffset, double yoffset);
    };

} // namespace Elysian
