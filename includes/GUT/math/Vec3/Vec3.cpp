/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// Vec3.cpp
//
// Class for 3D vectors
//
// AUTHOR: DAVID Malo
// CREATED: 11/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#include "Vec3.hpp"

#ifdef __cplusplus

namespace gut
{
namespace math
{
    Vec3::Vec3()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    Vec3::Vec3(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    Vec3::Vec3(const Vec3 & v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
    }

    Vec3::Vec3(const Vec3 & from, const Vec3 & to)
    {
        X = to.X - from.X;
        Y = to.Y - from.Y;
        Z = to.Z - from.Z;
    }

    Vec3 & Vec3::operator= (const Vec3 & v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        return *this;
    }

    bool Vec3::operator== (const Vec3 & v)
    {
        if(X == v.X && Y == v.Y && Z == v.Z)
            return true;
        return false;
    }

    bool Vec3::operator!= (const Vec3 & v)
    {
        if(X != v.X && Y != v.Y && Z != v.Z)
            return true;
        return false;
    }



    bool Vec3::operator== (const double valeur)
    {
        if(X == valeur && Y == valeur && Z == valeur)
            return true;
        return false;
    }

    bool Vec3::operator!= (const double valeur)
    {
        if(X != valeur && Y != valeur && Z != valeur)
            return true;
        return false;
    }

    Vec3 & Vec3::operator+= (const Vec3 & v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return *this;
    }

    Vec3 Vec3::operator+ (const Vec3 & v) const
    {
        Vec3 t = *this;
        t += v;
        return t;
    }

    Vec3 Vec3::operator+ (const double valeur)
    {
        X += valeur;
        Y += valeur;
        Z += valeur;

        return *this;
    }

    Vec3 & Vec3::operator-= (const Vec3 & v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        return *this;
    }

    Vec3 Vec3::operator- (const Vec3 & v) const
    {
        Vec3 t = *this;
        t -= v;
        return t;
    }

    Vec3 Vec3::operator- (const double valeur)
    {
        X -= valeur;
        Y -= valeur;
        Z -= valeur;

        return *this;
    }

    Vec3 & Vec3::operator*= (const double a)
    {
        X *= a;
        Y *= a;
        Z *= a;
        return *this;
    }

    Vec3 Vec3::operator* (const double a)const
    {
        Vec3 t = *this;
        t *= a;
        return t;
    }

    /*
     ######
    ##    ##   ##     ##
    ##         ##     ##
    ##       ###### ######
    ##         ##     ##
    ##    ##   ##     ##
     ######

    ░░░░░░░░░░░░▄▄░░░░░░░░░
    ░░░░░░░░░░░█░░█░░░░░░░░
    ░░░░░░░░░░░█░░█░░░░░░░░
    ░░░░░░░░░░█░░░█░░░░░░░░
    ░░░░░░░░░█░░░░█░░░░░░░░
    ███████▄▄█░░░░░██████▄░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█░░░░░░░░░░░░░░█░
    ▓▓▓▓▓▓█████░░░░░░░░░█░░
    ██████▀░░░░▀▀██████▀░░░
    */


    Vec3 operator* (const double a, const Vec3 & v)
    {
        return Vec3(v.X*a,v.Y*a,v.Z*a);
    }

    Vec3 & Vec3::operator* (const Vec3 &v)
    {
        X *= v.X;
        Y *= v.Y;
        Z *= v.Z;
        return *this;
    }

    Vec3 & Vec3::operator/= (const double a)
    {
        X /= a;
        Y /= a;
        Z /= a;
        return *this;
    }

    Vec3 Vec3::operator/ (const double a)const
    {
        Vec3 t = *this;
        t /= a;
        return t;
    }

    bool Vec3::operator< (const Vec3 &v)
    {
        if(X < v.X && Y < v.Y && Z < v.Z)
            return true;
        return false;
    }
    bool Vec3::operator< (const double valeur)
    {
        if(X < valeur && Y < valeur && Z < valeur)
            return true;
        return false;
    }




    bool Vec3::operator> (const Vec3 &v)
    {
        if(X > v.X && Y > v.Y && Z > v.Z)
            return true;
        return false;
    }
    bool Vec3::operator> (const double valeur)
    {
        if(X > valeur && Y > valeur && Z > valeur)
            return true;
        return false;
    }




    bool Vec3::operator<= (const Vec3 &v)
    {
        if(X <= v.X && Y <= v.Y && Z <= v.Z)
            return true;
        return false;
    }
    bool Vec3::operator<= (const double valeur)
    {
        if(X <= valeur && Y <= valeur && Z <= valeur)
            return true;
        return false;
    }




    bool Vec3::operator>= (const Vec3 &v)
    {
        if(X >= v.X && Y >= v.Y && Z >= v.Z)
            return true;
        return false;
    }
    bool Vec3::operator>= (const double valeur)
    {
        if(X >= valeur && Y >= valeur && Z >= valeur)
            return true;
        return false;
    }



    Vec3 Vec3::crossProduct(const Vec3 & v)const
    {
        Vec3 t;
        t.X = Y*v.Z - Z*v.Y;
        t.Y = Z*v.X - X*v.Z;
        t.Z = X*v.Y - Y*v.X;
        return t;
    }

    double Vec3::length()const
    {
        return sqrt(X*X + Y*Y + Z*Z);
    }

    Vec3 & Vec3::normalize()
    {
        (*this) /= length();
        return (*this);
    }

    Vec3 Vec3::COPY(const Vec3 &v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;

        return *this;
    }

    Vec3 Vec3::DirectCopy()
    {
        Vec3 cop;
        cop.X = X;
        cop.Y = Y;
        cop.Z = Z;
        return cop;
    }

    Vec3 Vec3::SET(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;

        return *this;
    }

    std::ostream & operator<<(std::ostream& target, const Vec3& source)
    {
        target << source.X << ", " << source.Y << ", " << source.Z;
        return target;
    }

    Vec3 Vec3::NEGATE()
    {
        X = -X;
        Y = -Y;
        Z = -Z;
        return *this;
    }

    Vec3 Vec3::NEGATEprecisely(bool x, bool y, bool z)
    {
        if(x) X = -X;
        if(y) Y = -Y;
        if(z) Z = -Z;

        return *this;
    }

    double Vec3::dot(Vec3 v)
    {
        return X * v.X + Y * v.Y + Z * v.Z;
    }
}
}

#endif // __cplusplus
