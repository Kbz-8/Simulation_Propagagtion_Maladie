#include "texts.hpp"

GameTexts::GameTexts(GUTtext path)
{
    std::string languageDATA;
    bool commentaire = false;
    bool SWITCH = false;
    std::size_t found;
    std::ifstream getLanguages(path, std::ios::in);
    if(getLanguages)
    {
        while(getLanguages >> languageDATA)
        {
            found = languageDATA.find("/*");

            if(found != std::string::npos)
                commentaire = true;

            if(!commentaire)
            {
                if(!SWITCH)
                {
                    _LANGUAGES.push_back(languageDATA);
                    SWITCH = true;
                }
                else
                {
                    _LANGUAGES_PATHS.push_back(languageDATA);
                    SWITCH = false;
                } 
            }

            found = languageDATA.find("*/");

            if(found != std::string::npos)
                commentaire = false;

            languageDATA.clear();
        }
		getLanguages.close();
    }
    else
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, "Unable to get the languages", std::string(strerror(errno)));
}

void GameTexts::getFilename(std::string path)
{
    _filename = path;
}

void GameTexts::LoadTexts()
{
    std::string languageDATA;
    std::string textData;
    bool commentaire = false;
    std::vector<std::string> DoubleVector;
    char completion = 0;
    std::size_t found;
    std::ifstream languageINIT(_filename.c_str(), std::ios::in);
    if(languageINIT)
    {
        while(languageINIT >> languageDATA)
        {
            found = languageDATA.find("/*");

            if(found != std::string::npos)
                commentaire = true;

            if(!commentaire)
            {
                if(languageDATA == "==")
                {
                    completion = 1;
                    languageDATA.clear();
                }

                found = languageDATA.find("\\n");
                if(found != std::string::npos)
                    languageDATA.replace(languageDATA.begin() + found, languageDATA.begin() + found + 2, "\n");

                found = languageDATA.find(";");
                if(found != std::string::npos)
                    languageDATA.pop_back();

                if(completion == 0)
                {
                    DoubleVector.push_back(languageDATA);
                }
                if(completion == 1)
                {
                    textData.append(languageDATA);
                    textData.append(" ");
                }

                if(found != std::string::npos)
                    completion = 2;
                
                if(completion == 2)
                {
                    DoubleVector.push_back(textData);
                    _TEXT_INFO.push_back(DoubleVector);
                    DoubleVector.clear();
                    textData.clear();
                    completion = 0;
                }
            }

            found = languageDATA.find("*/");

            if(found != std::string::npos)
                commentaire = false;

            languageDATA.clear();
        }
		languageINIT.close();
    }
    else
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, "Unable to get the texts from the language selected", std::string(strerror(errno)));
}

std::string GameTexts::getText(std::string ID)
{
    for(int i = 0; i < _TEXT_INFO.size(); i++)
    {
        if(ID == _TEXT_INFO[i][0])
            return _TEXT_INFO[i][1];
    }
    return "ERROR";
}

GameTexts::~GameTexts() {}
