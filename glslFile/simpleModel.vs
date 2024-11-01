#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;

#out vec2 TexCoord;
out vec2 UV

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	UV = aUV
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	#TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}