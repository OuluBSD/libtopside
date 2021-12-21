in vec3 normal;

/*void mainImage(out vec4 o, vec2 uv) {
	
	//o = texture(iChannel0, uv);
	//o = vec4(uv.x, uv.y, 0.0, 1.0);
	o = vec4(1.0, 1.0, 0.0, 1.0);
}*/

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	float intensity = dot(vNormal, iLightDir);
	if (false) {
		fragColor = vec4(intensity, intensity, intensity, 0);
	}
	else {
		intensity = intensity * 0.5 + 0.5;
		fragColor = texture(iDiffuse, vTexCoord) * intensity;
	}
}
