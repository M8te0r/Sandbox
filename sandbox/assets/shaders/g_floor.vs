#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormals;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normals;
} vs_out;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

// 天空盒的viewport变换
void main()
{
    // 移除了model矩阵，因为skybox并不会根据camera的移动改变相对关系
    vs_out.FragPos=aPos;
    vs_out.TexCoords=aTexCoords;
    vs_out.Normals=aNormals;
    // vec4 pos = projection * view * vec4(aPos, 1.0);
    // vec4 pos = MVP * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}  