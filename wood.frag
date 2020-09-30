
varying float LightIntensity;
varying vec3 ModelPos;

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;


// random and noise Adapted from:
// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com

vec3 random (vec3 st)
{
    float BigNumber = 493820.0;
    return vec3(
                fract(sin(dot(st.xyz,vec3(12.9898,78.233,34.235)))* BigNumber),
                fract(sin(dot(st.xyz,vec3(1.0320,44.235,92.012)))* BigNumber),
                fract(sin(dot(st.xyz,vec3(91.329,22.329,80.293)))* BigNumber));

}


vec3 perlin_noise(vec3 st)
{

    vec3 i = floor(st);
    vec3 f = fract(st);

    // values at eight corners of a 3D Cube
    vec3 c000 = random(i);
    vec3 c100 = random(i + vec3(1.0, 0.0, 0.0));
    vec3 c010 = random(i + vec3(0.0, 1.0, 0.0));
    vec3 c110 = random(i + vec3(1.0, 1.0, 0.0));
    vec3 c001 = random(i + vec3(0.0, 0.0, 1.0));;
    vec3 c101 = random(i + vec3(1.0, 0.0, 1.0));
    vec3 c011 = random(i + vec3(0.0, 1.0, 1.0));
    vec3 c111 = random(i + vec3(1.0, 1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec3 u = f*f*(3.0-2.0*f);
    //vec3 u = st;
    // u = smoothstep(0.,1.,f);

    // Mix 8 coorners percentages
    // from https://en.wikipedia.org/wiki/Trilinear_interpolation
    vec3 c00 = c000*(1.0-u.x) + c100*u.x;
    vec3 c01 = c001*(1.0-u.x) + c101*u.x;
    vec3 c10 = c010*(1.0-u.x) + c110*u.x;
    vec3 c11 = c011*(1.0-u.x) + c111*u.x;

    vec3 c0 = c00*(1.0 - u.y) + c10*u.y;
    vec3 c1 = c01*(1.0 - u.y) + c11*u.y;

    vec3 c = c0*(1.0 - u.z) + c1*u.z;

    return c;
}



//Wood Texture algorithm adapted from Red GL book

void  main()
{
    float Oct1 = 0.9;
    float Oct2 = 0.2;
    float Oct3 = 0.2;
    float Oct4 = 0.05;
    float Scale = .5;

    vec3 LightWood = vec3(0.6,0.3,0.1);
    vec3 DarkWood = vec3(0.4,0.2,0.07);
    float RingFreq=4.0;
    float LightGrains=1.0;
    float DarkGrains=0.0;
    float GrainThreshold=0.1;
    float NoiseScalex=0.5;
    float NoiseScaley=0.1;
    float NoiseScalez=0.1;
    float Noisiness=1.0;
    float GrainScale=27.0;

    vec3 Pos = ModelPos;

    vec3 noisevec1 = perlin_noise(Pos*Scale);
    vec3 noisevec2 = perlin_noise(Pos*2.21*Scale);
    vec3 noisevec3 = perlin_noise(Pos*2.21*2.0*Scale);
    vec3 noisevec4 = perlin_noise(Pos*2.21*4.0*Scale);

    // combine octaves
    vec3 noisesum = Oct1*noisevec1+Oct2*noisevec2+Oct3*noisevec3+Oct4*noisevec4;
    vec3 noisevec = noisesum*Noisiness;

    vec3 location = Pos + noisevec;
    float dist = sqrt(location.x * location.x +location.z *location.z);
    dist *= RingFreq;
    float r = fract(dist + noisevec[0]+noisevec[1]+noisevec[2])*2.0;
    if (r> 1.0)
        r = 2.0 - r;
    vec3 color = mix(LightWood, DarkWood, r);
    r = fract((Pos.x +Pos.z)*GrainScale + 0.5);
    noisevec[2] *= r;
    if (r < GrainThreshold)
        color += LightWood * LightGrains * noisevec[2];
    else
        color -= LightWood * DarkGrains * noisevec[2];
    color *= LightIntensity;
    gl_FragColor = vec4(color, 1.0);


}
