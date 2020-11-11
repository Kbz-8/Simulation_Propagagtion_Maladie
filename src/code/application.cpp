#include "application.hpp"

Application::Application(int width, int height)
{
    _width = width;
    _height = height;

    _pause = false;

    menu = new Menu(width, height);
    MAP = new Map(width, height);
    MAIN = new gut::gl::Shader("src/shaders/main.vert", "src/shaders/main.frag");

    text = new gut::gl::Text("includes/GUT/GL/text/font/font_1.ttf", 15, WHITE); // Initialisation des textes
    text->Init(" "); // Au début il n'affiche rien tant qu'on a pas les informations à lui transmettre
    infos = new gut::gl::Text("includes/GUT/GL/text/font/font_1.ttf", 15, WHITE);
    infos->Init("0");
    STATIC = new gut::gl::Text("includes/GUT/GL/text/font/font_1.ttf", 15, WHITE);
    STATIC->Init("Retour au menu: esc/echap\nPause: espace\n \nRègles:\n           Vert = sain\n           Rouge = malade\n           Bleu = immunisé\n           Noir = mort");

    std::cout << "Simulation initialisée" << std::endl << std::endl;
}

void Application::updates()
{
    menu->update(); // Update des inputs
    if(menu->fin())
        menu->_end = true;

    if(!menu->_go)
    {
        _pause = false;
        menu->activateTextInput(true);
        menu->updateMenu(*MAP);
        return;
    }

    if(menu->getTouche(SDL_SCANCODE_ESCAPE, UP))
        menu->_go = false;
    if(menu->getTouche(SDL_SCANCODE_SPACE, UP))
    {
        if(!_pause)
            _pause = true;
        else
            _pause = false;
    }
}

void Application::render()
{
    MAIN->bindShader(); // Application du shader principal
    MAIN->setBool("isTexture", true); // On dit au shader qu'il y a une texture à rendre car les textes sont des textures

    if(!menu->_go)
    {
        text->render(_width - 143,  -10); // Rendu des textes
        menu->renderMenu(*MAIN);
        return;
    }
    text->render((int)((_width/5) * 4 + 20),  -10);
    infos->render((int)((_width/5) * 4 + 20),  90);
    STATIC->render((int)((_width/5) * 4 + 20),  240);

    MAIN->setBool("isTexture", false); // On lui dit qu'il n'y a que des couleurs à rendre ici
    MAP->renderPopulation(_pause);
}

Application::~Application()
{
    // Supression manuelle des objets car ils sont initialisés en allocation dynamique
    delete infos;
    delete text;
    delete STATIC;

    delete menu;
    delete MAIN;
    delete MAP;

    TTF_Quit();

    std::cout << std::endl << "Simulation libérée" << std::endl << std::endl;
}
