#include "button.hpp"

Button::Button(int pos_x, int pos_y, int width, int height, GUTtext text, GUTtext path, GUTuint sizeFont) : Text(path, sizeFont, WHITE)
{
    _pos_x = pos_x;
    _pos_y = pos_y;
    _pos_w = width;
    _pos_h = height;

    Init(text);
}

void Button::update(int mouse_posx, int mouse_posy, bool isButtonDown, bool isbuttonUp, int ratioCorrecteur)
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
    if(_activate)
        glColor3ub(90, 90, 90);
    else
        glColor3ub(75, 75, 75);

    if(_button_down)
        glColor3ub(35, 35, 35);

    glBegin(GL_QUADS);
        glVertex2f(_pos_x,  _pos_y);
        glVertex2f(_pos_x + _pos_w,  _pos_y);
        glVertex2f(_pos_x + _pos_w,  _pos_y + _pos_h);
        glVertex2f(_pos_x,  _pos_y + _pos_h);
    glEnd();
}

void Button::rescale(int pos_x, int pos_y, int width, int height)
{
    _pos_x = pos_x;
    _pos_y = pos_y;
    _pos_w = width;
    _pos_h = height;
}

void Button::updateTexte(int width, int height)
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