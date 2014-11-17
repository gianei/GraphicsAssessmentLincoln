#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

//smooth out vec4 interpColor;

//uniform vec3 dirToLight;
//uniform vec4 lightIntensity;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

smooth out vec4 theColor;


out vec4 diffuseColor;
out vec3 vertexNormal;
out vec3 modelSpacePosition;


void main()
{
	//theColor = color;
	gl_Position = projection * view * model * vec4(position, 1.0f);
	// 

	vec3 dirToLight = normalize(vec3(0.0f,0.0f,1.0f));
	vec4 lightIntensity = vec4(1.0f,1.0f,1.0f,1.0f);

	//vec3 normCamSpace = normalize(mat3(projection) * mat3(view) * normal);
	vec3 normCamSpace = normal;
    
    float cosAngIncidence = dot(normCamSpace, dirToLight);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);
    
    theColor = lightIntensity * color * cosAngIncidence;
	//theColor = color;

	modelSpacePosition = position;
    vertexNormal = normal;
    diffuseColor = color;
}
