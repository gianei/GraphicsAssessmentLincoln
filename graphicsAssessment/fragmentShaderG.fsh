#version 330

smooth in vec4 theColor;



in vec4 diffuseColor;
in vec3 vertexNormal;
in vec3 modelSpacePosition;

out vec4 outputColor;

//uniform vec3 modelSpaceLightPos;

//uniform vec4 lightIntensity;
//uniform vec4 ambientIntensity;


void main()
{
	vec4 lightIntensity = vec4(0.5f,0.5f,0.5f,1.0f);
	vec4 ambientIntensity = vec4(1.0f,1.0f,1.0f,1.0f);

	vec3 modelSpaceLightPos = vec3(5.0f, 5.0f, 20.0f);

	vec3 lightDir = normalize(modelSpaceLightPos - modelSpacePosition);
	//vec3 lightDir = normalize(vec3(0.0f,0.0f,1.0f));
    
    float cosAngIncidence = dot(normalize(vertexNormal), lightDir);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);


	//outputColor = theColor;


	//outputColor = (diffuseColor * lightIntensity * cosAngIncidence) +
    //    (diffuseColor * ambientIntensity);
	outputColor = diffuseColor * lightIntensity * cosAngIncidence;

}