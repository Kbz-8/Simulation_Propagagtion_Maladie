/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// button.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 13/11/2020
// UPDATED: 17/01/2021
/*=============================================================*/

#ifdef __cplusplus

#include "button.hpp"

namespace gut
{
namespace sdl
{

    Button::Button(int pos_x, int pos_y, int wid, int hei, Uint32 winID, const char* path, unsigned int sizeFont, SDL_Renderer* renderer, const char* text)
    {
        winIDRequired = winID;

        _button_down = false;
        _activate = false;
        _function = false;

        _pos_x = pos_x;
        _pos_y = pos_y;
        _pos_w = wid;
        _pos_h = hei;

        _rectangle.x = _pos_x;
        _rectangle.y = _pos_y;
        _rectangle.w = _pos_w;
        _rectangle.h = _pos_h;

        if(TTF_Init() == -1)
            MessageBox::reportMessage(ERROR, "Impossible d'initialiser la TTF", TTF_GetError());

        _font = TTF_OpenFont(path, sizeFont);

        if(!_font)
            MessageBox::reportMessage(ERROR, "Impossible d'initialiser une font", TTF_GetError());


        _blanc = {200, 200, 200};

        _text_surface = TTF_RenderUTF8_Blended(_font, text, _blanc);

        _rect_text.x = _rectangle.x + (_rectangle.w - _text_surface->w)/2;
        _rect_text.y = _rectangle.y + (_rectangle.h - _text_surface->h)/2 + 1;
        _rect_text.w = _text_surface->w;
        _rect_text.h = _text_surface->h;

        _text_texture = SDL_CreateTextureFromSurface(renderer, _text_surface);
    }
    Button::Button(int pos_x, int pos_y, int wid, int hei, Uint32 winID, const char* path, unsigned int sizeFont)
    {
        winIDRequired = winID;

        _button_down = false;
        _activate = false;
        _function = false;

        _pos_x = pos_x;
        _pos_y = pos_y;
        _pos_w = wid;
        _pos_h = hei;

        _rectangle.x = _pos_x;
        _rectangle.y = _pos_y;
        _rectangle.w = _pos_w;
        _rectangle.h = _pos_h;

        if(TTF_Init() == -1)
            MessageBox::reportMessage(ERROR, "Impossible d'initialiser la TTF", TTF_GetError());

        _font = TTF_OpenFont(path, sizeFont);

        if(!_font)
            MessageBox::reportMessage(ERROR, "Impossible d'initialiser une font", TTF_GetError());


        _blanc = {200, 200, 200};

        _rect_text.x = _pos_x;
        _rect_text.y = _pos_y;
        _rect_text.w = _pos_w;
        _rect_text.h = _pos_h;
    }

    void Button::update(SDL_Renderer* renderer, int mouse_pos_x, int mouse_pos_y, bool mouse_button_up, bool mouse_button_down, Uint32 windowIDMouseMotion)
    {
        if(windowIDMouseMotion == winIDRequired)
        {
            if (   mouse_pos_y > _pos_y
                && mouse_pos_y <= _pos_y + _pos_h
                && mouse_pos_x > _pos_x
                && mouse_pos_x <= _pos_x + _pos_w
                && mouse_button_down)
                _button_down = true;

            if(mouse_button_up)
                _button_down = false;

            if (   mouse_pos_y > _pos_y
                && mouse_pos_y <= _pos_y + _pos_h
                && mouse_pos_x > _pos_x
                && mouse_pos_x <= _pos_x + _pos_w)
                _activate = true;

            else
                _activate = false;

            if(mouse_button_up && _activate)
                _function = true;
            else
                _function = false;
        }

        if(!_activate)
        {
            SDL_SetRenderDrawColor(renderer, 75, 75, 75, 255);
            SDL_RenderFillRect(renderer, &_rectangle);
        }

        else
        {
            SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
            SDL_RenderFillRect(renderer, &_rectangle);
        }

        if(_button_down)
        {
            SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
            SDL_RenderFillRect(renderer, &_rectangle);
        }
    }

    void Button::new_text(SDL_Renderer* renderer, const char* text)
    {
        _text_surface = TTF_RenderUTF8_Blended(_font, text, _blanc);

        _rect_text.x = _rectangle.x + (_rectangle.w - _text_surface->w)/2;
        _rect_text.y = _rectangle.y + (_rectangle.h - _text_surface->h)/2 + 1;
        _rect_text.w = _text_surface->w;
        _rect_text.h = _text_surface->h;

        _text_texture = SDL_CreateTextureFromSurface(renderer, _text_surface);
    }

    void Button::text_update(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, _text_texture, NULL, &_rect_text);
    }

    bool Button::Function()
    {
        return _function;
    }

    Button::~Button()
    {
        TTF_CloseFont(_font);
        TTF_Quit();
        SDL_FreeSurface(_text_surface);
        SDL_DestroyTexture(_text_texture);
    }

}
}

#endif // __cplusplus
