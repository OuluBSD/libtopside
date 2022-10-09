in vec3 normal;

#define M_PI	3.1415926535897932384626433832795

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	//vec4 clr = texture(iStageColor1, vTexCoord);
    vec4 clr = texture(iDiffuse, vTexCoord.xy);
    fragColor = clr;
    fragColor = vec4(vTexCoord.x, vTexCoord.y, clr.x, 1);
}
