/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// GUT.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 11/09/2020
// UPDATED: 03/12/2020
/*=============================================================*/

#include "GUT.hpp"

#ifdef __cplusplus

namespace gut
{
    void debugPrint(GUTtext text)
    {
        std::cout << bg_blue << bold << text << bg_def << bold_off << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Code code)
    {
        return os << "\033[1;" << std::to_string(code) << "m";
    }
}

#endif //__cplusplus
