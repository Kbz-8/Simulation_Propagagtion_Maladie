#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <GL/glew.h>
#include <iostream>

#include "../../../../includes/GUT/GUT.hpp"
#include "../../text/text.hpp"

class Button : public Text
{
    public:
        Button(int pos_x, int pos_y, int width, int height, GUTtext text, GUTtext path, GUTuint sizeFont = 30);

        void update(int mouse_posx, int mouse_posy, bool isButtonDown, bool isbuttonUp, int ratioCorrecteur = 0);
        void renderButton();
        void updateTexte(int width, int height);

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
