#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../../includes/GUT/GUT.hpp"
#include "input/input.hpp"
#include "shader/shader.hpp"
#include "map/map.hpp"
#include "text/text.hpp"
#include "menu/menu.hpp"

#include <iostream>

class Application : public Shader, public Input, public Map, public Menu // Classes héritées par la classe Application
{
    public:
        Application(int width, int height); // Constructeur de la classe

        void updates(); // Fonctions contenant toutes les updates
        void render();  // Fonction contenant tous les rendus

        ~Application(); // Destructeur de la classe

        Text *text; // Textes
        Text *days; // Texte jours

    private:
        int _width; // Dimensions de la fenêtre récupérées dans le constructeur
        int _height;
};

#endif // APPLICATION_HPP
