/**
 * -----------------------------------------------------------
 * - Scene Marching and Rendering
 * -----------------------------------------------------------
 *
 * A simple test scene consisting of a shader ball model and wooden platform/table.
 *
 * The shader ball has two different materials applied to it:
 *
 *     - Glossy white material. Low roughness and metallicness.
 *     - Black speckled material. Mid roughness and high metalicness.
 *
 * For the wood:
 *
 *     - Low metallic, roughness is based on .r component.
 *     - Simple bump mapping applied (only to direct lighting for performance consideration).
 *
 * For the lighting:
 *
 *     - Cook-Torrance Specular
 *     - Lambertian Diffuse
 *     - Single bounce reflection
 *     - Scene-based ambient occlusion
 */

//--------------------------------------------
// Defines for improved quality
//--------------------------------------------

/**
 * Toggles changes to:
 *
 *     - Enable bump mapping on ambient lighting (default: direct only)
 *     - Increase shadow marching steps to 32 (default: 16)
 *     - Increase reflection raymarching steps to 100 (default: 50)
 *     - Increase ambient environment sampling steps to 16 (default: 8)
 */

//#define HIGH_QUALITY

//--------------------------------------------
// General defines and constants
//--------------------------------------------

#define Epsilon           0.001
#define NearClip          Epsilon
#define FarClip           14.0
#define PI                3.14159
#define ONE_OVER_PI       0.31831
#define ONE_OVER_TWO_PI   0.15915

#ifdef HIGH_QUALITY
#define IBLSteps          16.0
#else
#define IBLSteps          8.0
#endif

const vec3  CamOrigin   = vec3(0.0, 2.5, 0.0);
const vec3  CamLookAt   = vec3(0.0, 1.1, 0.0);
const float CamFOV      = radians(45.0);
const vec3  SunLightDir = normalize(vec3(1.65, 2.0, 0.5));

//------------------------------------------------------------------------------------------
// Ray / Camera
//------------------------------------------------------------------------------------------

struct Ray
{
	vec3 o;
    vec3 d;
};

Ray Ray_LookAt(in vec2 uv, in vec3 o, in vec3 d)
{
    vec3 forward = normalize(d - o);
    vec3 right   = normalize(cross(forward, vec3(0.0, 1.0, 0.0)));
    vec3 up      = normalize(cross(right, forward));

    uv = (uv * 2.0) - 1.0;

    float u = tan(CamFOV) * distance(o, d);
    float v = u * (iResolution.y / iResolution.x);

    return Ray(o, normalize(d + (uv.x * u * right) + (uv.y * v * up) - o));
}

vec3 OrbitAround(vec3 origin, float radius, float rate)
{
    float time = iTime + 4.0f;
  	return vec3((origin.x + (radius * cos(time * rate))), (origin.y), (origin.z + (radius * sin(time * rate))));
}

//------------------------------------------------------------------------------------------
// Scene
//------------------------------------------------------------------------------------------

// Credit for simple shapes to http://iquilezles.org/www/articles/distfunctions/distfunctions.htm
vec3  RotX(in vec3 p, float a)        { float s = sin(a); float c = cos(a); return vec3(p.x, (c * p.y) - (s * p.z), (s * p.y) + (c * p.z)); }
vec3  Repeat(vec3 p, vec3 c)          { return mod(p, c) - (0.5 * c); }
float smin(float a, float b, float k) { float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0); return mix(b, a, h) - k*h*(1.0 - h); }
float Box(vec3 p, vec3 b)             { vec3 d = abs(p) - b; return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0)); }
float Sphere(vec3 p, float r)         { return length(p) - r; }
float Cylinder(vec3 p, vec2 h)        { vec2 d = abs(vec2(length(p.xz),p.y)) - h; return min(max(d.x,d.y),0.0) + length(max(d,0.0)); }
vec2  U(vec2 d1, vec2 d2)             { return (d1.x < d2.x) ? d1 : d2; }
vec2  S(vec2 d2, vec2  d1 )           { return (-d1.x > d2.x) ? -d1 : d2; }

vec2 ShaderBall(vec3 p)
{
    vec3 spos = p - vec3(0.0, 1.5, 0.0);
    
    vec2 ts   = vec2(max(Sphere(spos, 1.0), -Sphere(spos, 0.8)), 9.0);                // Hollow top sphere
    vec2 tsi  = vec2(Sphere(spos, 0.725), 2.0);                                       // Inner sphere core
    vec2 tsc  = vec2(Sphere(spos - vec3(0.0, 0.4, 0.8), 0.55), 3.0);                  // Cut into side of top sphere
    vec2 rc   = vec2(Box(RotX(spos, PI * 0.15), vec3(2.0, 0.05, 2.0)), 4.0);          // Ring cut into top sphere
    
    vec2 st   = vec2(Cylinder(p - vec3(0.0, 0.1, 0.0), vec2(mix(0.8, 0.3, clamp(p.y - 0.125, 0.0, 1.0)), 0.2)), 5.0);    // Stand wide base      
    vec2 stc  = vec2(Cylinder(Repeat(p, vec3(0.5, 0.0, 0.5)), vec2(0.125, 1.0)), 6.0);                                   // Stand ridge cuts
    vec2 stm  = vec2(Cylinder(p - vec3(0.0, 0.35, 0.0), vec2(0.5, 0.35)), 5.0);       // Thinner stand middle
    
    st   = S(st, stc);
    st.x = smin(st.x, stm.x, 0.2);                         
    
    vec2 b    = vec2(Cylinder(p - vec3(0.0, 0.025, 0.0), vec2(1.0, 0.05)), 8.0);      // Base
       
    vec2 result = S(ts, tsc);
         result = S(result, rc);
         result = U(result, tsi);
         result = U(result, st);
         result = U(result, b);
    
    return result;
}

// Returns vec2(sdf distance, surface/material id)
vec2 Scene(in vec3 p)
{
    return U(ShaderBall(p), 
             vec2(Box(p + vec3(0.0, 0.5, 0.0), vec3(10.0, 0.5, 4.0)), 1.0));  // Wood platform/table
}

vec2 March(in Ray ray, int maxSteps)
{
    float depth = NearClip;
    float id = 1.0;
    
    for(int i = 0; i < maxSteps; ++i)
    {
        vec2 sdf = Scene(ray.o + (ray.d * depth));
        
        if(sdf.x < Epsilon)
        {
            id = sdf.y;
            break;
        }
        
        if(sdf.x >= FarClip)
        {
            break;
        }
        
        depth += sdf.x;
    }
    
    return vec2(clamp(depth, NearClip, FarClip), id);
}

float Shadow(vec3 pos)
{
    float shadow = 1.0;
    float depth  = 1.0;
    
#ifdef HIGH_QUALITY
    for(int i = 0; i < 32; ++i)
#else
    for(int i = 0; i < 24; ++i)
#endif
    {
        vec2 sdf = Scene(pos + (SunLightDir * depth));
        
        shadow = min(shadow, (8.0 * sdf.x) / depth);
        depth += sdf.x;
        
        if(sdf.x < 0.001)
        {
            shadow = 0.0;
            break;
        }
    }
    
    return clamp(shadow, 0.0, 1.0);
}

vec3 SceneNormal(in vec3 p, in float d)
{
    vec2 eps = vec2(0.001 * d, 0.0);
    return normalize(vec3(Scene(p + eps.xyy).x - Scene(p - eps.xyy).x,
                          Scene(p + eps.yxy).x - Scene(p - eps.yxy).x,
                          Scene(p + eps.yyx).x - Scene(p - eps.yyx).x));
}

//------------------------------------------------------------------------------------------
// Sampling and Material
//------------------------------------------------------------------------------------------

vec3 SampleEnvironment(in vec3 reflVec)
{
    reflVec = normalize(reflVec);
    return texture(iChannel3, reflVec).rgb;
}

struct Material
{
    vec3  albedo;
    vec3  bump;
    float roughness;
    float metallic;
};

void GetBumpNormal(in vec3 pos, inout Material mat, int id)
{
    if(id != 1)
    {
        return;    // We only bump map the wood material
    }
    
    vec2 uv  = pos.xz * 0.25;
    vec2 eps = vec2(0.001, 0.0);

    float sampleU = texture(iChannel0, uv - eps.yx).r;
    float sampleD = texture(iChannel0, uv + eps.yx).r;
    float sampleL = texture(iChannel0, uv - eps.xy).r;
    float sampleR = texture(iChannel0, uv + eps.xy).r;

   	vec3 delta = vec3(
        (sampleL * sampleL - sampleR * sampleR), 
        0.0, 
        (sampleU * sampleU - sampleD * sampleD));

    mat.bump = normalize(mat.bump + (delta * 2.0));
}

Material CreateMaterial(in vec3 pos, in vec3 norm, in int id)
{
    Material mat;
    
    mat.albedo    = vec3(1.0);    // Default glossy white
    mat.roughness = 0.01;
    mat.metallic  = 0.0;
    mat.bump      = norm;
    
    if(id == 1)                   // Wood
    {
        mat.albedo    = textureLod(iChannel0, pos.xz * 0.25, 0.0).rgb;
        mat.roughness = 0.01 + (mat.albedo.r * 0.2);
        
        return mat;
    }
    
    if(id == 2)                   // Black sphere
    {
        mat.albedo    = vec3(0.1) * texture(iChannel1, pos.xy * 10.0).r;
        mat.roughness = 0.3;
        mat.metallic  = 1.0;
        
        return mat;
    }
    
    return mat;
}

//------------------------------------------------------------------------------------------
// PBR (see https://www.shadertoy.com/view/MsXBzl for documentation)
//------------------------------------------------------------------------------------------

vec3 CalculateDiffuse(
    in vec3 albedo)
{                              
    return (albedo * ONE_OVER_PI);
}

vec3 CalculateHalfVector(
    in vec3 toLight,
    in vec3 toView)
{
    return normalize(toLight + toView);
}

float CalculateNDF(
    in vec3  surfNorm,
    in vec3  halfVector,
    in float roughness)
{
    float a = (roughness * roughness);
    float halfAngle = dot(surfNorm, halfVector);
    
    return (a / (PI * pow((pow(halfAngle, 2.0) * (a - 1.0) + 1.0), 2.0)));
}

float CalculateAttenuation(
    in vec3  surfNorm,
    in vec3  vector,
    in float k)
{
    float d = max(dot(surfNorm, vector), 0.0);
 	return (d / ((d * (1.0 - k)) + k));
}

float CalculateAttenuationAnalytical(
    in vec3  surfNorm,
    in vec3  toLight,
    in vec3  toView,
    in float roughness)
{
    float k = pow((roughness + 1.0), 2.0) * 0.125;
    
    float lightAtten = CalculateAttenuation(surfNorm, toLight, k);
    float viewAtten  = CalculateAttenuation(surfNorm, toView, k);
    
    return (lightAtten * viewAtten);
}

float CalculateAttenuationIBL(
    in float roughness,
    in float normDotLight,
    in float normDotView)       
{
    float k = pow(roughness, 2.0) * 0.5;
    
    float lightAtten = (normDotLight / ((normDotLight * (1.0 - k)) + k));
    float viewAtten  = (normDotView / ((normDotView * (1.0 - k)) + k));
    
    return (lightAtten * viewAtten);
}

vec3 CalculateFresnel(
    in vec3 surfNorm,
    in vec3 toView,
    in vec3 fresnel0)
{
	float d = max(dot(surfNorm, toView), 0.0); 
    float p = ((-5.55473 * d) - 6.98316) * d;
        
    return fresnel0 + ((1.0 - fresnel0) * pow(1.0 - d, 5.0));
}

vec3 CalculateSpecularAnalytical(
    in    vec3  surfNorm,
    in    vec3  toLight,
    in    vec3  toView,
    in    vec3  fresnel0,  
    inout vec3  sfresnel,   
    in    float roughness)  
{
    vec3 halfVector = CalculateHalfVector(toLight, toView);
    
    float ndf      = CalculateNDF(surfNorm, halfVector, roughness);
    float geoAtten = CalculateAttenuationAnalytical(surfNorm, toLight, toView, roughness);
    
    sfresnel = CalculateFresnel(surfNorm, toView, fresnel0);
    
    vec3  numerator   = (sfresnel * ndf * geoAtten);
    float denominator = 4.0 * dot(surfNorm, toLight) * dot(surfNorm, toView);
    
    return (numerator / denominator);
}

vec2 Hammersley(float i, float numSamples)
{   
    uint b = uint(i);
    
    b = (b << 16u) | (b >> 16u);
    b = ((b & 0x55555555u) << 1u) | ((b & 0xAAAAAAAAu) >> 1u);
    b = ((b & 0x33333333u) << 2u) | ((b & 0xCCCCCCCCu) >> 2u);
    b = ((b & 0x0F0F0F0Fu) << 4u) | ((b & 0xF0F0F0F0u) >> 4u);
    b = ((b & 0x00FF00FFu) << 8u) | ((b & 0xFF00FF00u) >> 8u);
    
    float radicalInverseVDC = float(b) * 2.3283064365386963e-10;
    
    return vec2((i / numSamples), radicalInverseVDC);
} 

vec3 ImportanceSample(
    in vec2  xi,
    in float roughness,
    in vec3  surfNorm)
{
	float a = (roughness * roughness);
    
    float phi = 2.0 * PI * xi.x;
    float cosTheta = sqrt((1.0 - xi.y) / (1.0 + (a * a - 1.0) * xi.y));
    float sinTheta = sqrt(1.0 - (cosTheta * cosTheta));
    
    vec3 H = vec3((sinTheta * cos(phi)), (sinTheta * sin(phi)), cosTheta);
    
    vec3 upVector = (0.999 > surfNorm.z) ? vec3(1.0, 0.0, 0.0) : vec3(0.0, 0.0, 1.0);
    vec3 tangentX = normalize(cross(upVector, surfNorm));
    vec3 tangentY = cross(surfNorm, tangentX);
    
    return ((tangentX * H.x) + (tangentY * H.y) + (surfNorm * H.z));
}

vec3 CalculateSpecularIBL(
    in    vec3  surfNorm,
    in    vec3  surfPos,
    in    vec3  toView,
    in    vec3  fresnel0,
    inout vec3  sfresnel,
    inout float ao,
    in    float roughness)
{
    // In the original version, this simply samples from the environment map (iChannel3).
    // Single-bounce reflection and ambient occlusion were added for this shader.
    
    vec3 color = vec3(0.0);
    vec3 totalSpec = vec3(0.0);
    
    ao = 0.0;
    float aoScale = 0.8;
    
    for(float i = 0.0; i < IBLSteps; ++i)
    {
    	vec2 xi = Hammersley(i, IBLSteps);
        vec3 H  = ImportanceSample(xi, roughness, surfNorm);
        vec3 L  = normalize((2.0 * dot(toView, H) * H) - toView);
        
        float NoV = max(0.0, dot(surfNorm, toView));
        float NoL = max(0.0, dot(surfNorm, L));
        float NoH = max(0.0, dot(surfNorm, H));
        float VoH = max(0.0, dot(toView, H));
        
        if(NoL > 0.0)
        {
            // Perform single bounce and accumulate for AO
            
            Ray ray;
            ray.d = L;
            ray.o = surfPos + (ray.d * 0.05);
            
#ifdef HIGH_QUALITY
            vec2 march = March(ray, 100);
#else
            vec2 march = March(ray, 50);
#endif
            
            color = SampleEnvironment(L);
            
            if(march.x < FarClip)
            {
                vec3 pos = ray.o + (ray.d * march.x);
                vec3 norm = SceneNormal(pos, march.x);
                
                Material mat = CreateMaterial(pos, norm, int(march.y));
                float dirIntens = max(0.0, dot(norm, SunLightDir));
                
                if(dirIntens > 0.0) { dirIntens *= Shadow(pos); }
                
                // Calculate a very simple direct lighting for the bounce.
                color = mat.albedo * max(0.2, dirIntens);
                
                ao      += (1.0 - 10.0 * clamp(march.x * 0.25, 0.0, 1.0)) * aoScale;
                aoScale *= 0.4;
            }
            
            // Calculate lighting
            
            float geoAtten = CalculateAttenuationIBL(roughness, NoL, NoV);
            vec3  fresnel = CalculateFresnel(surfNorm, toView, fresnel0);
            
            sfresnel  += fresnel;
            totalSpec += (color * fresnel * geoAtten * VoH) / (NoH * NoV);
        }
    }
    
    ao         = clamp(1.0 - (ao / IBLSteps), 0.0, 1.0);
    sfresnel  /= IBLSteps;
    totalSpec /= IBLSteps;
    
    return totalSpec;
}

vec3 CalculateLightingAnalytical(    // Direct lighting
    in vec3 toLight,
    in vec3 toView,
    in Material mat)
{
    vec3 fresnel0 = mix(vec3(0.04), mat.albedo, mat.metallic);
    vec3 ks       = vec3(0.0);
    vec3 diffuse  = CalculateDiffuse(mat.albedo);
    vec3 specular = CalculateSpecularAnalytical(mat.bump, toLight, toView, fresnel0, ks, mat.roughness);
    vec3 kd       = (1.0 - ks);
    
    float angle = max(0.0, dot(mat.bump, toLight));
    
    return ((kd * diffuse) + specular) * angle;
}

vec3 CalculateLightingIBL(          // Ambient lighting
    in vec3 surfNorm,
    in vec3 surfPos,
    in vec3 toView,
    in Material mat)
{
    float ao = 0.0;
    
    vec3 fresnel0 = mix(vec3(0.04), mat.albedo, mat.metallic);
    vec3 ks       = vec3(0.0);
    vec3 diffuse  = CalculateDiffuse(mat.albedo);
    vec3 specular = CalculateSpecularIBL(surfNorm, surfPos, toView, fresnel0, ks, ao, mat.roughness);
    vec3 kd       = (1.0 - ks);
    
    return ((kd * diffuse) + specular) * ao;
}

//------------------------------------------------------------------------------------------
// Render
//------------------------------------------------------------------------------------------

vec3 Light(in Ray ray, in Material mat, in vec3 norm, in vec3 pos)
{
    vec3 direct = vec3(0.0);
    float sunIntens = max(0.0, dot(norm, SunLightDir));
    
    if(sunIntens > 0.0)
    {
        direct = CalculateLightingAnalytical(SunLightDir, -ray.d, mat);
    	direct *= Shadow(pos);
    }
    
#ifdef HIGH_QUALITY
    vec3 ambient = CalculateLightingIBL(mat.bump, pos, -ray.d, mat);
#else
    vec3 ambient = CalculateLightingIBL(norm, pos, -ray.d, mat);
#endif
    
    return (direct * 2.0 + ambient);
}

vec4 Render(in Ray ray)
{
    vec3 color = SampleEnvironment(ray.d);
    
    vec2 march = March(ray, 150);
    vec3 pos   = ray.o + (ray.d * march.x);
    int  id    = int(march.y);
    
    if(march.x < FarClip)
    {
        vec3 norm = SceneNormal(pos, march.x);
        Material mat = CreateMaterial(pos, norm, id);
        
        GetBumpNormal(pos, mat, id);
        
        color = clamp(Light(ray, mat, norm, pos), vec3(0.0), vec3(1.0));
    }
    
    float d = clamp((march.x / FarClip), 0.0001, 1.0);
    
    // id is integer part of .w, depth is fractional part.
    return vec4(color, march.y + d);
}

//------------------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------------------

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{    
    vec2 uv  = fragCoord.xy / iResolution.xy;
    vec3 pos = OrbitAround(CamOrigin, 3.0, 0.2);
    
    fragColor = Render(Ray_LookAt(uv, pos, CamLookAt));
}
