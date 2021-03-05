#include "menupopup.hpp"

MenuPopUp::MenuPopUp(int pos_x, int pos_y, int w, int h)
{
    _width = w;
    _height = h;

    _pos_x = pos_x;
    _pos_y = pos_y;

    Menu = SDL_CreateWindow(NULL, _pos_x, _pos_y, _width, _height, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_POPUP_MENU);
    _renderer = SDL_CreateRenderer(Menu, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    _border = {2, 2, _width - 4, _height - 4};
}

void MenuPopUp::call(bool activate, int pos_x, int pos_y)
{
    _pos_x = pos_x;
    _pos_y = pos_y;

    SDL_SetWindowPosition(Menu, _pos_x, _pos_y);

    _activate = activate;

    if(_activate)
    {
        SDL_ShowWindow(Menu);

        SDL_SetRenderDrawColor(_renderer, 90, 90, 90, 255);
        SDL_RenderClear(_renderer);

        SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(_renderer, &_border);
    }

    else
        SDL_HideWindow(Menu);
}

void MenuPopUp::updateRenderer()
{
    if(_activate)
        SDL_RenderPresent(_renderer);
}

bool MenuPopUp::isOpen()
{
    return _activate;
}

int MenuPopUp::getID()
{
    return SDL_GetWindowID(Menu);
}

MenuPopUp::~MenuPopUp()
{
    SDL_DestroyWindow(Menu);
    SDL_DestroyRenderer(_renderer);
}
