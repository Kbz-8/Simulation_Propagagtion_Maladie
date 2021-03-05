/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// GUT.hpp
//
// AUTHOR: Malo DAVID
// CREATED: 11/09/2020
// UPDATED: 03/12/2020
/*=============================================================*/

#ifndef __GUT_HPP__
#define __GUT_HPP__

#ifdef __cplusplus  // only available for C++

#include "math/math.hpp"

#include "Log/log.hpp"

#include "GL_old/utils.hpp"
#include "GL_modern/utils.hpp"

#include "SDL2/input/input.hpp"
#include "SDL2/messagebox/messagebox.hpp"
#include "SDL2/button/button.hpp"

#include <iostream>
#include <string>


/* shortcuts for variable types */
#define GUTuint unsigned int
#define GUTulong unsigned long
#define GUTulonglong unsigned long long
#define GUTushort unsigned short
#define GUTubyte unsigned char
#define GUTuchar unsigned char
#define GUTtext const char*

namespace gut
{
    void debugPrint(GUTtext text = "debug");

/*============ Couleurs des std::cout ============*/
    enum Code
    {
        red = 31,
        green = 32,
        blue = 34,
        def = 39,
        black = 30,
        yellow = 33,
        magenta = 35,
        cyan = 36,
        white = 37,
        bg_red = 41,
        bg_green = 42,
        bg_blue = 44,
        bg_def = 49,
        bg_black = 40,
        bg_yellow = 43,
        bg_magenta = 45,
        bg_cyan = 46,
        bg_white = 47,
        reset = 0,
        bold = 1,
        underline = 4,
        inverse = 7,
        bold_off = 21,
        underline_off = 24,
        inverse_off = 27
    };

    std::ostream &operator<<(std::ostream &os, const Code code);
}

#endif // __cplusplus
#endif // __GUT_HPP__
