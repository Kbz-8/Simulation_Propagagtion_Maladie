/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// vec2.hpp
//
// Class for 2D vectors
//
// AUTHOR: Malo DAVID
// CREATED: 11/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef Vec2_HPP_INCLUDED
#define Vec2_HPP_INCLUDED

#ifdef __cplusplus

#include <iostream>
#include <cmath>

#define Vec2Null gut::math::Vec2(NULL, NULL)

namespace gut
{
namespace math
{
    struct Vec2
    {
        double X;
        double Y;

        Vec2();
        Vec2(double x, double y);
        Vec2(const Vec2 & v);
        Vec2(const Vec2 & from, const Vec2 & to);

        Vec2 & operator= (const Vec2 & v);

        bool operator== (const Vec2 & v);
        bool operator!= (const Vec2 & v);

        bool operator== (const double valeur);
        bool operator!= (const double valeur);

        Vec2 & operator+= (const Vec2 & v);
        Vec2 operator+ (const Vec2 & v) const;
        Vec2 operator+ (const double valeur);

        Vec2 & operator-= (const Vec2 & v);
        Vec2 operator- (const Vec2 & v) const;
        Vec2 operator- (const double valeur);

        Vec2 & operator*= (const double a);
        Vec2 operator* (const double a)const;
        friend Vec2 operator* (const double a, const Vec2 & v);
        Vec2 & operator* (const Vec2 &v);

        Vec2 & operator/= (const double a);
        Vec2 operator/ (const double a)const;

        bool operator< (const Vec2 &v);
        bool operator< (const double valeur);

        bool operator> (const Vec2 &v);
        bool operator> (const double valeur);

        bool operator<= (const Vec2 &v);
        bool operator<= (const double valeur);

        bool operator>= (const Vec2 &v);
        bool operator>= (const double valeur);

        Vec2 crossProduct(const Vec2 & v)const;
        double length()const;
        Vec2 & normalize();

        Vec2 COPY(const Vec2 &v);
        Vec2 DirectCopy();

        Vec2 SET(double x, double y);

        friend std::ostream & operator<<(std::ostream& target, const Vec2& source);

        Vec2 NEGATE();
        Vec2 NEGATEprecisely(bool x, bool y);

        double dot(Vec2 v);
    };
}
}

#endif // __cplusplus
#endif
