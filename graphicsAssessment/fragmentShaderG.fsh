#version 330

smooth in vec4 theColor;



in vec4 diffuseColor;
in vec3 vertexNormal;
in vec3 modelSpacePosition;

out vec4 outputColor;

//uniform vec3 modelSpaceLightPos;

vec4 lightIntensity;
vec4 ambientIntensity;
vec4 lightAttenuation;

uniform vec3 modelSpaceLightPos;
vec3 lightDir;

bool bUseRSquare = true;

vec4 ApplyLightIntensity(in vec3 cameraSpacePosition, out vec3 lightDirection)
{
    vec3 lightDifference =  modelSpaceLightPos - cameraSpacePosition;
    float lightDistanceSqr = dot(lightDifference, lightDifference);
    lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
    
    float distFactor = bUseRSquare ? lightDistanceSqr : sqrt(lightDistanceSqr);
    
    return lightIntensity * (1 / ( 1.0 + lightAttenuation * distFactor));
}

void main()
{
	lightIntensity = vec4(0.9f,0.9f,0.9f,1.0f);
	ambientIntensity = vec4(0.0f,0.0f,0.0f,1.0f);
	lightAttenuation = vec4(0.9f,0.9f,0.9f,1.0f);

	//modelSpaceLightPos = vec3(5.0f, 5.0f, 20.0f);

	lightDir = normalize(modelSpaceLightPos - modelSpacePosition);
	//lightDir = normalize(vec3(0.0f,0.0f,1.0f));
    
    float cosAngIncidence = dot(normalize(vertexNormal), lightDir);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);


	vec4 attenIntensity = ApplyLightIntensity(modelSpacePosition, lightDir);

	//outputColor = (diffuseColor * attenIntensity * cosAngIncidence) +
    //    (diffuseColor * ambientIntensity);
	outputColor = diffuseColor * lightIntensity * cosAngIncidence +  (diffuseColor * ambientIntensity);

}

