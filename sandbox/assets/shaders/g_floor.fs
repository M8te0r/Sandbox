#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normals;
} vs_in;


uniform sampler2D texture1;


// 载入skybox的纹理
void main()
{    
    FragColor = texture(texture1, vs_in.TexCoords);
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    // FragColor =vec4(vec3(vs_in.Normals), 1.0);
}