#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <GL/glew.h>
#include "../text/text.hpp"
#include "../input/input.hpp"
#include "../shader/shader.hpp"
#include "button/button.hpp"

class Menu
{
    public:
        Menu(int width, int height);

        void updateMenu(Input& input);
        void renderMenu(Shader &main);

        virtual ~Menu();

        bool _go = false;

    private:
        Text* _title;
        Text* _test;
        Button* _enter;

        int _width;
        int _height;
};

#endif // MENU_HPP
