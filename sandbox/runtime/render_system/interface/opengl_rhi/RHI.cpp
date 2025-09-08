#include "render_system/interface/opengl_rhi/RHI.h"
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
namespace Elysian
{
    void RHI::prepareContext()
    {
        // 载入所有GL函数指针
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }
    }

    
} // namespace Elysian
