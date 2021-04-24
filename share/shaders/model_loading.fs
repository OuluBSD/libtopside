#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec4 in_color;
uniform bool is_colored_only;

void main()
{    
	if (is_colored_only)
		FragColor = in_color;
	else
		FragColor = texture(texture_diffuse1, TexCoords);
}
