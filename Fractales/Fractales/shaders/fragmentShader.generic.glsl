#version 330 core

in vec3 RGB;
out vec4 FragColor;

void main()
{
	FragColor = vec4(RGB, 1.0f);
}