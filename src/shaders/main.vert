#version 120

varying vec2 texCoords;
varying vec4 Color;


void main(void)
{
	texCoords = gl_MultiTexCoord0.xy;
	Color = gl_Color;

	gl_Position = ftransform();
}
