vec4 fetch(in sampler2D channel, in vec2 xy) {
    return texture(channel, xy / iResolution.xy);
}

vec2 Hash12(in float t) {
	vec3 p3 = fract(t * vec3(0.1031, 0.1030, 0.0973));
	p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xx + p3.yz) * p3.zy);
}

// vec4(position, orientation)
vec4 getCamera(in float t) {
    float id = floor(t), local = fract(t);
    vec2 a = Hash12(id), b = Hash12(id + 1.0), c = Hash12(id + 2.0);
    vec2 mid1 = 0.5 * (a + b), mid2 = 0.5 * (b + c);

    float tInv = 1.0 - local;
    vec2 pos = mid1 * tInv * tInv + 2.0 * b * tInv * local + mid2 * local * local;
    vec2 dir = normalize(mid1 * (local - 1.0) + (1.0 - 2.0 * local) * b + mid2 * local);

    return vec4(pos, dir);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 center = 0.5 * iResolution.xy;
    vec2 uv = (fragCoord - center) / iResolution.y;

    vec2 oUv = uv;

    vec4 camera = getCamera(iTime * 0.25);

    vec2 pos = camera.xy * 5.0 - 2.5;
    uv -= pos;

    vec2 face = camera.zw;
    uv *= mat2(face.yx, -face.x, face.y);

    fragColor = fetch(iChannel0, uv * iResolution.y + center);
}