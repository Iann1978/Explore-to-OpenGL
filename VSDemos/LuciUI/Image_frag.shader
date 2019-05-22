#version 330 core

in vec2 VertexTexcoord;

// Ouput data
out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
	color = texture(myTextureSampler, VertexTexcoord).rgb;
	// Output color = color of the texture at the specified UV
	//color = vec3(1, 0, 0);
}