#version 420
uniform vec2 resolution;
uniform vec3 rayOrigin;
uniform float time;
uniform vec2 cameraDirection;
uniform float zoom;
uniform mat3 transform;

const int MAX_STEPS = 400;
const float MAX_DIST = 20.;
const float SURFACE_DIST = 0.001;


float sphere(vec4 s) {
    return length(s.xyz) - s.w;
}

float hash(vec3 p) {
    p = fract(p * 0.3183099 + 0.1);
    p *= 17.0;
    return fract(p.x * p.y * p.z * (p.x + p.y + p.z));
}

float noise(vec3 x) {
    vec3 i = floor(x);
    vec3 f = fract(x);
    f = f * f * (3.0 - 2.0 * f);
    return mix(mix(mix(hash(i + vec3(0, 0, 0)),
                       hash(i + vec3(1, 0, 0)), f.x),
                   mix(hash(i + vec3(0, 1, 0)),
                       hash(i + vec3(1, 1, 0)), f.x), f.y),
               mix(mix(hash(i + vec3(0, 0, 1)),
                       hash(i + vec3(1, 0, 1)), f.x),
                   mix(hash(i + vec3(0, 1, 1)),
                       hash(i + vec3(1, 1, 1)), f.x), f.y), f.z);
}

vec4 getGlow(float minPDist) {
    float mainGlow = minPDist * 1.2;
    mainGlow = pow(mainGlow, 32.0);
    float outerGlow = minPDist * minPDist * 0.16;
    vec4 glow = vec4(10, 5, 3, clamp(mainGlow + outerGlow, 0.0, 1.0));
    return glow;
}

float getDist(vec3 p) {
    vec3 diskPos = -p;
    float diskDist = sphere(vec4(diskPos, 5.0));
    diskDist = max(diskDist, diskPos.y - 0.21);
    diskDist = max(diskDist, -diskPos.y + 0.21);
    diskDist = max(diskDist, -sphere(vec4(-p, 1.5) * 10.0));
    if(diskDist < 2.0)
    {
        vec3 c = vec3(length(diskPos), diskPos.y, atan(diskPos.z + 1.0, diskPos.x + 1.0) * 0.5);
        c *= 10.0;
        diskDist += noise(c) * 0.4;
        diskDist += noise(c * 2.5) * 0.2;
    }
    return diskDist;
}

vec4 raymarch(vec3 ro, vec3 rd) {
    vec3 p = ro;
    float glow = 0.0;
    for (int i = 0; i < MAX_STEPS; i++) {
        float dS = getDist(p);
        glow = max(glow, 1.0 / (dS + 1.0));
        vec3 bdir = normalize(-p);
        float bdist = length(p);
        dS = min(dS, length(p)) * 0.04;
        if (dS > 30.0) break;
        if(bdist < 1.0) {
            vec4 gcol = getGlow(glow);
            vec4 c = vec4(0., 0., 0., 1.);
            c.rgb = mix(c.rgb, gcol.rgb, gcol.a);
            return c;
        }
        bdist = pow(bdist + 1.0, 2.0);
        bdist = dS * 1.0 / bdist;
        rd = mix(rd, bdir, bdist);
        p += rd * max(dS, 0.01);
    }
    vec4 c = vec4(0.0, 0., 0., 1.0);
    vec4 gcol = getGlow(glow);
    c.rgb = mix(c.rgb, gcol.rgb, gcol.a);
    return c;
}

mat2 rotate(float a) {
    float s = sin(a);
    float c = cos(a);
    return mat2(c, -s, s, c);
}

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * resolution) / resolution.y;

    vec3 rayDirection = normalize(vec3(uv.x, uv.y, zoom) * transform);
    rayDirection.yz *= rotate(cameraDirection.y);
    rayDirection.xz *= rotate(cameraDirection.x);
    gl_FragColor = raymarch(rayOrigin, rayDirection);;
}