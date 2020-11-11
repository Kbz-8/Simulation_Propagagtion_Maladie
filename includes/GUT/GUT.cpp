/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// GUT.cpp
//
// AUTHOR: DAVID Malo
// CREATED: 11/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#include "GUT.hpp"

#ifdef __cplusplus

namespace gut
{

    void debugPrint(GUTtext text)
    {
        std::cout << text << std::endl;
    }

}

#endif //__cplusplus
