#version 460 core
layout (location = 0) in vec3 aPosition; 
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTexCoord; 

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

void main()
{
    gl_Position = u_ViewProjection * vec4(aPosition, 1.0);
}