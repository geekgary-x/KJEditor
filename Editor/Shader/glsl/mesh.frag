#version 460 core
layout (location = 0) out vec4 FragColor;
layout (location = 0) in vec2 in_TexCoord;
layout (binding = 0) uniform sampler2D simple;
void main()
{
    FragColor = texture(simple, in_TexCoord);
}