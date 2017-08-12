#version 330 core
struct Material 
{
    vec3 ambient; // jaki kolor jest widziany pod wplywem ambient light
    vec3 diffuse; // ustawia jaki rzeczywiscie ma byc widoczny kolor
    vec3 specular; // kolor tego specular
    float shininess; // promien tego specular
};

struct MaterialTexture 
{
    sampler2D diffuse;
    vec3      specular;
    float     shininess;
}; 

struct Light // w celu wyroznienia pewnych skladowych swiatla
{
    vec3 pos;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

in vec2 TexCoord;
in vec3 FragPos;  
in vec3 Normal;  
  
out vec4 color;

uniform Light light;
uniform vec3 viewPosition;		//camera position
uniform Material material;		// material type
uniform MaterialTexture materialTexture;	// material texture
uniform bool isTexture;

void main()
{
	if(isTexture)
	{
		// Ambient light
		vec3 ambient = light.ambient * vec3(texture(materialTexture.diffuse, TexCoord));
  	
		// Diffuse light
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.pos - FragPos); // vector which describes light direction
		float diff = max(dot(norm, lightDir), 0.0);		// dot product and abs value
		vec3 diffuse = light.diffuse * diff * vec3(texture(materialTexture.diffuse, TexCoord));
    
		// Specular light
		vec3 viewDir = normalize(viewPosition - FragPos);	// vector which describes direction of the camera
		vec3 reflectDir = reflect(-lightDir, norm);			// reflection computing
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialTexture.shininess);	// how big is area where light is to focus on
		vec3 specular = light.specular * spec * materialTexture.specular;  
        
		vec3 result = ambient + diffuse + specular;
		color = vec4(result, 1.0f);
	}
	else
	{
		// Ambient light
		vec3 ambient = light.ambient * material.ambient;
  	
		// Diffuse light
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.pos - FragPos);		// vector which describes light direction
		float diff = max(dot(norm, lightDir), 0.0);			// dot product and abs value
		vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
		// Specular - swiatlo skupiajace
		vec3 viewDir = normalize(viewPosition - FragPos);	// vector which describes direction of the camera
		vec3 reflectDir = reflect(-lightDir, norm);			// reflection computing
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);		// how big is area where light is to focus on
		vec3 specular = light.specular * (spec * material.specular);  
        
		vec3 result = ambient + diffuse + specular;
		color = vec4(result, 1.0f);
	}
}