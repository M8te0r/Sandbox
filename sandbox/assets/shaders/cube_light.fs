#version 330 core
out vec4 FragColor;
  

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
} vs_in;

// uniform vec3 objectColor;
// uniform vec3 lightColor;


void main()
{



    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}