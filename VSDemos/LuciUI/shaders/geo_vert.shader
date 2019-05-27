#version 330 core

uniform vec4 rect;
uniform float screenWidth;
uniform float screenHeight;
uniform mat4 mvp;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 input_VertexPosition;
layout(location = 1) in vec2 input_VertexTexcoord;

// Output data ; will be interpolated for each fragment.
out vec2 VertexTexcoord;

void main() {

	// Output position of the vertex, in clip space : MVP * position
	
	gl_Position = mvp * vec4(input_VertexPosition.xyz,1);

	// UV of the vertex. No special space for this one.
	VertexTexcoord = input_VertexTexcoord;
}

