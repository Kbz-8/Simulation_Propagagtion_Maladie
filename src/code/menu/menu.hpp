#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <GL/glew.h>

#include "../../../includes/GUT/GUT.hpp"
#include "entry/entry.hpp"
#include "../map/map.hpp"

class Menu: public Input
{
    public:
        Menu(int width, int height);

        void updateMenu(Map &MAP);
        void renderMenu(Shader &main);

        virtual ~Menu();

        bool _go = false;

        Entry* _vaccinated_chanceEntry;
        Entry* _mortalityEntry;
        Entry* _contagiousness_chanceEntry;
        Entry* _time_before_deathEntry;
        Entry* _time_before_cureEntry;

    private:
        Text* _title;
        Text* _test;
        Button* _enter;

        Text* _vaccinated_chanceText;
        Text* _mortalityText;
        Text* _contagiousness_chanceText;
        Text* _time_before_deathText;
        Text* _time_before_cureText;

        int _width;
        int _height;
};

#endif // MENU_HPP
