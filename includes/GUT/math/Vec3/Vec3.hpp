/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// Vec3.hpp
//
// Class for 3D vectors
//
// AUTHOR: DAVID Malo
// CREATED: 11/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef Vec3_HPP_INCLUDED
#define Vec3_HPP_INCLUDED

#ifdef __cplusplus

#include <iostream>
#include <cmath>

#define Vec3Null Vec3(NULL, NULL, NULL)

namespace gut
{
namespace math
{
    class Vec3
    {
        public :
            double X;
            double Y;
            double Z;

            Vec3();
            Vec3(double x,double y,double z);
            Vec3(const Vec3 & v);
            Vec3(const Vec3 & from, const Vec3 & to);

            Vec3 & operator= (const Vec3 & v);

            bool operator== (const Vec3 & v);
            bool operator!= (const Vec3 & v);

            bool operator== (const double valeur);
            bool operator!= (const double valeur);

            Vec3 & operator+= (const Vec3 & v);
            Vec3 operator+ (const Vec3 & v) const;
            Vec3 operator+ (const double valeur);

            Vec3 & operator-= (const Vec3 & v);
            Vec3 operator- (const Vec3 & v) const;
            Vec3 operator- (const double valeur);

            Vec3 & operator*= (const double a);
            Vec3 operator* (const double a)const;
            friend Vec3 operator* (const double a,const Vec3 & v);
            Vec3 & operator* (const Vec3 &v);

            Vec3 & operator/= (const double a);
            Vec3 operator/ (const double a)const;

            bool operator< (const Vec3 &v);
            bool operator< (const double valeur);

            bool operator> (const Vec3 &v);
            bool operator> (const double valeur);

            bool operator<= (const Vec3 &v);
            bool operator<= (const double valeur);

            bool operator>= (const Vec3 &v);
            bool operator>= (const double valeur);

            Vec3 crossProduct(const Vec3 & v)const;
            double length()const;
            Vec3 & normalize();

            Vec3 COPY(const Vec3 &v);
            Vec3 DirectCopy();

            Vec3 SET(double x, double y, double z);

            friend std::ostream & operator<<(std::ostream& target, const Vec3& source);

            Vec3 NEGATE();
            Vec3 NEGATEprecisely(bool x, bool y, bool z);

            double dot(Vec3 v);
    };
}
}

#endif // __cplusplus

#endif
