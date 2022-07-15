#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec4 in_color;
uniform bool disable_textures;

void main()
{    
	if (disable_textures)
		FragColor = in_color;
	else
		FragColor = texture(texture_diffuse1, TexCoords);
}
