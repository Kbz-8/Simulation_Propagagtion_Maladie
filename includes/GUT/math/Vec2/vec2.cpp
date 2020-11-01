/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// vec2.cpp
//
// Class for 2D vectors
//
// AUTHOR: DAVID Malo
// CREATED: 11/09/2020
// UPDATED: 20/09/2020
/*=============================================================*/

#include "vec2.hpp"

#ifdef __cplusplus

Vec2::Vec2()
{
    X = 0;
    Y = 0;
}

Vec2::Vec2(double x, double y)
{
    X = x;
    Y = y;
}

Vec2::Vec2(const Vec2 & v)
{
    X = v.X;
    Y = v.Y;
}

Vec2::Vec2(const Vec2 & from, const Vec2 & to)
{
    X = to.X - from.X;
    Y = to.Y - from.Y;
}

Vec2 & Vec2::operator= (const Vec2 & v)
{
    X = v.X;
    Y = v.Y;
    return *this;
}

bool Vec2::operator== (const Vec2 & v)
{
    if(X == v.X && Y == v.Y)
        return true;
    return false;
}

bool Vec2::operator!= (const Vec2 & v)
{
    if(X != v.X && Y != v.Y)
        return true;
    return false;
}



bool Vec2::operator== (const double valeur)
{
    if(X == valeur && Y == valeur)
        return true;
    return false;
}

bool Vec2::operator!= (const double valeur)
{
    if(X != valeur && Y != valeur)
        return true;
    return false;
}

Vec2 & Vec2::operator+= (const Vec2 & v)
{
    X += v.X;
    Y += v.Y;
    return *this;
}

Vec2 Vec2::operator+ (const Vec2 & v) const
{
    Vec2 t = *this;
    t += v;
    return t;
}

Vec2 Vec2::operator+ (const double valeur)
{
    X += valeur;
    Y += valeur;
    return *this;
}

Vec2 & Vec2::operator-= (const Vec2 & v)
{
    X -= v.X;
    Y -= v.Y;
    return *this;
}

Vec2 Vec2::operator- (const Vec2 & v) const
{
    Vec2 t = *this;
    t -= v;
    return t;
}

Vec2 Vec2::operator- (const double valeur)
{
    X -= valeur;
    Y -= valeur;
    return *this;
}

Vec2 & Vec2::operator*= (const double a)
{
    X *= a;
    Y *= a;
    return *this;
}

Vec2 Vec2::operator* (const double a)const
{
    Vec2 t = *this;
    t *= a;
    return t;
}

Vec2 operator* (const double a, const Vec2 & v)
{
    return Vec2(v.X*a, v.Y*a);
}

Vec2 & Vec2::operator* (const Vec2 &v)
{
    X *= v.X;
    Y *= v.Y;
    return *this;
}

Vec2 & Vec2::operator/= (const double a)
{
    X /= a;
    Y /= a;
    return *this;
}

Vec2 Vec2::operator/ (const double a)const
{
    Vec2 t = *this;
    t /= a;
    return t;
}

bool Vec2::operator< (const Vec2 &v)
{
    if(X < v.X && Y < v.Y)
        return true;
    return false;
}
bool Vec2::operator< (const double valeur)
{
    if(X < valeur && Y < valeur)
        return true;
    return false;
}




bool Vec2::operator> (const Vec2 &v)
{
    if(X > v.X && Y > v.Y)
        return true;
    return false;
}
bool Vec2::operator> (const double valeur)
{
    if(X > valeur && Y > valeur)
        return true;
    return false;
}




bool Vec2::operator<= (const Vec2 &v)
{
    if(X <= v.X && Y <= v.Y)
        return true;
    return false;
}
bool Vec2::operator<= (const double valeur)
{
    if(X <= valeur && Y <= valeur)
        return true;
    return false;
}




bool Vec2::operator>= (const Vec2 &v)
{
    if(X >= v.X && Y >= v.Y)
        return true;
    return false;
}
bool Vec2::operator>= (const double valeur)
{
    if(X >= valeur && Y >= valeur)
        return true;
    return false;
}



Vec2 Vec2::crossProduct(const Vec2 & v)const
{
    return Vec2(v.Y, -v.X);
}

double Vec2::length()const
{
    return sqrt(X*X + Y*Y);
}

Vec2 & Vec2::normalize()
{
    (*this) /= length();
    return (*this);
}

Vec2 Vec2::COPY(const Vec2 &v)
{
	X = v.X;
	Y = v.Y;

	return *this;
}

Vec2 Vec2::DirectCopy()
{
    Vec2 cop;
    cop.X = X;
    cop.Y = Y;
    return cop;
}

Vec2 Vec2::SET(double x, double y)
{
	X = x;
	Y = y;

	return *this;
}

std::ostream & operator<<(std::ostream& target, const Vec2& source)
{
    target << source.X << ", " << source.Y;
    return target;
}

Vec2 Vec2::NEGATE()
{
    X = -X;
    Y = -Y;
    return *this;
}

Vec2 Vec2::NEGATEprecisely(bool x, bool y)
{
    if(x) X = -X;
    if(y) Y = -Y;

    return *this;
}

double Vec2::dot(Vec2 v)
{
    return X * v.X + Y * v.Y;
}

#endif // __cplusplus
