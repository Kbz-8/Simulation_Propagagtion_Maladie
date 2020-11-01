/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// getpixelcolor.hpp
// Can only be used with OpenGL
//
// AUTHOR: DAVID Malo
// CREATED: 11/09/2020
// UPDATED: 12/09/2020
/*=============================================================*/

#ifndef __GETPIXELCOLOR_HPP__
#define __GETPIXELCOLOR_HPP__

#ifdef __cplusplus  // only available for C++

// Includes OpenGL
#include <GL/glew.h>

struct Color
{
    GLubyte R;
    GLubyte G;
    GLubyte B;
};

Color getPixelColor(GLint x, GLint y);

#endif // __cplusplus
#endif // __GETPIXELCOLOR_HPP__
