/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// messagebox.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 08/11/2020
// UPDATED: 08/11/2020
/*=============================================================*/

#ifdef __cplusplus

#include "messagebox.hpp"

namespace gut
{
namespace sdl
{
    MessageBox::MessageBox() {}

    void MessageBox::reportMessage(enum LogType type, std::string message, std::string logReport)
    {
        SDL_MessageBoxButtonData buttons[] = {
            {NULL, 0, "Plus de détails"},
            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "ok"}
        };
        const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                {56, 54, 53},
                /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                {233, 233, 233},
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                {180, 180, 180},
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                {105, 102, 99},
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                {160, 160, 160}
            }
        };

        Uint32 flag = SDL_MESSAGEBOX_INFORMATION;
        const char* title;

        switch(type)
        {
            case MESSAGE: flag = SDL_MESSAGEBOX_INFORMATION; title = "Message"; break;
            case WARNING: flag = SDL_MESSAGEBOX_WARNING; title = "Warning"; break;
            case ERROR:   flag = SDL_MESSAGEBOX_ERROR; title = "Error"; break;
            case FATAL_ERROR:   flag = SDL_MESSAGEBOX_ERROR; title = "Fatal Error"; break;

            default: break;
        }

        SDL_MessageBoxData messageboxdata = {
            flag, /* .flags */
            NULL, /* .window */
            title, /* .title */
            message.c_str(), /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
        };

        int buttonid;

        SDL_ShowMessageBox(&messageboxdata, &buttonid);

        if(buttonid == 1)
            Log::report(type, logReport, "Log_Report");
        else
        {
            message.append(":\n");
            message.append(logReport);

            SDL_MessageBoxButtonData buttons2[] = {
                {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "ok"}
            };

             messageboxdata = {
                flag, /* .flags */
                NULL, /* .window */
                title, /* .title */
                message.c_str(), /* .message */
                SDL_arraysize(buttons2), /* .numbuttons */
                buttons2, /* .buttons */
                &colorScheme /* .colorScheme */
            };

            SDL_ShowMessageBox(&messageboxdata, &buttonid);
            if(buttonid == 1)
                Log::report(type, logReport, "Log_Report");
        }
    }

    MessageBox::~MessageBox() {}
}
}

#endif // __cplusplus
