#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 scale;
uniform mat4 offset;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * scale * offset * vec4(aPos, 1.0);
}
