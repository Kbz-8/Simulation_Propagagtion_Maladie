/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// main.vert
//
// Simple shader in GLSL for basic programs.
//
// AUTHOR: Malo DAVID
// CREATED: 14/11/2020
// UPDATED: 18/11/2020
/*=============================================================*/

#version 330 core

out vec2 texCoords;
out vec4 Color;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 texCoordIn;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

void main(void)
{
  vec4 fragPos = vec4(model * vec4(aPos, 1.0));
  Color = aColor;
  texCoords = texCoordIn;

  gl_Position = proj * view * fragPos;
}
