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
