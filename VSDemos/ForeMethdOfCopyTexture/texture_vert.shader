#version 330 core

layout(location = 0) in vec2 input_VertexPosition;
layout(location = 1) in vec2 input_VertexTexcoord;

out vec2 VertexTexcoord;

void main() {
	gl_Position = vec4(input_VertexPosition, 0.1, 1);
	VertexTexcoord = input_VertexTexcoord;
}