/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// main.frag
//
// Simple shader in GLSL for basic programs.
//
// AUTHOR: Malo DAVID
// CREATED: 14/11/2020
// UPDATED: 18/11/2020
/*=============================================================*/

#version 330 core

out vec4 fragColor;

uniform sampler2D tex;
uniform bool isTexture;

in vec3 fragPos;
in vec2 texCoords;
in vec4 Color;

void main(void)
{
	if(isTexture)
        fragColor = texture(tex, texCoords);
	else
		fragColor = Color;
}
