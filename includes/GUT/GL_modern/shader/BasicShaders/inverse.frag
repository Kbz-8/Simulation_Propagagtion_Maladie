/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// inverse.frag
//
// Simple shader in GLSL for basic programs.
//
// AUTHOR: Malo DAVID
// CREATED: 14/11/2020
// UPDATED: 18/11/2020
/*=============================================================*/

#version 330 core

out vec4 fragColor;
in vec4 Color;

void main(void)
{
  vec4 color = Color;
  color.rgb = 1. - color.rgb;
  fragColor = color;
}
