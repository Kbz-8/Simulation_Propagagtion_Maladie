#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <GL/glew.h>

#include "../../../includes/GUT/GUT.hpp"
#include "entry/entry.hpp"
#include "../map/map.hpp"

class Menu: public gut::sdl::Input
{
    public:
        Menu(int width, int height);

        void updateMenu(Map &MAP);
        void renderMenu(gut::gl::Shader &main);

        virtual ~Menu();

        bool _go = false;
        bool _end = false;

    private:
        gut::gl::Text* _title;
        gut::gl::Button* _enter;
        gut::gl::Button* _reset;
        gut::gl::Button* _quit;

        gut::gl::Text* _sickNumberText;
        gut::gl::Text* _vaccinated_chanceText;
        gut::gl::Text* _mortalityText;
        gut::gl::Text* _contagiousness_chanceText;
        gut::gl::Text* _time_before_deathText;
        gut::gl::Text* _time_before_cureText;

        Entry* _sickNumberEntry;
        Entry* _vaccinated_chanceEntry;
        Entry* _mortalityEntry;
        Entry* _contagiousness_chanceEntry;
        Entry* _time_before_deathEntry;
        Entry* _time_before_cureEntry;

        TTF_Font *font = NULL;

        int _width;
        int _height;
};

#endif // MENU_HPP
