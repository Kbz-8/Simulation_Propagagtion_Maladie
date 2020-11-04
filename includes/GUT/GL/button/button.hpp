/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// button.hpp
//
// AUTHOR: DAVID Malo
// CREATED: 04/11/2020
// UPDATED: 04/11/2020
/*=============================================================*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <GL/glew.h>
#include <iostream>

#include "../text/text.hpp"

class Button : public Text
{
    public:
        Button(int pos_x, int pos_y, int width, int height, const char* text, const char* path, unsigned int sizeFont = 30);

        void updateButton(int mouse_posx, int mouse_posy, bool isButtonDown, bool isbuttonUp, int ratioCorrecteur = 0);
        void renderButton();
        void updateTexte();

        void rescale(int pos_x, int pos_y, int width, int height);

        bool getActivation();
        void resetFunction();

        ~Button();

    private:
        int _pos_x;
        int _pos_y;
        int _pos_w;
        int _pos_h;

        bool _activate = false;
        bool _button_down = false;

        bool _function = false;

        int _ratioCorrecteur = 0;
};

#endif // BUTTON_HPP
