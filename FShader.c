#version 330

// Tex coords of the quad from vertex shader between 0 and 1
in vec2 vTexCoord;// Output colour
out vec4 oColor;// Contains world space normals
uniform sampler2D uTexNormals;// Contains world space positions
uniform sampler2D uTexWorld;// Contains the image that will be reflected from in my case, the lit geometry
uniform sampler2D uTexSource;// Contains an image filled with random values
uniform sampler2D uTexNoise; // Random value texture

// Camera position in world space
uniform vec3 uCameraPosition;
// projection view matrix of the camera
uniform mat4 uProjViewMatrix;

const int NUM_SAMPLES = 8;
const float SAMPLE_SPACING = 3.0f;
const float SAMPLE_TOLLERANCE = SAMPLE_SPACING*5.0f;
const float SAMPLE_RANDOMISE = 0.02f;

void main()
{
	// World space normal
	vec3 normal = texture2D(uTexNormals, vTexCoord).xyz*2-1;

	// World space position
	vec3 world = texture2D(uTexWorld, vTexCoord).xyz;

	// Normalised vector from camera position to world position
	vec3 eye = normalize(uCameraPosition – world);

	// Generate reflected ray
	vec3 ray = reflect(-eye, normal);

	// Random sample (this texture was using in my SSAO, but I
	// have bound it here to add some variance to help battle artefacts)
	vec3 rand = texture2D(uTexNoise, vTexCoord*vec2(1.6,1)*4).xyz*2-1;
	float n = rand.x*0.5+1;

	vec3 col = vec3(0);
	for (int i=0; i<NUM_SAMPLES; i++)
	{
		// Pick a point on the ray
		vec3 raysamp = world + rand*SAMPLE_RANDOMISE + ray*(i+n)*SAMPLE_SPACING;

		// Put ray into screenspace
		vec4 vssamp = uProjViewMatrix * vec4(raysamp, 1);
		vssamp /= vssamp.w; // Now its between -1 and 1
		vssamp = vssamp*0.5+0.5; // Now its between 0 and 1

		// World space sample position
		vec3 p = texture2D(uTexWorld, vssamp.xy).xyz;

		// Colour of world space sample position
		vec3 c = texture2D(uTexSource, vssamp.xy).xyz;

		// Calculate the blend amount for the sample 
		float b = max(0, 0.5-length(raysamp-p)/SAMPLE_TOLLERANCE);

		// Add the colour to the output
		col += c * b;
	}

// Send across the colour to the blend shader which blends it with the source colour based on the w component
// The w component consists of Fresnel and perhaps shininess or metalness etc…
gl_FragColor = vec4(col, 0.3);
}