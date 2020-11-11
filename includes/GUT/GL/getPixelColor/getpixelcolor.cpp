/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// getpixelcolor.cpp
// Can only be used with OpenGL
//
// AUTHOR: DAVID Malo
// CREATED: 11/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifdef __cplusplus  // only available for C++

#include "getpixelcolor.hpp"

namespace gut
{
namespace gl
{
    Color getPixelColor(GLint x, GLint y)
    {
        Color color;
        glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
        return color;
    }
}
}

#endif // __cplusplus
