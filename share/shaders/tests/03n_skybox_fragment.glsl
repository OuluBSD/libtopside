
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	fragColor = vec4(texture(iCubeDiffuse, vTexCoord).xyz, 1.0);
}
