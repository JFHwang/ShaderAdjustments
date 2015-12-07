uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gSpec; 
uniform vec3 cameraPosition;

void main( void )
{
	vec4 image = texture2D( gSpec, gl_TexCoord[0].xy );
	vec4 position = texture2D( gPosition, gl_TexCoord[0].xy );
	vec4 normal = texture2D( gNormal, gl_TexCoord[0].xy );
	
	vec3 light = vec3(50,100,50);
	vec3 lightDir = light - position.xyz ;
	
	normal = normalize(normal);
	lightDir = normalize(lightDir);
	
	vec3 eyeDir = normalize(cameraPosition-position.xyz);
	vec3 vHalfVector = normalize(lightDir.xyz+eyeDir);
	
	gl_FragColor = max(dot(normal.xyz,lightDir),0) * image + pow(max(dot(normal.xyz,vHalfVector),0.0), 100) * 1.5;
	
	//Make everything red
	//gl_FragColor = image;
}
