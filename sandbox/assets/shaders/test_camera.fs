#version 330 core
out vec4 FragColor;
  

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
} vs_in;

// uniform vec3 objectColor;
// uniform vec3 lightColor;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform sampler2D texture1;

void main()
{
    // FragColor = vec4(lightColor * objectColor, 1.0);
    // FragColor = vec4(vs_in.FragPos, 1.0);
    // FragColor = vec4(vec3(0.5), 1.0);


    vec3 color = vec3(0.5, 0.5, 0.5);

    // ambient
    vec3 ambient = 0.05 * color;
    // diffuse
    vec3 lightDir = normalize(lightPos - vs_in.FragPos);
    vec3 normal = normalize(vs_in.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(viewPos - vs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color

    // FragColor = vec4(ambient + diffuse + specular, 1.0);
    // FragColor = vec4(vs_in.FragPos, 1.0);
    FragColor = texture(texture1, vs_in.TexCoords);
}