#pragma once
#include "glm/glm.hpp"

#include "glm/ext/scalar_constants.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <vector>
#include <memory>

namespace Elysian
{

    struct PointLight
    {
    public:
        glm::vec3 position;
        // radiant flux in W
        glm::vec3 flux;

        // calculate an appropriate radius for light culling
        // a windowing function in the shader will perform a smooth transition to zero
        // this is not physically based and usually artist controlled

        PointLight(float x, float y, float z) : position(glm::vec3(x, y, z)){};
        PointLight(glm::vec3 pos) : position(pos){};

        float calculateRadius() const
        {
            // radius = where attenuation would lead to an intensity of 1W/m^2
            const float INTENSITY_CUTOFF = 1.0f;
            const float ATTENTUATION_CUTOFF = 0.05f;
            glm::vec3 intensity = flux / (4.0f * glm::pi<float>());
            float maxIntensity = glm::max(glm::max(intensity.x, intensity.y), intensity.z);
            float attenuation = glm::max(INTENSITY_CUTOFF, ATTENTUATION_CUTOFF * maxIntensity) / maxIntensity;
            return 1.0f / sqrtf(attenuation);
        }
    };

    struct AmbientLight
    {
    public:
        glm::vec3 irradiance;

        AmbientLight(float irrX, float irrY, float irrZ) : irradiance(glm::vec3(irrX, irrY, irrZ)){};
        AmbientLight(glm::vec3 irr) : irradiance(irr){};
    };

    struct DirectionalLight
    {
    public:
        glm::vec3 direction;
        glm::vec3 color;
        DirectionalLight(float x, float y, float z) : direction(glm::vec3(x, y, z)), color(glm::vec3(1.0f, 1.0f, 1.0f)){};
        DirectionalLight(glm::vec3 dir, glm::vec3 lightColor) : direction(dir), color(lightColor){};
    };

    struct Lights
    {
    public:
        std::shared_ptr<AmbientLight> aLight;
        std::vector<DirectionalLight> dirLights;
        std::vector<PointLight> pLights;
        Lights()
        {
            // 环境光
            aLight = std::make_shared<AmbientLight>(0.1f, 0.1f, 0.1f);

            // 平行光
            DirectionalLight m_dl_b(-1.0f, 2.0f, 0.0f);
            dirLights.push_back(m_dl_b);

            // 点光源
            PointLight pl_1(sin(glfwGetTime()), 1.0f, cos(glfwGetTime()));
            pLights.push_back(pl_1);
            PointLight pl_2(sin(glfwGetTime()), 1.0f, 0.0f);
            pLights.push_back(pl_2);
        }
    };

} // namespace Elysian