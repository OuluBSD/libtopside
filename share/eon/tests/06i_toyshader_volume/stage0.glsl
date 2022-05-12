
#define PI 3.14159265359
#define rot(a) mat2(cos(a + PI*0.5*vec4(0,1,3,0)))

// Dave_Hoskins hash
#define HASHSCALE3 vec3(.1031, .1030, .0973)
vec3 hash33( in vec3 p3 ){
	p3 = fract(p3 * HASHSCALE3);
    p3 += dot(p3, p3.yxz+19.19);
    return fract((p3.xxy + p3.yxx)*p3.zyx);
}

// triplanar mapping
vec4 tex3D( in sampler2D t, in vec3 p, in vec3 n ){
    n = abs(n);
    float tot = n.x + n.y + n.z;
	return (texture(t,p.yz)*n.x+texture(t,p.zx)*n.y+texture(t,p.xy)*n.z)/tot;
}

// noise with smooth derivative
float snoise( in vec3 x, const in float lod ) {
    float dim = 32.0 / exp2(lod);
    x = x * dim;
    vec3 p = floor(x);
    vec3 f = fract(x);
    f = f*f*(3.0-2.0*f);
    x = (p+f+0.5) / dim;
    return textureLod(iChannel0, x.xy, lod).r;
}

// distance estimator
float de( in vec3 p ) {
    float n = snoise(p*0.15+iTime*0.01, 0.0)-0.5;
    return length(p) - 1.0 + n*0.5;
}

// normal from central difference
vec3 getNormal( in vec3 p ) {
	vec3 e = vec3(0.0, 0.03, 0.0);
	return normalize(vec3(
		de(p+e.yxx)-de(p-e.yxx),
		de(p+e.xyx)-de(p-e.xyx),
		de(p+e.xxy)-de(p-e.xxy)));	
}

// approximation of the error function
// https://github.com/libretro/glsl-shaders/blob/master/blurs/blur9fast-vertical.glsl
float erf( in float x ) {
    //return tanh(1.202760580 * x);
	float sign_x = sign(x);
	float t = 1.0/(1.0 + 0.47047*abs(x));
	float result = 1.0 - t*(0.3480242 + t*(-0.0958798 + t*0.7478556))*exp(-(x*x));
	return result * sign_x;
}

// analytical volumetric fog applied around a sphere
// similar to http://www.iquilezles.org/www/articles/fog/fog.htm
float getFog( in vec3 start, in vec3 dir, in float dist ) {
    
    const float a = 7.000; // fog exponent
	const float b = 1.000; // sphere radius
    const float c = 500.0; // fog strength
    
    float k = start.x;
    float l = dir.x;
    float m = start.y;
    float n = dir.y;
    float o = start.z;
    float p = dir.z;
    float d = dot(start, dir);

    float res = exp(b-a*(+k*k*(n*n+p*p)
                         -m*m*(-1.0+n*n)
                         -o*o*(-1.0+p*p)
                         -2.0*k*l*o*p
                         -2.0*m*n*(k*l+o*p) ));
    res *= erf( sqrt(a)*(d+dist) ) - erf( sqrt(a)*d );
    res *= (0.5/sqrt(a)) * sqrt(PI) * c;
    
    return res;
    
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    
    vec2 uv = (fragCoord - iResolution.xy * 0.5) / iResolution.y;
	
	vec3 from = vec3(0, 0, -5.0);
	vec3 dir = normalize(vec3(uv*0.5, 1.0));
	
    if (iMouse.z > 0.5) {
        vec2 mouse=(iMouse.xy - iResolution.xy*0.5) / iResolution.y * 2.5;
        mat2 rotxz = rot(-mouse.x);
        mat2 rotxy = rot(mouse.y);
        from.zy *= rotxy;
        from.xz *= rotxz;
        dir.zy  *= rotxy;
        dir.xz  *= rotxz;
    }
    
	float totdist = 0.0;
	for (int steps = min(iFrame, 0) ; steps < 300 ; steps++) {
		vec3 p = from + totdist * dir;
        float dist = de(p);
		if (dist < 0.0001)
            break;
        totdist += min(dist*0.2, 1.0);
	}
    
    vec3 p = from + totdist * dir;
    
    if (length(p) < 2.0) {
        vec3 n = getNormal(p);
        
        vec3 albedo = tex3D(iChannel1, p*0.5+iTime*0.01, n).rgb;
        albedo = sqrt(albedo.brg);
        
        // main light source
        const vec3 pri = vec3(0.8, 0.7, 0.5)*2.0;
        fragColor.rgb += albedo * pri * max(0.0, dot(n, normalize(vec3(7, 10, -3))));
        
        // secondary light source
        const vec3 sec = vec3(0.1, 0.2, 0.3);
        fragColor.rgb += albedo * sec * max(0.0, dot(n, normalize(vec3(-7, -4, 2))));
        
    } else {
        fragColor = vec4(0.01);
    }
    
    // apply fog
    float d = getFog(from, dir, totdist);
    d = 1.0 - exp(-d);
    //d = min(d, 1.0);
    fragColor.rgb = mix(fragColor.rgb, vec3(0.5, 0.6, 0.7), d);
    
    // gamma correction
    fragColor.rgb = pow(fragColor.rgb, vec3(1.0/2.2));
    // dithering
    fragColor.rgb += (hash33(vec3(fragCoord, iFrame))-0.5)*0.02;

}
