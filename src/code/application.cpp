#include "application.hpp"

Application::Application(int width, int height) : Shader("src/shaders/main.vert", "src/shaders/main.frag"), Input(), Map(width, height), Menu(width, height) // Initialisations des classes héritées
{
    _width = width;
    _height = height;

    text = new Text("src/code/text/font/font_1.ttf", 15, WHITE); // Initialisation des textes
    text->Init(" "); // Au début il n'affiche rien tant qu'on a pas les informations à lui transmettre
    days = new Text("src/code/text/font/font_1.ttf", 15, WHITE);
    days->Init("0");
}

void Application::updates()
{
    update(); // Update des inputs
    if(!_go)
        updateMenu(*this);
}

void Application::render()
{
    bindShader(); // Application du shader principal
    setBool("isTexture", true); // On dit au shader qu'il y a une texture à rendre car les textes sont des textures
    text->render(_width - 140,  -10); // Rendu des textes

    if(!_go)
    {
        renderMenu(*this);
        return;
    }
    days->render(_width - 140,  50);

    setBool("isTexture", false); // On lui dit qu'il n'y a que des couleurs à rendre ici
    renderPopulation(); // On rend la population
}

Application::~Application()
{
    unbindShader();
    delete text; // Supression manuelle des textes car ils sont initialisés en allocation dynamique
    delete days;
}
