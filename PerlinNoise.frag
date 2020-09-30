
varying float LightIntensity;
varying vec3 ModelPos;
//uniform vec2 loc;



// written by Joe Geisz
// Adapted from:
// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com


vec3 random (vec3 st)
{
    float BigNumber = 103039.0;
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

    // Mix 8 corners percentages
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



void  main()
{

    float Oct1 = 1.0;
    float Oct2 = .5;
    float Oct3 = .25;
    float Oct4 = .125;
    float Scale = 5.0;

    // get perlin noise at 4 differing "octaves" or scales
    vec3 noisevec1 = perlin_noise(ModelPos*Scale);
    vec3 noisevec2 = perlin_noise(ModelPos*2.21*Scale);
    vec3 noisevec3 = perlin_noise(ModelPos*2.21*2.0*Scale);
    vec3 noisevec4 = perlin_noise(ModelPos*2.21*4.0*Scale);

    // combine octaves
    vec3 noisesum = Oct1*noisevec1+Oct2*noisevec2+Oct3*noisevec3+Oct4*noisevec4;

    //set color
    gl_FragColor = vec4(noisesum*LightIntensity,1.0);

}
