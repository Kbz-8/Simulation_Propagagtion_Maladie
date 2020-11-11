/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// messagebox.hpp
//
// AUTHOR: DAVID Malo
// CREATED: 08/11/2020
// UPDATED: 08/11/2020
/*=============================================================*/

#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#ifdef __cplusplus

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <string>

#include "../../Log/log.hpp"

namespace gut
{
namespace sdl
{
    class MessageBox
    {
        public:
            MessageBox();

            static void reportMessage(enum LogType type, std::string message, std::string logReport);

            ~MessageBox();

        private:
    };
}
}

#endif // __cplusplus

#endif // MESSAGEBOX_HPP
