
// from https://www.shadertoy.com/view/XsfXWX

#define saturate(x) clamp(x,0.0,1.0)

vec3 PBR_HDRCubemap(vec3 sampleDir, float LOD_01)
{
    vec3 linearGammaColor_sharp = pow(texture( iCubeDiffuse, sampleDir ).rgb,vec3(2.2));
    vec3 linearGammaColor_blur  = pow(texture( iCubeIrradiance, sampleDir ).rgb,vec3(1));
    vec3 linearGammaColor = mix(linearGammaColor_sharp,linearGammaColor_blur,saturate(LOD_01));
    return linearGammaColor;
}



float G1V ( float dotNV, float k ) {
	return 1.0 / (dotNV*(1.0 - k) + k);
}

float GGX(vec3 N, vec3 V, vec3 L, float roughness, float F0) {
    	float alpha = roughness*roughness;
	vec3 H = normalize (V + L);

	float dotNL = clamp (dot (N, L), 0.0, 1.0);
	float dotNV = clamp (dot (N, V), 0.0, 1.0);
	float dotNH = clamp (dot (N, H), 0.0, 1.0);
	float dotLH = clamp (dot (L, H), 0.0, 1.0);

	float D, vis;
	float F;

	// NDF : GGX
	float alphaSqr = alpha*alpha;
	float pi = 3.1415926535;
	float denom = dotNH * dotNH *(alphaSqr - 1.0) + 1.0;
	D = alphaSqr / (pi * denom * denom);

	// Fresnel (Schlick)
	float dotLH5 = pow (1.0 - dotLH, 5.0);
	F = F0 + (1.0 - F0)*(dotLH5);

	// Visibility term (G) : Smith with Schlick's approximation
	float k = alpha / 2.0;
	vis = G1V (dotNL, k) * G1V (dotNV, k);

	return /*dotNL */ D * F * vis;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
	vec3 normal = normalize(vNormal);
	vec3 ray = iCameraDir;
	
	// material
	float metallic = 0.04;
	float spec_value = texture(iSpecular,vTexCoord.xy).r;
	float shininess_value = spec_value * 0.25 + 0.75; // hack
	float roughness = step(fract(shininess_value * 2.02), 0.5) + 0.1;
	float fresnel_pow = mix(5.0, 3.5,metallic);
	vec3 light_color = pow(vec3(1.0, 1.0, 1.0), vec3(2.2));
	vec3 clr = texture(iDiffuse,vTexCoord.xy).rgb;
	vec3 color_mod = vec3(1.0);
			
			
	// IBL
	vec3 ibl_diffuse = pow(texture(iDiffuse,vTexCoord.xy).rgb, vec3(2.2));
	vec3 ibl_reflection = pow(texture(iCubeIrradiance,reflect(ray,normal)).rgb, vec3(2.2));
	
	// fresnel
	float fresnel = max(1.0 - dot(normal,-ray), 0.0);
	fresnel = pow(fresnel,fresnel_pow);    
	
	// reflection        
	vec3 refl = pow(texture(iCubeDiffuse,reflect(ray,normal)).rgb, vec3(2.2));
	refl = mix(refl,ibl_reflection,(1.0-fresnel)*roughness);
	refl = mix(refl,ibl_reflection,roughness);
	
	// specular
	vec3 light = iLightDir;
	float power = 1.0 / max(roughness * 0.4,0.01);
	//vec3 spec = light_color * phong(light,ray,normal,power);
	vec3 spec = light_color * GGX(normal,-ray,light,roughness*0.7, 0.2);
	refl -= spec;
	
	// diffuse
	vec3 diff = ibl_diffuse * spec_value;
	diff = mix(diff * color_mod,refl,fresnel);        

	vec3 color = mix(diff,refl * color_mod,metallic) + spec;
	fragColor = vec4(pow(color, vec3(1.0/2.2)), 1.0);
    
}
