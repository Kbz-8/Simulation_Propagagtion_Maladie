/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// GUT.hpp
//
// AUTHOR: DAVID Malo
// CREATED: 11/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef __GUT_HPP__
#define __GUT_HPP__

#ifdef __cplusplus  // only available for C++

#include "math/Vec3/Vec3.hpp"
#include "math/Vec2/vec2.hpp"
#include "math/Vec4/vec4.hpp"
#include "math/math.hpp"
#include "Log/log.hpp"
#include "GL/getPixelColor/getpixelcolor.hpp"
#include "GL/shader/shader.hpp"
#include "GL/text/text.hpp"
#include "GL/button/button.hpp"
#include "SDL2/input/input.hpp"
#include "SDL2/messagebox/messagebox.hpp"

#include <iostream>


/* shortcuts for variable types */
#define GUTuint unsigned int
#define GUTulong unsigned long
#define GUTulonglong unsigned long long
#define GUTushort unsigned short
#define GUTuchar unsigned char
#define GUTtext const char*

namespace gut
{
    void debugPrint(GUTtext text = "debug");
}

#endif // __cplusplus
#endif // __GUT_HPP__
