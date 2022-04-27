#version 460 core
layout (location = 0) out vec4 FragColor;
layout (location = 0) in vec2 in_TexCoord;
layout (location = 1) in flat vec3 in_CameraPos; 

layout(std140, binding = 1) uniform block2
{
	vec3 u_LightPos;
    vec3 u_LightAmbientColor;
    vec3 u_LightDiffuseColor;
    vec3 u_LightSpecularColor;
};


layout (binding = 0) uniform sampler2D simple;

void main()
{
    FragColor = vec4(u_LightPos, 1.0f);
}