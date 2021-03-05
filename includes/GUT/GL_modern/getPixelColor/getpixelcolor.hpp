/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// getpixelcolor.hpp
// Can only be used with OpenGL
//
// AUTHOR: Malo DAVID
// CREATED: 11/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef __GETPIXELCOLOR_HPP__
#define __GETPIXELCOLOR_HPP__

#ifdef __cplusplus  // only available for C++

// Includes OpenGL
#include <GL/glew.h>

struct Color
{
    float R;
    float G;
    float B;
};

namespace gut
{
namespace gl3
{
    Color getPixelColor(GLint x, GLint y);
}
}

#endif // __cplusplus
#endif // __GETPIXELCOLOR_HPP__
