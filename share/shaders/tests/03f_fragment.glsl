
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	float intensity = dot(vNormal, iLightDir);
	intensity = (1.0 + intensity) * 0.5;
	vec2 tex_coord = vTexCoord.xy / vTexCoord.z;
	if (false) {
		fragColor = vec4(255, 255, 255, 0);
	}
	else if (false) {
		fragColor = vec4(intensity, intensity, intensity, 0);
	}
	else {
		fragColor = vec4(texture(iDiffuse, tex_coord).rgb * intensity, 1);
		//fragColor = vec4(texture(iDiffuse, vTexCoord).rgb, 1);
		//fragColor = vec4(vec3(vTexCoord, 0) * intensity, 1);
	}
}
