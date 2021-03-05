/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// math.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 31/10/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifdef __cplusplus

#include "math.hpp"

namespace gut
{
    namespace math
    {
        int randint(int a, int b)
        {
            return rand() % (b - a) + a;
        }

        bool rand_probability(double proba)
        {
            if(proba < 1)
                return ((double)rand() / (double)RAND_MAX < proba);
            else if(proba == 1)
                return true;
            return false;
        }
    }
}

#endif // __cplusplus
