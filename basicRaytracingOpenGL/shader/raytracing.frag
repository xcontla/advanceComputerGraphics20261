#version 410 core
in vec2 texCoord;
out vec4 color;
void main()
{
    color = vec4(texCoord, 0.0, 1.0);
}