/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// vec4.hpp
//
// Class for 4D vectors
//
// AUTHOR: Malo DAVID
// CREATED: 09/10/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef VEC4_HPP
#define VEC4_HPP

#ifdef __cplusplus

#include <iostream>
#include <cmath>

#define Vec4Null Vec4(NULL, NULL, NULL, NULL)

namespace gut
{
namespace math
{
    struct Vec4
    {
        double X;
        double Y;
        double Z;
        double W;

        Vec4();
        Vec4(double x,double y,double z, double w);
        Vec4(const Vec4 & v);
        Vec4(const Vec4 & from, const Vec4 & to);

        Vec4 & operator= (const Vec4 & v);

        bool operator== (const Vec4 & v);
        bool operator!= (const Vec4 & v);

        bool operator== (const double valeur);
        bool operator!= (const double valeur);

        Vec4 & operator+= (const Vec4 & v);
        Vec4 operator+ (const Vec4 & v) const;
        Vec4 operator+ (const double valeur);

        Vec4 & operator-= (const Vec4 & v);
        Vec4 operator- (const Vec4 & v) const;
        Vec4 operator- (const double valeur);

        Vec4 & operator*= (const double a);
        Vec4 operator* (const double a)const;
        friend Vec4 operator* (const double a,const Vec4 & v);
        Vec4 & operator* (const Vec4 &v);

        Vec4 & operator/= (const double a);
        Vec4 operator/ (const double a)const;

        bool operator< (const Vec4 &v);
        bool operator< (const double valeur);

        bool operator> (const Vec4 &v);
        bool operator> (const double valeur);

        bool operator<= (const Vec4 &v);
        bool operator<= (const double valeur);

        bool operator>= (const Vec4 &v);
        bool operator>= (const double valeur);

        Vec4 crossProduct(const Vec4 & v)const;
        double length()const;
        Vec4 & normalize();

        Vec4 COPY(const Vec4 &v);
        Vec4 DirectCopy();

        Vec4 SET(double x, double y, double z, double w);

        friend std::ostream & operator<<(std::ostream& target, const Vec4& source);

        Vec4 NEGATE();
        Vec4 NEGATEprecisely(bool x, bool y, bool z, bool w);

        double dot(Vec4 v);
    };
}
}

#endif // __cplusplus

#endif // VEC4_HPP
