#version 130

in vec3 Colour;
in vec2 Texcoord;

//TODO1: these are our input variables which will be different for each fragment.
// Fragment position and surface normal in view space
in vec4 fragNormalView;
in vec4 fragPositionView;

out vec4 outColor;

uniform sampler2D tex;
uniform vec4 light_position;
uniform vec4 light_colour;

void main()
{
	//Compute direction of light from frag position in view space
	vec3 lightDisplacement = light_position.xyz - fragPositionView.xyz;

	//Normalised light vector
	vec3 normalisedLightDisp = normalize(lightDisplacement);

	//TODO2: Calculate the diffuse component using the Lambertian light equation
	//HINT: dot product
	vec4 normalizedFragNormalView = normalize(fragNormalView);

	vec4 diffuse = dot(normalisedLightDisp, normalizedFragNormalView.xyz) * (light_colour);

	//TODO3: calculate the distance to light from the surface
	float d = length(lightDisplacement);

	//TODO4: Compute light reflection using (negate normalisedLightDisp because the light comes from the light to the surface)
	//(just uncomment and read)
	vec3 reflection = reflect(-normalisedLightDisp, fragNormalView.xyz);

	//Shininess material parameter.
	float shininess = 100;


	//TODO5: compute the specular intensity
	vec3 normalizedFragPositionView = -normalize(fragPositionView.xyz);


	float specular_intensity = dot(reflection, normalizedFragPositionView.xyz);


	//TODO6:compute specular colour component (just uncomment and read)
	vec4 specular = pow(clamp(specular_intensity,0,1), shininess) * light_colour;

	//TODO7: Set a constant ambient colour so things are never completely dark
	vec4 ambient = vec4(0.3,0.3,0.3,1.0);

    //Final total colour including diffuse, specular, ambient, falloff (with 1/d^2), texture and colour
    //outColor =  ((diffuse + specular) * (1/(d*d)) + ambient) * texture(tex, Texcoord) * vec4(Colour, 1.0);

    //TODO8: Try these outColours to see just the single components of the light!
    //outColor = diffuse * texture(tex, Texcoord);
    //outColor = ambient * texture(tex, Texcoord);
    //outColor = specular;
     
	 //outColor = specular + diffuse;
	 outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // outColor = (diffuse + specular) * (1/(d*d));
}
