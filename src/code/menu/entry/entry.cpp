#include "entry.hpp"

Entry::Entry(enum EntryTYPE type, int pos_x, int pos_y, int width, int height, GUTtext path, GUTuint sizeFont): Text(path, sizeFont, WHITE)
{
    _pos_x = pos_x;
    _pos_y = pos_y;
    _pos_w = width;
    _pos_h = height;

    _type = type;

    switch(_type)
    {
        case PERCENT: _text = "000.00%"; break;
        case INTEGER: _text = "000"; break;

        default: break;
    }

    Init(_text);
}

void Entry::updateEntry(int mouse_posx, int mouse_posy, bool isButtonDown)
{
    if(    mouse_posy >  _pos_y
        && mouse_posy <= _pos_y + _pos_h
        && mouse_posx >  _pos_x
        && mouse_posx <= _pos_x + _pos_w
        && isButtonDown)
        _activate = true;
    if(   (mouse_posy < _pos_y
        || mouse_posy > _pos_y + _pos_h
        || mouse_posx < _pos_x
        || mouse_posx > _pos_x + _pos_w)
        && isButtonDown)
        _activate = false;
}

void Entry::renderEntry()
{
    if(_activate)
        glColor3ub(90, 90, 90);
    else
        glColor3ub(75, 75, 75);

    glBegin(GL_QUADS);
        glVertex2f(_pos_x,  _pos_y);
        glVertex2f(_pos_x + _pos_w,  _pos_y);
        glVertex2f(_pos_x + _pos_w,  _pos_y + _pos_h);
        glVertex2f(_pos_x,  _pos_y + _pos_h);
    glEnd();
}

void Entry::updateTexte(Input &input)
{
    if(input.getTouche(SDL_SCANCODE_RIGHT, UP))
    {
        if(_type == PERCENT && _whichSizeOn != 4)
            _whichSizeOn++;
        else if(_type == INTEGER && _whichSizeOn != 2)
            _whichSizeOn++;
    }
    if(input.getTouche(SDL_SCANCODE_LEFT, UP) && _whichSizeOn != 0)
        _whichSizeOn--;

    if(input._isTyping)
        _typingText = input.getTextEntry();

    if(input.getTouche(SDL_SCANCODE_BACKSPACE))
        _isErasing = true;
    if(input.getTouche(SDL_SCANCODE_BACKSPACE, UP))
        _isErasing = false;

    if(_isErasing)
        _typingText = "0";

    switch(_whichSizeOn)
    {
        case 0:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_hundreds);
            std::istringstream(_typingText) >> _hundreds;
            if(_hundreds != 0) _hundreds = 1;
            _text.replace(_text.begin(), _text.begin() + 1, std::to_string(_hundreds));
        break;

        case 1:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_tens);
            std::istringstream(_typingText) >> _tens;
            if(_hundreds != 0 && _type == PERCENT) _tens = 0;
            _text.replace(_text.begin() + 1, _text.begin() + 2, std::to_string(_tens));
        break;

        case 2:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_units);
            std::istringstream(_typingText) >> _units;
            if(_hundreds != 0 && _type == PERCENT) _units = 0;
            _text.replace(_text.begin() + 2, _text.begin() + 3, std::to_string(_units));
        break;

        case 3:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_tenths);
            std::istringstream(_typingText) >> _tenths;
            if(_hundreds != 0) _tenths = 0;
            _text.replace(_text.begin() + 4, _text.begin() + 5, std::to_string(_tenths));
        break;

        case 4:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_hundredths);
            std::istringstream(_typingText) >> _hundredths;
            if(_hundreds != 0) _hundredths = 0;
            _text.replace(_text.begin() + 5, _text.begin() + 6, std::to_string(_hundredths));
        break;

        default: break;
    }
    input._isTyping = false;

    Init(_text);

    _percent = ((_tens*10) + _units + (_tenths/10.0) + (_hundredths/100.0)) / 100.0;

    if(_hundreds && _type == PERCENT)
        _percent = 1.0;

    _integer = (_hundreds*100) + (_tens*10) + _units;
}

void Entry::renderTexte()
{
    render(_pos_x + (_pos_w - _surf_wid.front())/2, _pos_y + (_pos_h - _surf_hei.front())/2);
}

Entry::~Entry()
{
    //dtor
}
