
varying float LightIntensity;
varying vec3 ModelPos;


// written by Joe Geisz
// Adapted from:
// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com

vec3 random (vec3 st)
{
    float BigNumber = 103039.0;
    //taking the Sine of our point times a very large number gives us approximately a random BigNumber
    // between -1 and 1, we take just the decimal i.e. the absolute value.
    return vec3(
                fract(sin(dot(st.xyz,vec3(12.9898,78.233,34.235)))* BigNumber),
                fract(sin(dot(st.xyz,vec3(1.0320,44.235,92.012)))* BigNumber),
                fract(sin(dot(st.xyz,vec3(91.329,22.329,80.293)))* BigNumber));
}


void  main()
{
    //Pick a random color for each point
    gl_FragColor = vec4( random(ModelPos)*LightIntensity, 1.0);

}
