mat3 rotY(float d){
    float s = sin(d);
    float c = cos(d);
    return mat3(  c, 0.0,  -s,
                0.0, 1.0, 0.0,
                  s, 0.0,   c );
}

float closeObj = 0.0;

vec2 vecMin(vec2 a, vec2 b){
    if(a.x <= b.x){
        return a;
    }
    return b;
}

vec2 mapMat(vec3 p){
    vec2 cubeMap = vec2(-length(p) + 4.0, 1.0);
    vec2 mirrorSphere = vec2(length(p - vec3(cos(iTime / 2.0), 0.0, sin(iTime / 2.0))) - 0.25, 2.0);
    return vecMin(cubeMap, mirrorSphere);
}

float map(vec3 p){
    return mapMat(p).x;
}

float trace(vec3 ro, vec3 rd){
    float t = 0.0;
    float d = 0.0;
    vec2 c;
    int inter = 0;
    for(int i = 0; i < 1000; i++){
        c = mapMat(ro + rd * t);
        d = c.x;
        if(d < 0.0001){
            inter = 1;
            break;
        }
        t += d;
        if(t > 5.0){
            break;
        }
    }
    closeObj = c.y;
    if(inter == 0){
        t = -1.0;
    }
    return t;
}

vec3 normal(vec3 p){
    return normalize(vec3(map(vec3(p.x + 0.0001, p.yz)) - map(vec3(p.x - 0.0001, p.yz)),
                          map(vec3(p.x, p.y + 0.0001, p.z)) - map(vec3(p.x, p.y - 0.0001, p.z)),
                	      map(vec3(p.xy, p.z + 0.0001)) - map(vec3(p.xy, p.z - 0.0001))));
}

vec3 camPos = vec3(0.0, 0.0, 0.0);
vec3 lightPos = vec3(0.0, 0.0, 0.0);

vec3 amb(vec3 c, float k){
    return c * k;
}

vec3 diff(vec3 c, float k, vec3 p){
    vec3 n = normal(p);
    vec3 l = normalize(lightPos - p);
    return c * k * max(0.0, dot(n, l));
}

vec3 spec(vec3 c, float k, vec3 p, float a){
    vec3 n = normal(p);
    vec3 l = normalize(lightPos - p);
    vec3 v = normalize(p - camPos);
    float facing = dot(l, n) > 0.0 ? 1.0 : 0.0;
    vec3 r = reflect(l, n);
    return c * k * facing * pow(max(0.0, dot(r, v)), a);
}

vec3 colour(vec3 p, float id){    
    if(id == 1.0){
        vec3 col = texture(iChannel0, normal(p)).xyz;
        return col;
    }else if(id == 2.0){
        vec3 col = texture(iChannel0, reflect(normalize(lightPos - p), normal(p))).xyz 
            	* vec3(0.776477, 0.376471, 0.184314);
        return amb(col, 0.5) + diff(col, 0.6, p) + spec(vec3(0.776477, 0.376471, 0.184314), 0.95, p, 64.0);
    }
    return vec3(0.0, 1.0, 0.0);
} 

void mainImage( out vec4 fragColor, in vec2 fragCoord ){
	vec2 uv = fragCoord.xy / iResolution.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;
    camPos = vec3(0.0 , 0.0, 0.0);
    lightPos = vec3(0.0, 0.0, 0.0);
    vec3 ro = camPos;
    vec3 rd = normalize(rotY(-iTime / 2.0 + radians(90.0)) * vec3(uv, 1.0));
    float d = trace(ro, rd);
    vec3 c = ro + rd * d;
    vec3 col = vec3(1.0);
    //If intersected
    if(d > 0.0){
    	col = colour(c, closeObj);
    }else{
        col = vec3(0.0);
    }
	fragColor = vec4(col,1.0);
}