#version 140

in vec2 textureCoords;

out vec4 out_Colour;

uniform sampler2D colourTexture;

void main(void){

	out_Colour = texture(colourTexture, textureCoords);
	out_Colour = out_Colour + vec4(0.3, 0, 0, 0);
}