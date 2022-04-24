#version 460 core
layout (location = 0) in vec3 in_Position; 
layout (location = 1) in vec3 in_Normal; 
layout (location = 2) in vec2 in_TexCoord; 

layout (location = 0) out vec2 out_TexCoord; 

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

void main()
{
    gl_Position = u_ViewProjection * vec4(in_Position, 1.0);
	out_TexCoord = in_TexCoord;
}