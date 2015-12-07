varying vec4		position;
varying vec3		normals;
varying mat4		TBN;
uniform sampler2D	spec;

void main( void )
{
	gl_FragData[0]		= vec4(position.xyz,0);
	gl_FragData[1]		= vec4(normals.xyz,0);
	gl_FragData[2]		= vec4(texture2D(spec,gl_TexCoord[0].st).rgb, 0);
}
