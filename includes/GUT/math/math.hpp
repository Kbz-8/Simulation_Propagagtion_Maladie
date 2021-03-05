/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// math.hpp
//
// AUTHOR: Malo DAVID
// CREATED: 31/10/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef MATH_HPP
#define MATH_HPP

#ifdef __cplusplus

#include "Vec2/vec2.hpp"
#include "Vec3/Vec3.hpp"
#include "Vec4/vec4.hpp"

#include <iostream>
#include <cmath>

namespace gut
{
    namespace math
    {
        int randint(int a, int b);  // gives a random integer
        bool rand_probability(double proba);
    }
}

#endif // __cplusplus

#endif // MATH_HPP
