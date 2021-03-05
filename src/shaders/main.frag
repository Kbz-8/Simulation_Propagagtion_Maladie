#version 120

uniform sampler2D tex;
uniform bool isTexture;

varying vec2 texCoords;
varying vec4 Color;

void main(void)
{
	if(isTexture)
  		gl_FragColor = texture2D(tex, texCoords) * Color;
  	else
  		gl_FragColor = Color;
}
