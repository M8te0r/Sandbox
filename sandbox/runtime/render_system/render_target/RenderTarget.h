#pragma once

#include <memory>
#include "asset_system/mesh/Mesh.h"
#include "asset_system/mesh/inner_mesh/Cube.h"
#include "asset_system/mesh/inner_mesh/Triangle.h"
#include "asset_system/shader/Shader.h"
#include "asset_system/texture/Texture.h"

#include "render_system/light/Light.h"
#include "camera_system/CameraSystem.h"
#include "asset_system/material/Material.h"

namespace Elysian
{
    class RenderTarget
    {
    public:
        std::shared_ptr<Mesh> targetMesh;           // 顶点缓冲和索引缓冲的引用数据
        std::shared_ptr<Shader> targetShader;       // shader的引用数据
        std::shared_ptr<Texture> targetTexture;     // texture的引用数据
        std::shared_ptr<Material> targetMaterial;   // material的应用数据
        glm::mat4 targetMvpMat;                     // mvp变换矩阵
        std::shared_ptr<Lights> targetLights;       // 光照信息
        std::shared_ptr<CameraSystem> targetCamera; // 视口信息

        // TODO renderTarget需要包含的具体的属性
        // 在渲染队列中，每个对象都应该包含一些必要的数据，例如：

        // 顶点缓冲对象（Vertex Buffer Object，VBO）的引用或数据；
        // 索引缓冲对象（Index Buffer Object，IBO）的引用或数据；
        // 渲染状态（渲染状态包括渲染目标、深度测试、剪裁等）；
        // 着色器程序（Shader Program）的引用或数据；
        // 纹理（Texture）的引用或数据；
        // 矩阵变换（Transformation）的数据，例如物体的位置、旋转和缩放等；
        // 其他可选的数据，例如颜色、法线等。

        // 顶点数据：每个对象需要包含一个顶点数据缓冲区，其中存储了每个顶点的位置、法向量、纹理坐标等信息。这些数据是使用OpenGL中的顶点缓冲区对象（Vertex Buffer Object）存储的。

        // 索引数据：索引缓冲区对象（Index Buffer Object）用于存储每个三角形的顶点索引。

        // 材质数据：包括每个对象的纹理贴图、漫反射颜色、环境光反射颜色、高光反射颜色和光泽度等材质属性。

        // 变换矩阵：每个对象需要一个变换矩阵，用于将对象从模型空间转换到世界空间，再转换到相机空间和投影空间。

        // 光照数据：光源位置、光源颜色和光源类型等。

        // 视口数据：包括视口的宽度、高度、视野角度、近剪裁面和远剪裁面等。

    public:
        ~RenderTarget();
        void initialize(std::shared_ptr<Mesh> _targetMesh, std::shared_ptr<Shader> _targetShader, std::shared_ptr<Texture> _targetTexture);
        void setUniform();
    };

} // namespace Elysian
