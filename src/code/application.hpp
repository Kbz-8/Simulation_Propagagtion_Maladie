#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../../includes/GUT/GUT.hpp"
#include "map/map.hpp"
#include "menu/menu.hpp"

#include <iostream>

class Application
{
    public:
        Application(int width, int height); // Constructeur de la classe

        void updates(); // Fonctions contenant toutes les updates
        void render();  // Fonction contenant tous les rendus

        ~Application(); // Destructeur de la classe

        gut::gl::Text *text; // Textes
        gut::gl::Text *infos; // Texte informatif
        gut::gl::Text *STATIC; // Texte static

        Menu* menu;
        gut::gl::Shader* MAIN;
        Map* MAP;

    private:
        int _width; // Dimensions de la fenêtre récupérées dans le constructeur
        int _height;

        bool _pause;
};

#endif // APPLICATION_HPP
