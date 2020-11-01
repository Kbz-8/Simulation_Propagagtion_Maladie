 #version 130

out vec4 fragColor;

uniform sampler2D tex;
uniform bool isTexture;

in vec4 fragPos;
in vec2 texCoords;
in vec4 Color;

void main(void)
{
	if(isTexture)
  		fragColor = texture(tex, texCoords) * Color;
  	else
  		fragColor = Color;
}
