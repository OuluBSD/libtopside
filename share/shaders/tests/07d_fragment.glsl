in vec3 normal;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	float intensity = dot(vNormal, iLightDir);
	intensity = (1.0 + intensity) * 0.5;
	if (false) {
		fragColor = vec4(255, 255, 255, 0);
	}
	else if (true) {
		fragColor = vec4(intensity, intensity, intensity, 0);
	}
	else {
		fragColor = texture(iDiffuse, vTexCoord) * intensity;
	}
}
