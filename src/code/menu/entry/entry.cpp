#include "entry.hpp"

Entry::Entry(enum EntryTYPE type, int pos_x, int pos_y, int width, int height, GUTtext path, GUTuint sizeFont): gut::gl2::Text(path, sizeFont, WHITE)
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

Entry::Entry(enum EntryTYPE type, int pos_x, int pos_y, int width, int height, TTF_Font *font): gut::gl2::Text(font, WHITE)
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

void Entry::updateEntry(gut::sdl::Input &input)
{
    if(    input.getY() >  _pos_y
        && input.getY() <= _pos_y + _pos_h
        && input.getX() >  _pos_x
        && input.getX() <= _pos_x + _pos_w
        && input.getBoutonSouris(1))
        _activate = true;
    if(   (input.getY() < _pos_y
        || input.getY() > _pos_y + _pos_h
        || input.getX() < _pos_x
        || input.getX() > _pos_x + _pos_w)
        && input.getBoutonSouris(1))
        _activate = false;

    if(_activate)
        updateTexte(input);
    else
    {
        if(_type == PERCENT)
        {
            _text.replace(_text.begin(),     _text.begin() + 1, std::to_string(_units[0]));
            _text.replace(_text.begin() + 1, _text.begin() + 2, std::to_string(_units[1]));
            _text.replace(_text.begin() + 2, _text.begin() + 3, std::to_string(_units[2]));
            _text.replace(_text.begin() + 4, _text.begin() + 5, std::to_string(_units[3]));
            _text.replace(_text.begin() + 5, _text.begin() + 6, std::to_string(_units[4]));
        }
        else
        {
            _text.replace(_text.begin(),     _text.begin() + 1, std::to_string(_units[0]));
            _text.replace(_text.begin() + 1, _text.begin() + 2, std::to_string(_units[1]));
            _text.replace(_text.begin() + 2, _text.begin() + 3, std::to_string(_units[2]));
        }

        Init(_text);

        _timer = 0;
    }
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

void Entry::updateTexte(gut::sdl::Input &input)
{
    if(input.getTouche(SDL_SCANCODE_RIGHT, UP))
        _canChangeRIGHT = true;
    if(input.getTouche(SDL_SCANCODE_LEFT, UP) && _whichSizeOn != 0)
        _canChangeLEFT = true;

    if(input._isTyping)
        _typingText = input.getTextEntry();

    if(input.getTouche(SDL_SCANCODE_BACKSPACE))
        _isErasing = true;
    if(input.getTouche(SDL_SCANCODE_BACKSPACE, UP))
        _isErasing = false;

    if(_isErasing)
        _typingText = "0";

    if(_timer == 60)
        _timer = 0;

    _timer++;

    switch(_whichSizeOn)
    {
        case 0:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_units[0]);
            std::istringstream(_typingText) >> _units[0];
            if(input._isTyping) _canChangeRIGHT = true;
            if(_units[0] != 0 && _type == PERCENT) _units[0] = 1;
            if(_timer < 30) _text.replace(_text.begin(), _text.begin() + 1, " ");
            if(_timer > 30 || _canChangeLEFT || _canChangeRIGHT) _text.replace(_text.begin(), _text.begin() + 1, std::to_string(_units[0]));
        break;

        case 1:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_units[1]);
            std::istringstream(_typingText) >> _units[1];
            if(input._isTyping) _canChangeRIGHT = true;
            if(_units[0] != 0 && _type == PERCENT) _units[1] = 0;
            if(_timer < 30) _text.replace(_text.begin() + 1, _text.begin() + 2, " ");
            if(_timer > 30 || _canChangeLEFT || _canChangeRIGHT) _text.replace(_text.begin() + 1, _text.begin() + 2, std::to_string(_units[1]));
        break;

        case 2:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_units[2]);
            std::istringstream(_typingText) >> _units[2];
            if(input._isTyping) _canChangeRIGHT = true;
            if(_units[0] != 0 && _type == PERCENT) _units[2] = 0;
            if(_timer < 30) _text.replace(_text.begin() + 2, _text.begin() + 3, " ");
            if(_timer > 30 || _canChangeLEFT || _canChangeRIGHT) _text.replace(_text.begin() + 2, _text.begin() + 3, std::to_string(_units[2]));
        break;

        case 3:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_units[3]);
            std::istringstream(_typingText) >> _units[3];
            if(input._isTyping) _canChangeRIGHT = true;
            if(_units[0] != 0) _units[3] = 0;
            if(_timer < 30) _text.replace(_text.begin() + 4, _text.begin() + 5, " ");
            if(_timer > 30 || _canChangeLEFT || _canChangeRIGHT) _text.replace(_text.begin() + 4, _text.begin() + 5, std::to_string(_units[3]));
        break;

        case 4:
            if(!input._isTyping && !_isErasing) _typingText = std::to_string(_units[4]);
            std::istringstream(_typingText) >> _units[4];
            if(input._isTyping) _canChangeRIGHT = true;
            if(_units[0] != 0) _units[4] = 0;
            if(_timer < 30) _text.replace(_text.begin() + 5, _text.begin() + 6, " ");
            if(_timer > 30 || _canChangeLEFT || _canChangeRIGHT) _text.replace(_text.begin() + 5, _text.begin() + 6, std::to_string(_units[4]));
        break;

        default: break;
    }
    input._isTyping = false;

    Init(_text);

    _percent = ((_units[1]*10) + _units[2] + (_units[3]/10.0) + (_units[4]/100.0)) / 100.0;

    if(_units[0] && _type == PERCENT)
        _percent = 1.0;

    _integer = (_units[0]*100) + (_units[1]*10) + _units[2];

    if(_canChangeRIGHT)
    {
        _timer = 0;
        if(_type == PERCENT && _whichSizeOn != 4)
            _whichSizeOn++;
        else if(_type == INTEGER && _whichSizeOn != 2)
            _whichSizeOn++;
    }

    if(_canChangeLEFT)
    {
        _whichSizeOn--;
        _timer = 0;
    }

    _canChangeLEFT = false;
    _canChangeRIGHT = false;
}

void Entry::renderTexte()
{
    render(_pos_x + (_pos_w - _surf_wid.front())/2, _pos_y + (_pos_h - _surf_hei.front())/2);
}

Entry::~Entry() {}
