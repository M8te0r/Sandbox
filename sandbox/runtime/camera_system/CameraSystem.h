#pragma once
#include "glm/glm.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Elysian
{
    class CameraSystem
    {
    public:
        glm::vec3 position;
        glm::vec3 position_delta;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;

        glm::vec3 worldup = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 matProjection;
        glm::mat4 matView;

        // 欧拉角
        float yaw;      // 偏航角
        float pitch;    // 俯仰角
        float rotation; // 旋转角

        float fov;         // 视野 https://blog.csdn.net/SnoopyNa2Co3/article/details/83893093
        float aspectRatio; // 屏幕宽高比，相当于分辨率
        float zNear;       // 投影近平面
        float zFar;        // 投影远平面

        bool isPerspective; // 互斥锁（投影变换和正交变换）

    public:
        CameraSystem();
        CameraSystem(glm::vec3 _position, glm::vec3 _front, glm::vec3 _up);

        void initialize();
        void finalize();

        void setFront();
        glm::mat4 setView();
        void setPerspective(float _fov, float _aspect, float _near, float _far);
        void setOrthographic(float _left, float _right, float _bottom, float _top, float _near, float _far);
    };

} // namespace Elysian
