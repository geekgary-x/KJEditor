#version 460 core
layout (location = 0) out vec4 FragColor;
layout (location = 0) in vec2 in_TexCoord;
layout (location = 1) in flat vec3 in_CameraPos; 
layout (binding = 0) uniform sampler2D simple;
void main()
{
    FragColor = vec4(in_CameraPos, 1.0f);
}