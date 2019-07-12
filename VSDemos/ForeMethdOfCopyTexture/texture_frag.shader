#version 330 core

uniform sampler2D baseTexture;

in vec2 VertexTexcoord;

out vec4 output_Color;

void main() {
	output_Color = texture(baseTexture, VertexTexcoord);
}
