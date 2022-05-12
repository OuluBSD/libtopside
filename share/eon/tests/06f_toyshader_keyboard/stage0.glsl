
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec3 res = iResolution;
	vec2 uv = fragCoord / res.xy;
	fragColor = texture(iChannel0, uv);
}
