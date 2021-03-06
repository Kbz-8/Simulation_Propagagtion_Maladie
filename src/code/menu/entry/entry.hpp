#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <GL/glew.h>
#include <iostream>
#include <sstream>

#include "../../../../includes/GUT/GUT.hpp"

enum EntryTYPE
{
    PERCENT,
    INTEGER
};

class Entry : public gut::gl2::Text
{
    public:
        Entry(enum EntryTYPE type, int pos_x, int pos_y, int width, int height, GUTtext path, GUTuint sizeFont = 30);
        Entry(enum EntryTYPE type, int pos_x, int pos_y, int width, int height, TTF_Font *font);

        void updateEntry(gut::sdl::Input &input);
        void renderEntry();
        void renderTexte();

        ~Entry();

        bool _activate = false;

        double _percent = 0.0;
        int _integer = 0;

        int _pos_x;
        int _pos_y;
        int _pos_w;
        int _pos_h;

    private:
        void updateTexte(gut::sdl::Input &input);

        int _units[5] = {0, 0, 0, 0, 0};

        char _whichSizeOn = 0;

        std::string _text;
        std::string _typingText = "0";

        bool _isErasing = false;

        enum EntryTYPE _type;

        int _timer = 0;
        bool _canChangeLEFT = false;
        bool _canChangeRIGHT = false;
};

#endif // ENTRY_HPP
