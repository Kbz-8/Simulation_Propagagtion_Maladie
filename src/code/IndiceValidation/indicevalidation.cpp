#include "indicevalidation.hpp"

IndiceValidation::IndiceValidation(int pos_x, int pos_y, int SIZE)
{
    _pos_x = pos_x;
    _pos_y = pos_y;
    _SIZE = SIZE;

    _Rectangle_1 = {_pos_x, _pos_y, _SIZE, _SIZE};
    _Rectangle_2 = {_pos_x + 2, _pos_y + 2, _SIZE - 4, _SIZE - 4};
    
    _activate = false;
}

void IndiceValidation::setActive(bool activate)
{
    _activate = activate;
}

bool IndiceValidation::getActive()
{
    return _activate;
}

void IndiceValidation::update(SDL_Renderer* renderer)
{
    if(_activate)
    {
        SDL_SetRenderDrawColor(renderer, 110, 110, 110, 255);
        SDL_RenderFillRect(renderer, &_Rectangle_1);
    }

    else
    {
        SDL_SetRenderDrawColor(renderer, 110, 110, 110, 255);
        SDL_RenderFillRect(renderer, &_Rectangle_1);
        SDL_SetRenderDrawColor(renderer, 75, 75, 75, 255);
        SDL_RenderFillRect(renderer, &_Rectangle_2);
    }
}

IndiceValidation::~IndiceValidation() {}
