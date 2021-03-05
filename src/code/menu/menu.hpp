#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <GL/glew.h>

#include "../../../includes/GUT/GUT.hpp"
#include "entry/entry.hpp"
#include "../map/map.hpp"
#include "../texts/texts.hpp"

class Menu: public gut::sdl::Input
{
    public:
        Menu(int width, int height);

        void updateMenu(Map &MAP);
        void renderMenu(gut::gl2::Shader &main);

        virtual ~Menu();

        bool _go = false;
        bool _end = false;

    private:
        gut::gl2::Text* _title;
        gut::gl2::Button* _enter;
        gut::gl2::Button* _reset;
        gut::gl2::Button* _quit;

        gut::gl2::Text* _sickNumberText;
        gut::gl2::Text* _vaccinated_chanceText;
        gut::gl2::Text* _mortalityText;
        gut::gl2::Text* _contagiousness_chanceText;
        gut::gl2::Text* _time_before_deathText;
        gut::gl2::Text* _time_before_cureText;

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
