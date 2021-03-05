/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// button.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 04/11/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifdef __cplusplus

#include "button.hpp"

namespace gut
{
namespace gl3
{
    Button::Button(int pos_x, int pos_y, int width, int height, const char* text, const char* path, unsigned int sizeFont) : Text(path, sizeFont, WHITE)
    {
        _pos_x = pos_x;
        _pos_y = pos_y;
        _pos_w = width;
        _pos_h = height;

        Init(text);
    }

    Button::Button(int pos_x, int pos_y, int width, int height, const char* text, TTF_Font *font) : Text(font, WHITE)
    {
        _pos_x = pos_x;
        _pos_y = pos_y;
        _pos_w = width;
        _pos_h = height;

        Init(text);
    }

    void Button::updateButton(int mouse_posx, int mouse_posy, bool isButtonDown, bool isbuttonUp, int ratioCorrecteur)
    {
        resetFunction();

        if(_ratioCorrecteur != ratioCorrecteur)
            _ratioCorrecteur = ratioCorrecteur;

        if(    mouse_posy >  _pos_y
            && mouse_posy <= _pos_y + _pos_h
            && mouse_posx >  _pos_x
            && mouse_posx <= _pos_x + _pos_w
            && isButtonDown)
            _button_down = true;
        if(isbuttonUp)
            _button_down = false;

        if(    mouse_posy >  _pos_y
            && mouse_posy <= _pos_y + _pos_h
            && mouse_posx >  _pos_x
            && mouse_posx <= _pos_x + _pos_w)
            _activate = true;
        else
            _activate = false;


        if(_activate && isbuttonUp)
            _function = true;
        else
            _function = false;
    }

    void Button::renderButton()
    {
        unsigned char *couleurs;

        float vertices[] = {
            _pos_x, _pos_y + _pos_h,             // v4
            _pos_x, _pos_y,                      // v1
            _pos_x + _pos_w, _pos_y,             // v2

            _pos_x, _pos_y + _pos_h,             // v4
            _pos_x + _pos_w, _pos_y,             // v2
            _pos_x + _pos_w, _pos_y + _pos_h     // v3
        };

        if(_activate)
        {
            couleurs = new unsigned char[16]{
                 90, 90, 90, 255,   90, 90, 90, 255,   90, 90, 90, 255,   90, 90, 90, 255
            };
        }
        else
        {
            couleurs = new unsigned char[16]{
                 75, 75, 75, 255,   75, 75, 75, 255,   75, 75, 75, 255,   75, 75, 75, 255
            };
        }
        if(_button_down)
        {
            couleurs = new unsigned char[16]{
                 35, 35, 35, 255,   35, 35, 35, 255,   35, 35, 35, 255,   35, 35, 35, 255
            };
        }

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)vertices);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 4, (void*)couleurs);

        glDrawArrays(GL_TRIANGLES, 6, sizeof(vertices));

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        delete[] couleurs;
    }

    void Button::rescale(int pos_x, int pos_y, int width, int height)
    {
        _pos_x = pos_x;
        _pos_y = pos_y;
        _pos_w = width;
        _pos_h = height;
    }

    void Button::updateTexte()
    {
        render(_pos_x + (_pos_w - _surf_wid.front())/2, _pos_y + _ratioCorrecteur + (_pos_h - _surf_hei.front())/2);
    }

    bool Button::getActivation()
    {
        return _function;
    }

    void Button::resetFunction()
    {
        _function = false;
    }

    Button::~Button() {}
}
}

#endif // __cplusplus
