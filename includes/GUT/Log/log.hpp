/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// log.hpp
//
// Class for Logs
//
// AUTHOR: Malo DAVID
// CREATED: 04/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef LOG_HPP
#define LOG_HPP

#ifdef __cplusplus

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>

enum LogType
{
    MESSAGE,
    WARNING,
    ERROR,
    FATAL_ERROR
};

namespace gut
{
    class Log
    {
        public:
            Log();

            static void report(enum LogType type, std::string message, std::string path);

            ~Log();

        private:
            static std::string getTime(enum LogType type, std::string path);
    };
}



#endif // __cplusplus

#endif // LOG_HPP
