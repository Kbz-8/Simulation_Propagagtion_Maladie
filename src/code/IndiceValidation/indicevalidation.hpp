#ifndef INDICEVALIDATION_HPP
#define INDICEVALIDATION_HPP

#include <SDL2/SDL.h>


class IndiceValidation
{
    public:
        IndiceValidation(int pos_x, int pos_y, int SIZE);

        void setActive(bool activate);
        bool getActive();

        void update(SDL_Renderer* renderer);

        ~IndiceValidation();

    private:
        int _pos_x;
        int _pos_y;
        int _SIZE;

        bool _activate;

        SDL_Rect _Rectangle_1;
        SDL_Rect _Rectangle_2;
};

#endif // INDICEVALIDATION_HPP
