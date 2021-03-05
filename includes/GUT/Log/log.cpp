/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// log.cpp
//
// Class for Logs
//
// AUTHOR: Malo DAVID
// CREATED: 04/09/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#include "log.hpp"

#ifdef __cplusplus

void TERMINATE()
{
    std::cout << "EXIT FAILURE: emergency abortion program" << std::endl;
    abort();
}

namespace gut
{

    Log::Log() {}

    void Log::report(enum LogType type, std::string message, std::string path)
    {
        std::ofstream test(getTime(type, path).c_str());
        if(test)
            test << message;
        if(type == FATAL_ERROR)
        {
            std::set_terminate(TERMINATE);
            std::terminate();
        }
    }

    std::string Log::getTime(enum LogType type, std::string path)
    {
        time_t tmm = time(0);

        // convertir en forme de chaîne
        char* dt = ctime(&tmm);

        std::string date = dt;

        switch(type)
        {
            case MESSAGE: path.append("/Messages/"); break;
            case WARNING: path.append("/Warnings/"); break;
            case ERROR:
            case FATAL_ERROR: path.append("/Errors/"); break;
            default: break;
        }

        path.append(date);
        path.append(".txt");

        return path;
    }

    Log::~Log() {}

}

#endif // __cplusplus
