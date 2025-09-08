#include "camera_system/CameraSystem.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

namespace Elysian
{
    CameraSystem::CameraSystem()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::normalize(glm::cross(front, up));
        yaw = 0.0f;
        pitch = 0.0f;
        setView();
    }

    void CameraSystem::initialize()
    {
        // TODO 初始化相机位置和观察方向
        position = glm::vec3(0.0f, 1.0f, 1.0f);
        front = glm::vec3(0.0f, -1.0f, -1.0f);
    }

    CameraSystem::CameraSystem(glm::vec3 _position, glm::vec3 _front, glm::vec3 _up) : position(_position), front(_front), up(_up), right(glm::normalize(glm::cross(_front, _up)))
    {
        yaw = 0.0f;
        pitch = 0.0f;
        setView();
    }

    glm::mat4 CameraSystem::setView()
    {
        // position+front=()
        // 位置向量是相反的，因为我们最终希望把世界平移到与我们自身移动的相反方向
        matView = glm::lookAt(position, position + front, up);
        return matView;
    }

    void CameraSystem::setPerspective(float _fov, float _aspect, float _near, float _far)
    {
        isPerspective = true;
        matProjection = glm::perspective(_fov, _aspect, _near, _far);
        fov = _fov;
        aspectRatio = _aspect;
        zNear = _near;
        zFar = _far;
    }

    // --------------------------------------------------------------------------------------------
    void CameraSystem::setOrthographic(float _left, float _right, float _bottom, float _top, float _near, float _far)
    {
        isPerspective = false;
        matProjection = glm::ortho(_left, _right, _bottom, _top, _near, _far);
        zNear = _near;
        zFar = _far;
    }

    void CameraSystem::setFront()
    {
        glm::vec3 currentFront;

        currentFront.y = sin(glm::radians(pitch));
        currentFront.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        currentFront.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw)); // 因为是面朝z轴负方向的，这里要取负号

        front = glm::normalize(currentFront);
    }

} // namespace Elysian
