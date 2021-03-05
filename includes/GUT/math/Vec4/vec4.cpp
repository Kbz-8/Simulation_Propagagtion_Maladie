/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// vec4.cpp
//
// Class for 4D vectors
//
// AUTHOR: Malo DAVID
// CREATED: 09/10/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#include "vec4.hpp"

#ifdef __cplusplus

namespace gut
{
namespace math
{
    Vec4::Vec4()
    {
        X = 0;
        Y = 0;
        Z = 0;
        W = 0;
    }

    Vec4::Vec4(double x, double y, double z, double w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    Vec4::Vec4(const Vec4 & v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
    }

    Vec4::Vec4(const Vec4 & from, const Vec4 & to)
    {
        X = to.X - from.X;
        Y = to.Y - from.Y;
        Z = to.Z - from.Z;
        W = to.W - from.W;
    }

    Vec4 & Vec4::operator= (const Vec4 & v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = v.W;
        return *this;
    }

    bool Vec4::operator== (const Vec4 & v)
    {
        if(X == v.X && Y == v.Y && Z == v.Z && W == v.W)
            return true;
        return false;
    }

    bool Vec4::operator!= (const Vec4 & v)
    {
        if(X != v.X && Y != v.Y && Z != v.Z && W != v.W)
            return true;
        return false;
    }



    bool Vec4::operator== (const double valeur)
    {
        if(X == valeur && Y == valeur && Z == valeur && W == valeur)
            return true;
        return false;
    }

    bool Vec4::operator!= (const double valeur)
    {
        if(X != valeur && Y != valeur && Z != valeur && W != valeur)
            return true;
        return false;
    }

    Vec4 & Vec4::operator+= (const Vec4 & v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        W += v.W;
        return *this;
    }

    Vec4 Vec4::operator+ (const Vec4 & v) const
    {
        Vec4 t = *this;
        t += v;
        return t;
    }

    Vec4 Vec4::operator+ (const double valeur)
    {
        X += valeur;
        Y += valeur;
        Z += valeur;
        W += valeur;
        return *this;
    }

    Vec4 & Vec4::operator-= (const Vec4 & v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        W -= v.W;
        return *this;
    }

    Vec4 Vec4::operator- (const Vec4 & v) const
    {
        Vec4 t = *this;
        t -= v;
        return t;
    }

    Vec4 Vec4::operator- (const double valeur)
    {
        X -= valeur;
        Y -= valeur;
        Z -= valeur;
        W -= valeur;
        return *this;
    }

    Vec4 & Vec4::operator*= (const double a)
    {
        X *= a;
        Y *= a;
        Z *= a;
        W *= a;
        return *this;
    }

    Vec4 Vec4::operator* (const double a)const
    {
        Vec4 t = *this;
        t *= a;
        return t;
    }

    Vec4 operator* (const double a, const Vec4 & v)
    {
        return Vec4(v.X*a, v.Y*a, v.Z*a, v.W*a);
    }

    Vec4 & Vec4::operator* (const Vec4 &v)
    {
        X *= v.X;
        Y *= v.Y;
        Z *= v.Z;
        W *= v.W;
        return *this;
    }

    Vec4 & Vec4::operator/= (const double a)
    {
        X /= a;
        Y /= a;
        Z /= a;
        W /= a;
        return *this;
    }

    Vec4 Vec4::operator/ (const double a)const
    {
        Vec4 t = *this;
        t /= a;
        return t;
    }

    bool Vec4::operator< (const Vec4 &v)
    {
        if(X < v.X && Y < v.Y && Z < v.Z && W < v.W)
            return true;
        return false;
    }
    bool Vec4::operator< (const double valeur)
    {
        if(X < valeur && Y < valeur && Z < valeur && W < valeur)
            return true;
        return false;
    }




    bool Vec4::operator> (const Vec4 &v)
    {
        if(X > v.X && Y > v.Y && Z > v.Z && W > v.W)
            return true;
        return false;
    }
    bool Vec4::operator> (const double valeur)
    {
        if(X > valeur && Y > valeur && Z > valeur && W > valeur)
            return true;
        return false;
    }




    bool Vec4::operator<= (const Vec4 &v)
    {
        if(X <= v.X && Y <= v.Y && Z <= v.Z && W <= v.W)
            return true;
        return false;
    }
    bool Vec4::operator<= (const double valeur)
    {
        if(X <= valeur && Y <= valeur && Z <= valeur && W <= valeur)
            return true;
        return false;
    }




    bool Vec4::operator>= (const Vec4 &v)
    {
        if(X >= v.X && Y >= v.Y && Z >= v.Z && W >= v.W)
            return true;
        return false;
    }
    bool Vec4::operator>= (const double valeur)
    {
        if(X >= valeur && Y >= valeur && Z >= valeur && W >= valeur)
            return true;
        return false;
    }



    Vec4 Vec4::crossProduct(const Vec4 & v)const
    {
        Vec4 t;
        t.X = Y*v.Z - Z*v.Y;
        t.Y = Z*v.X - X*v.Z;
        t.Z = X*v.Y - Y*v.X;
        t.W = 1;
        return t;
    }

    double Vec4::length()const
    {
        return sqrt(X*X + Y*Y + Z*Z + W*W);
    }

    Vec4 & Vec4::normalize()
    {
        (*this) /= length();
        return (*this);
    }

    Vec4 Vec4::COPY(const Vec4 &v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = v.W;
        return *this;
    }

    Vec4 Vec4::DirectCopy()
    {
        Vec4 cop;
        cop.X = X;
        cop.Y = Y;
        cop.Z = Z;
        cop.W = W;
        return cop;
    }

    Vec4 Vec4::SET(double x, double y, double z, double w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
        return *this;
    }

    std::ostream & operator<<(std::ostream& target, const Vec4& source)
    {
        target << source.X << ", " << source.Y << ", " << source.Z << ", " << source.W;
        return target;
    }

    Vec4 Vec4::NEGATE()
    {
        X = -X;
        Y = -Y;
        Z = -Z;
        W = -W;
        return *this;
    }

    Vec4 Vec4::NEGATEprecisely(bool x, bool y, bool z, bool w)
    {
        if(x) X = -X;
        if(y) Y = -Y;
        if(z) Z = -Z;
        if(w) W = -W;
        return *this;
    }

    double Vec4::dot(Vec4 v)
    {
        return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
    }
}
}

#endif // __cplusplus
