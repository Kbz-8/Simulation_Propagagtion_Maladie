/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// button.hpp
//
// AUTHOR: Malo DAVID
// CREATED: 13/11/2020
// UPDATED: 18/01/2021
/*=============================================================*/

#ifndef button_hpp
#define button_hpp

#ifdef __cplusplus

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../messagebox/messagebox.hpp"

#include <iostream>


namespace gut
{
namespace sdl
{

    class Button
    {
        public:
            Button(int pos_x, int pos_y, int wid, int hei, Uint32 winID, const char* path, unsigned int sizeFont, SDL_Renderer* renderer, const char* text);
            Button(int pos_x, int pos_y, int wid, int hei, Uint32 winID, const char* path, unsigned int sizeFont);

            void update(SDL_Renderer* renderer, int mouse_pos_x, int mouse_pos_y, bool mouse_button_up, bool mouse_button_down, Uint32 windowIDMouseMotion);

            void new_text(SDL_Renderer* renderer, const char* text);
            void text_update(SDL_Renderer* renderer);

            bool Function();

            ~Button();

        private:
            Uint32 winIDRequired;

            int _pos_x;
            int _pos_y;
            int _pos_w;
            int _pos_h;

            SDL_Rect _rectangle;

            bool _activate;
            bool _button_down;

            bool _function;


            TTF_Font *_font;
            SDL_Surface *_text_surface;
            SDL_Texture *_text_texture;

            SDL_Color _blanc;

            SDL_Rect _rect_text;
    };
}
}

#endif // __cplusplus
#endif // button_hpp
