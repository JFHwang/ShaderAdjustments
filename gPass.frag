varying vec4		position;
varying vec3		normals;
varying mat4		TBN;
uniform sampler2D	textureSampler;	//The texture sampler that represents the colors

void main( void )
{
	vec2 st = gl_TexCoord[0];
	vec4 textureColor = texture2D(textureSampler, st);
	
	gl_FragData[0]		= vec4(position.xyz,0);
	gl_FragData[1]		= vec4(normals.xyz,0);
	gl_FragData[2]		= textureColor;
}


varying vec3 N;
varying vec3 v;
varying vec2 vTexCoord;

uniform sampler2D myTexture;


#define MAX_LIGHTS 3 

void main(void) {
    //  vec3 N = normalize(N);
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec3 E = normalize(-position); // we are in Eye Coordinates, so EyePos is (0,0,0) 

    vec4 color = texture2D(myTexture, vTexCoord);
    if(color.rgb == vec3(0,0,0))
        color = vec4(1,1,1,1);
    
    
    if (gl_FrontMaterial.emission.rgb != vec3(0, 0, 0).rgb) {   // These are particles.
        gl_FragColor = gl_FrontLightModelProduct.sceneColor + gl_FrontMaterial.emission;
    } else {
        for (int i = 6; i < 8; ++i) {
            vec3 L = normalize(gl_LightSource[i].position.xyz - v);
            vec3 R = normalize(-reflect(L, normals));


            //calculate Ambient Term: 
            vec4 Iamb = gl_FrontLightProduct[i].ambient;
            //calculate Diffuse Term: 
            vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(normals, L), 0.0);
            // calculate Specular Term:
            vec4 Ispec = gl_FrontLightProduct[i].specular * pow(max(dot(R, E), 0.0), 0.3 * gl_FrontMaterial.shininess);


            Idiff = clamp(Idiff, 0.0, 1.0);
            Ispec = clamp(Ispec, 0.0, 1.0);


            finalColor += Iamb + (color * Idiff) + Ispec;
        }

        gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor;

    }

}