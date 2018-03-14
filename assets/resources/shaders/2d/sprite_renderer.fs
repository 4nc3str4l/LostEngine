#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform float transparency;

void main()
{    
    color = vec4(spriteColor, 1.0f) * texture(image, TexCoords);
    color.w = transparency;
    color.x = 1.0f;
} 