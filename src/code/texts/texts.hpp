#ifndef __TEXTS_HPP__
#define __TEXTS_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../../includes/GUT/GUT.hpp"

class GameTexts
{
    public:
        GameTexts(GUTtext path);
        void getFilename(std::string path);
        void LoadTexts();
        std::string getText(std::string ID);
        std::vector<std::string> _LANGUAGES;
        std::vector<std::string> _LANGUAGES_PATHS;

        ~GameTexts();
    private:
        std::string _filename;
        std::vector<std::vector<std::string>> _TEXT_INFO;
};

#endif //__TEXTS_HPP__