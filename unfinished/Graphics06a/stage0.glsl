#define TMIN     0.1
#define TMAX     5000.0

#define ID_NONE           -1.0
#define ID_FLOOR           0.10
#define ID_CEILING         0.11
#define ID_WALL_BACK       0.12
#define ID_WALL_RIGHT      0.13
#define ID_WALL_LEFT       0.14
#define ID_LIGHT           0.15
#define ID_SPHERE_REFRACT  0.16
#define ID_SPHERE_REFLECT  0.17
#define ID_VOID            1.0

#define GLASS_REFRACTION_INDEX    1.5

// http://www.graphics.cornell.edu/online/box/data.html
const vec4 FLOOR          = vec4(278.0, 0.0, 279.6, ID_FLOOR);
const vec4 CEILING        = vec4(278.0, 0.0, 279.6, ID_CEILING);
const vec4 WALL_BACK      = vec4(278.0, 274.4, 0.0, ID_WALL_BACK);
const vec4 WALL_RIGHT     = vec4(0.0, 274.4, 279.6, ID_WALL_RIGHT);
const vec4 WALL_LEFT      = vec4(0.0, 274.4, 279.6, ID_WALL_LEFT);
const vec4 LIGHT          = vec4(65.0, 0.0, 52.5, ID_LIGHT);
const vec4 SPHERE_REFRACT = vec4(80.0, 0.0, 0.0, ID_SPHERE_REFRACT);
const vec4 SPHERE_REFLECT = vec4(100.0, 0.0, 0.0, ID_SPHERE_REFLECT);

const vec3 lightPos = vec3(278.0, 0.0, 279.6);

float sdBox(in vec3 p, in vec3 box) {
   vec3 d = abs(p) - box;
   return min(max(d.x, max(d.y, d.z)), 0.0) + length(max(d, 0.0));
}

float sdSphere(vec3 p, float s) {
   return length(p) - s;
}

vec2 intersectSpheres(in vec3 p, bool refrSph) {
    // hit object ID is stored in res.x, distance to object is in res.y

    vec2 res = vec2(ID_VOID, 2000.0);

    if (refrSph) res = vec2(ID_SPHERE_REFRACT, sdSphere(p + vec3(380.0, 468.8, 166.0), SPHERE_REFRACT.x));
    vec2 obj = vec2(ID_SPHERE_REFLECT, sdSphere(p + vec3(190.0, 448.8, 365.0), SPHERE_REFLECT.x));
    if (obj.y < res.y) res = obj;

    return res;
}

vec2 intersect(in vec3 p, bool refrSph) {
    // hit object ID is stored in res.x, distance to object is in res.y

    vec2 res = vec2(ID_VOID, 2000.0);

    vec2 obj = vec2(ID_LIGHT, sdBox(p + lightPos, LIGHT.xyz));
    if (obj.y < res.y) res = obj;

    obj = vec2(ID_FLOOR, sdBox(p + vec3(278.0, 548.8, 279.6), FLOOR.xyz));
    if (obj.y < res.y) res = obj;
    obj = vec2(ID_CEILING, sdBox(p + vec3(278.0, 0.0, 279.6), CEILING.xyz));
    if (obj.y < res.y) res = obj;
    obj = vec2(ID_WALL_BACK, sdBox(p + vec3(278.0, 274.4, 559.2), WALL_BACK.xyz));
    if (obj.y < res.y) res = obj;
    obj = vec2(ID_WALL_RIGHT, sdBox(p + vec3(556.0, 274.4, 279.6), WALL_RIGHT.xyz));
    if (obj.y < res.y) res = obj;
    obj = vec2(ID_WALL_LEFT, sdBox(p + vec3(0.0, 274.4, 279.6), WALL_LEFT.xyz));
    if (obj.y < res.y) res = obj;

    obj = intersectSpheres(p, refrSph);
    if (obj.y < res.y) res = obj;

    return res;
}

vec2 intersect(in vec3 p) {
    return intersect(p, true);
}

vec2 raymarchScene(in vec3 ro, in vec3 rd, in float tmin, in float tmax, bool refrSph) {
    vec3 res = vec3(ID_NONE);
    float t = tmin;
    for (int i = 0; i < 250; i++) {
        vec3 p = ro + rd * t;
        res = vec3(intersect(p, refrSph), t);
        float d = res.y;
        if (d < (0.001 * t) || t > tmax)
            break;
        t += 0.5 * d;
    }
    return res.xz;
}

vec3 getNormal(in vec3 p) {
    vec2 eps = vec2(0.005, 0.0);
    return normalize(vec3(intersect(p + eps.xyy).y - intersect(p - eps.xyy).y,
                          intersect(p + eps.yxy).y - intersect(p - eps.yxy).y,
                          intersect(p + eps.yyx).y - intersect(p - eps.yyx).y));
}

float raymarchAO(in vec3 ro, in vec3 rd, float tmin) {
    float ao = 0.0;
    for (float i = 0.0; i < 5.0; i++) {
        float t = tmin + pow(i / 5.0, 2.0);
        vec3 p = ro + rd * t;
        float d = intersect(p).y;
        ao += max(0.0, t - 0.5 * d - 0.05);
    }
    return 1.0 - 0.00125 * ao;
}

float raymarchShadows(in vec3 ro, in vec3 rd, float tmin, float tmax) {
    float sh = 1.0;
    float t = tmin;
    for(int i = 0; i < 50; i++) {
        vec3 p = ro + rd * t;
        float d = intersectSpheres(p, true).y;
        sh = min(sh, 16.0 * d / t);
        t += 0.5 * d;
        if (d < (0.001 * t) || t > tmax)
            break;
    }
    return sh;
}

vec3 getLightColor(in vec2 obj, in vec3 pos, in vec3 rd, in vec3 nor) {
    vec3 difColor = vec3(18.4, 15.6, 8.0);

    // main light
    vec3 lightDir = normalize(vec3(-lightPos.x, -125.0, -lightPos.z) - pos);
    float lightDist = length(vec3(-lightPos.x, -125.0, -lightPos.z) - pos);
    float dif = max(0.0, dot(nor, lightDir));
    vec3 h = normalize(-rd + lightDir);
    float spe = pow(clamp(dot(h, nor), 0.0, 1.0), 4.0);
    vec3 lightColor = dif * difColor * (1.0 / lightDist);
    lightColor += 0.25 * dif * spe * difColor;

    lightDir = normalize(vec3(-lightPos.x, 350.0, -lightPos.z) - pos);
    float sha = clamp(raymarchShadows(pos, lightDir, 0.5, 500.0), 0.0, 1.0);
    float id = obj.x;
    if (id != ID_LIGHT && id != ID_CEILING) lightColor *= sha;

    // light bounce on back wall
    lightDir = normalize(vec3(-278.0, -274.4, -55.0) + pos);
    lightDist = length(vec3(-278.0, -274.4, -55.0) + pos);
    dif = max(0.0, dot(nor, lightDir));
    h = normalize(-rd + lightDir);
    spe = pow(clamp(dot(h, nor), 0.0, 1.0), 2.0);
    lightColor += dif * vec3(0.25, 0.175, 0.1) * (1.0 / lightDist);
    lightColor += 0.5 * dif * spe * vec3(0.25, 0.175, 0.1);

    // light bounce on right wall
    lightDir = normalize(vec3(-556.0, -274.4, -279.6) - pos);
    lightDist = length(vec3(-556.0, -274.4, -279.6) - pos);
    dif = max(0.0, dot(nor, lightDir));
    h = normalize(-rd + lightDir);
    spe = pow(clamp(dot(h, nor), 0.0, 1.0), 2.0);
    lightColor += dif * vec3(0.0, 0.5, 0.0) * (1.0 / lightDist);
    lightColor += 0.5 * dif * spe * vec3(0.0, 0.5, 0.0);

    // light bounce on left wall
    lightDir = normalize(vec3(0.0, -274.4, -279.6) - pos);
    lightDist = length(vec3(0.0, -274.4, -279.6) - pos);
    dif = max(0.0, dot(nor, lightDir));
    h = normalize(-rd + lightDir);
    spe = pow(clamp(dot(h, nor), 0.0, 1.0), 2.0);
    lightColor += dif * vec3(1.5, 0.0, 0.0) * (1.0 / lightDist);
    lightColor += 0.5 * dif * spe * vec3(1.5, 0.0, 0.0);

    float amb = clamp(0.75 + 0.25 * nor.y, 0.0, 1.0);
    lightColor += 0.015 * amb * difColor;

    return lightColor;
}

vec3 getWallColor(in vec2 obj) {
    vec3 color = vec3(0.0);
    float id = obj.x;
    if (id == ID_FLOOR) color = vec3(0.25, 0.175, 0.1);
    if (id == ID_CEILING) color = vec3(0.25, 0.175, 0.1);
    if (id == ID_WALL_BACK) color = vec3(0.25, 0.175, 0.1);
    if (id == ID_WALL_RIGHT) color = vec3(0.0, 0.05, 0.0);
    if (id == ID_WALL_LEFT) color = vec3(0.25, 0.0, 0.0);
    if (id == ID_LIGHT) color = vec3(10.0);
    return color;
}

vec3 getBoxColor(in vec2 obj, in vec3 pos, in vec3 rd, in vec3 nor) {
    vec3 color = getWallColor(obj);
    float occ = clamp(raymarchAO(pos, nor, 80.0), 0.0, 1.0);
    color *= getLightColor(obj, pos, rd, nor) * occ;
    return color;
}

vec3 getMirrorBallColor(in vec3 pos, in vec3 rd, in vec3 nor) {
    vec3 refl = reflect(rd, nor);
    vec2 robj = raymarchScene(pos, refl, TMIN, TMAX, true);
    vec3 rpos = pos + refl * robj.y;
    vec3 rnor = getNormal(rpos);
    vec3 color = getWallColor(robj);
    float occ = clamp(raymarchAO(rpos, rnor, 80.0), 0.0, 1.0);
    if (robj.x == ID_SPHERE_REFRACT) {
        vec3 rrefl = reflect(refl, rnor);
        vec2 reflObj = raymarchScene(rpos, rrefl, TMIN, TMAX, true);
        vec3 reflPos = rpos + rrefl * reflObj.y;
        vec3 reflNor = getNormal(reflPos);
        float reflOcc = clamp(raymarchAO(reflPos, reflNor, 80.0), 0.0, 1.0);
        vec3 refr = refract(refl, rnor, 1.0 / (GLASS_REFRACTION_INDEX * 2.0));
        robj = raymarchScene(rpos, refr, TMIN, TMAX, false);
        rpos = rpos + refr * robj.y;
        rnor = getNormal(rpos);
        color = getWallColor(robj);
        float occ = clamp(raymarchAO(rpos, rnor, 80.0), 0.0, 1.0);
        color *= occ;
        color = mix(color, getWallColor(reflObj) * reflOcc, 0.02);
    }
    color *= getLightColor(robj, rpos, refl, rnor) * occ;

    return color;
}

vec3 getGlassBallColor(in vec3 pos, in vec3 rd, in vec3 nor) {
    vec3 refl = reflect(rd, nor);
    vec2 reflObj = raymarchScene(pos, refl, TMIN, TMAX, true);
    vec3 reflPos = pos + refl * reflObj.y;
    vec3 reflNor = getNormal(reflPos);
    float reflOcc = clamp(raymarchAO(reflPos, reflNor, 80.0), 0.0, 1.0);
    vec3 refr = refract(rd, nor, 1.0 / GLASS_REFRACTION_INDEX);
    vec2 robj = raymarchScene(pos, refr, TMIN, TMAX, false);
    vec3 rpos = pos + refr * robj.y;
    vec3 rnor = getNormal(rpos);
    vec3 color = getWallColor(robj);
    float occ = clamp(raymarchAO(rpos, rnor, 80.0), 0.0, 1.0);
    if (robj.x == ID_SPHERE_REFLECT) {
        vec3 rrefl = reflect(refr, rnor);
        robj = raymarchScene(rpos, rrefl, TMIN, TMAX, true);
        rpos = rpos + rrefl * robj.y;
        rnor = getNormal(rpos);
        color = getWallColor(robj);
        if (robj.x == ID_SPHERE_REFRACT) {
            vec3 rrefr = refract(rrefl, rnor, 1.0 / (GLASS_REFRACTION_INDEX * 2.0));
            vec2 rrobj = raymarchScene(rpos, rrefr, TMIN, TMAX, false);
            vec3 rrpos = rpos + rrefr * rrobj.y;
            vec3 rrnor = getNormal(rrpos);
            color = getWallColor(rrobj);
            float occ = clamp(raymarchAO(rrpos, rrnor, 80.0), 0.0, 1.0);
            color *= occ;
        }
        float occ = clamp(raymarchAO(rpos, rnor, 80.0), 0.0, 1.0);
        color *= occ;
    }
    vec3 reflColor = getWallColor(reflObj);
    reflColor *= reflOcc;
    if (reflObj.x == ID_SPHERE_REFLECT) {
        vec3 rrefl = reflect(refl, reflNor);
        reflObj = raymarchScene(reflPos, rrefl, TMIN, TMAX, true);
        reflPos = reflPos + rrefl * reflObj.y;
        reflNor = getNormal(reflPos);
        reflColor = getWallColor(reflObj);
        float occ = clamp(raymarchAO(reflPos, reflNor, 80.0), 0.0, 1.0);
        reflColor *= occ;
    }
    color *= getLightColor(robj, rpos, refr, rnor) * occ;
    color = mix(color, reflColor, 0.02);

    return color;
}

vec3 getFloorColor(in vec2 obj, in vec3 pos, in vec3 rd, in vec3 nor) {
    vec3 color = getBoxColor(obj, pos, rd, nor);
    vec3 lightDir = normalize(vec3(-lightPos.x, 500.0, -lightPos.z) - pos);
    vec2 robj = raymarchScene(pos, lightDir, TMIN, TMAX, true);
    if (robj.x == ID_SPHERE_REFRACT) {
        vec3 rpos = pos + lightDir * robj.y;
        vec3 rnor = getNormal(rpos);
        vec3 refr = refract(lightDir, rnor, 1.0 / GLASS_REFRACTION_INDEX);
        robj = raymarchScene(rpos, refr, TMIN, TMAX, false);
        rpos = rpos + refr * robj.y;
        rnor = getNormal(rpos);
        if (robj.x == ID_LIGHT) {
            vec3 difColor = vec3(18.4, 15.6, 8.0);
            float occ = clamp(raymarchAO(pos, nor, 80.0), 0.0, 1.0);
            color = mix(color, difColor * occ, 0.05);
        }
    }
    return color;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 p = (-iResolution.xy + 2.0 * fragCoord.xy) / iResolution.y;

    vec3 eye = vec3(278.0, 273.0, -800.0);
    vec2 rot = 6.2831 * (vec2(0.085, 0.01) + vec2(1.0, 0.5) * (iMouse.xy - iResolution.xy * 0.5) / iResolution.x);
    eye.yz = cos(rot.y) * eye.yz + sin(rot.y) * eye.zy * vec2(-1.0, 1.0);
    eye.xz = cos(rot.x) * eye.xz + sin(rot.x) * eye.zx * vec2(1.0, -1.0);

    vec3 ro = eye;
    vec3 ta = vec3(-278.0, -274.4, -279.6);

    vec3 cw = normalize(ta - ro);
    vec3 cu = normalize(cross(vec3(0.0, 1.0, 0.0), cw));
    vec3 cv = normalize(cross(cw, cu));
    mat3 cam = mat3(cu, cv, cw);

    vec3 rd = cam * normalize(vec3(p.xy, 2.75));

    // background
    vec3 color = vec3(0.0);

    vec2 obj = raymarchScene(ro, rd, TMIN, TMAX, true);
    float id = obj.x;
    if (id != ID_VOID) {
        float t = obj.y;
        vec3 pos = ro + rd * t;
        vec3 nor = getNormal(pos);

        if (id == ID_SPHERE_REFRACT) {
            color = getGlassBallColor(pos, rd, nor);
        }
        else if (id == ID_SPHERE_REFLECT) {
            color = getMirrorBallColor(pos, rd, nor);
        }
        else if (id == ID_FLOOR) {
            color = getFloorColor(obj, pos, rd, nor);
        }
        else {
            color = getBoxColor(obj, pos, rd, nor);
        }
    }

    // gamma correction
    vec3 gamma = vec3(1.0 / 2.2);
    fragColor = vec4(pow(color, gamma), 1.0);
}