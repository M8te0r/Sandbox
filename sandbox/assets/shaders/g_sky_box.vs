#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 MVP;

// 天空盒的viewport变换
void main()
{
    // 移除了model矩阵，因为skybox并不会根据camera的移动改变相对关系
    TexCoords = aPos;
    // vec4 pos = projection * view * vec4(aPos, 1.0);
    // vec4 pos = MVP * vec4(aPos, 1.0);
    vec4 pos = projection * view * model * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  