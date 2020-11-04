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

class Entry : public Text
{
    public:
        Entry(enum EntryTYPE type, int pos_x, int pos_y, int width, int height, GUTtext path, GUTuint sizeFont = 30);

        void updateEntry(int mouse_posx, int mouse_posy, bool isButtonDown);
        void renderEntry();

        void updateTexte(Input &input);
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
        int _hundreds = 0;
        int _tens = 0;
        int _units = 0;
        int _tenths = 0;
        int _hundredths = 0;

        char _whichSizeOn = 0;

        std::string _text;
        std::string _typingText = "0";

        bool _isErasing = false;

        enum EntryTYPE _type;
};

#endif // ENTRY_HPP
