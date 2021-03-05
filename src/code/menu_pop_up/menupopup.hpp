#ifndef MENUPOPUP_HPP
#define MENUPOPUP_HPP

#include <SDL2/SDL.h>
#include <iostream>


class MenuPopUp
{
    public:
        MenuPopUp(int pos_x, int pos_y, int w, int h);

        void call(bool activate, int pos_x, int pos_y);

        void updateRenderer();

        bool isOpen();

        int getID();

        ~MenuPopUp();

        SDL_Renderer* _renderer;

    private:
        SDL_Window *Menu;

        int _width;
        int _height;

        int _pos_x;
        int _pos_y;

        bool _activate;

        SDL_Rect _border;
};

#endif // MENUPOPUP_HPP
