#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform float transparency;

void main()
{    
    color = vec4(spriteColor, transparency) * texture(image, TexCoords);
} 
