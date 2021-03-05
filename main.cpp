/*==========================================================================*/
// Maths en JEAN
// Lycée Albert Claveille
//
// Simulation de la propagation d'une maladie dans une
// population donnée, selon plusieurs paramètres
// Cette simulation est grandement inspirée de celle-ci:
//
// https://github.com/angeluriot/Disease_propagation
//
// Simulation of the propagation of a disease in a
// given population, according to several parameters
// This simulation is largely inspired by this one:
//
// https://github.com/angeluriot/Disease_propagation
//
// Language: C++ (C++14)
// Compiler: GNU GCC
// Graphic Library: OpenGL(2.1), SDL_2 TTF, GLSL
// Window: SDL_2
// Extension: GUT(Global Utility Toolkit)
//
// AUTHOR: Malo DAVID <bilbo.sacquet@orange.fr>
// CREATED: 28/10/2020
// UPDATED: 18/01/2021
/*==========================================================================*/

/*====================== Includes ======================*/
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <memory>

#include "src/code/application.hpp"
#include "src/code/menu_pop_up/menupopup.hpp"
#include "src/code/IndiceValidation/indicevalidation.hpp"

/*======================= Globals ======================*/

GameTexts *texts;
#define launchWid 350
#define launchHei 150

/*==================== Fonction main ===================*/

int main(int argc, char *argv[])
{
    SDL_Window* screen; // Fenêtre SDL
    SDL_GLContext context; // Contexte OpenGL
    SDL_Rect rect; // Rectangle SDL pôur récupérer les dimensions utilisables de l'écran (sans la barre des taches)

    int fps = 0;
    int updatePerSecond = 0;

    Uint32 elapsed_time;
    Uint32 before = SDL_GetTicks();
    Uint32 timer = SDL_GetTicks();

    double ms = 1000.0 / 60.0;

    texts = new GameTexts("src/texts/languages.txt");

    /*================ OpenGL version ================*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if(SDL_Init(SDL_INIT_VIDEO) != 0) // Initialisation de la SDL
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, texts->getText("InitSDL"), SDL_GetError());

    /* ========================================================== Fenêtre de sélection de la langue ========================================================== */

    SDL_Window* languageWindow;
    SDL_Renderer* renderer;

    languageWindow = SDL_CreateWindow("Languages", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, launchWid, launchHei, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SHOWN);
    if(!languageWindow)
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, "Unable to create the language selection window", SDL_GetError());

    renderer = SDL_CreateRenderer(languageWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, "Unable to create the language selection renderer", SDL_GetError());

    int ID = SDL_GetWindowID(languageWindow);

    gut::sdl::Button selection(launchWid/2 - 140, launchHei/2 - 55, 275, 50, ID, "includes/GUT/GL_old/text/font/font_1.ttf", 20, renderer, "Languages");
    gut::sdl::Button go(launchWid/2 - 75, launchHei/2 + 5, 150, 50, ID, "includes/GUT/GL_old/text/font/font_1.ttf", 20, renderer, "Start");
    
    int x, y;
    SDL_GetWindowPosition(languageWindow, &x, &y);
    MenuPopUp menu(x + launchWid/2 - 140, y + launchHei/2 - 5, 275, texts->_LANGUAGES.size() * 55 + 20);
    bool openMenu = false;

    std::vector<std::shared_ptr<gut::sdl::Button>> lang_buttons;
    lang_buttons.clear();
    lang_buttons.reserve(texts->_LANGUAGES.size());

    std::vector<IndiceValidation> lang_val;
    lang_val.clear();
    lang_val.reserve(texts->_LANGUAGES.size());

    for(int i = 0; i < texts->_LANGUAGES.size(); i++)
    {
        std::shared_ptr<gut::sdl::Button> tempo(new gut::sdl::Button(10, i*55 + 10, 175, 50, menu.getID(), "includes/GUT/GL_old/text/font/font_1.ttf", 20, menu._renderer, texts->_LANGUAGES[i].c_str()));
        lang_buttons.push_back(tempo);

        lang_val.push_back(IndiceValidation(215, i*55 + 10, 50));
    }
    lang_val[0].setActive(true);
    texts->getFilename(texts->_LANGUAGES_PATHS[0]);

    gut::sdl::Input* input;
    input = new gut::sdl::Input;
    while(!input->fin())
    {
        SDL_SetRenderDrawColor(renderer, 50,  50, 50, 100);
        SDL_RenderClear(renderer);
        input->update();
        if(input->getTouche(SDL_SCANCODE_ESCAPE))
            input->end();
        if(openMenu)
        {
            menu.call(true, x + launchWid/2 - 140, y + launchHei/2);

            for(int i = 0; i < texts->_LANGUAGES.size(); i++)
            {
                lang_buttons[i]->update(menu._renderer, input->getX(), input->getY(), input->getBoutonSouris(1, UP), input->getBoutonSouris(1, DOWN), input->getWindowMouseMotion());
                lang_buttons[i]->text_update(menu._renderer);

                if(lang_buttons[i]->Function())
                {
                    lang_val[i].setActive(true);
                    for(int j = 0; j < lang_val.size(); j++)
                    {
                        if(j != i)
                            lang_val[j].setActive(false);
                    }
                    texts->getFilename(texts->_LANGUAGES_PATHS[i]);
                }

                lang_val[i].update(menu._renderer);
            }

            menu.updateRenderer();
        }
        else
            menu.call(false, x + launchWid/2 - 140, y + launchHei/2);

        selection.update(renderer, input->getX(), input->getY(), input->getBoutonSouris(1, UP), input->getBoutonSouris(1, DOWN), input->getWindowMouseMotion());
        selection.text_update(renderer);
        go.update(renderer, input->getX(), input->getY(), input->getBoutonSouris(1, UP), input->getBoutonSouris(1, DOWN), input->getWindowMouseMotion());
        go.text_update(renderer);
        SDL_GetWindowPosition(languageWindow, &x, &y);
        if(selection.Function())
        {
            if(openMenu) openMenu = false;
            else         openMenu = true;
        }
        if(go.Function())
            break;
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(languageWindow);

    if(input->fin())
    {
        delete input;
        SDL_Quit();
        std::cout << "SDL quitee" << std::endl;
        return 0;
    }
    delete input;

    texts->LoadTexts();

    /* ======================================================================================================================================================= */
    /* ======================================================================================================================================================= */

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Attributs d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if(SDL_GetDisplayUsableBounds(0, &rect) != 0) // Récupération de la zone utilisable par la fenêtre
        gut::sdl::MessageBox::reportMessage(ERROR, texts->getText("DisplayBounds"), SDL_GetError());

    screen = SDL_CreateWindow("Simulation", 0, 0, rect.w, rect.h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // Création de la fenêtre

    if(!screen)     // Mesure de sécurité en cas d'erreur lors de la création de la fenêtre
    {
        SDL_Quit();
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, texts->getText("CreateWindow"), SDL_GetError());
    }

    #if defined(_WIN32) || defined(_WIN64)
        int topBorder;
        SDL_GetWindowBordersSize(screen, &topBorder, NULL, NULL, NULL);
        rect.h -= topBorder;
        SDL_SetWindowSize(screen, rect.w, rect.h);
        SDL_SetWindowPosition(screen, 0, topBorder);
    #endif // _WIN32

    context = SDL_GL_CreateContext(screen); // Création du contexte OpenGL

    if(!context)    // Mesure de sécurité en cas d'erreur lors de la création du contexte OpenGL
    {
        SDL_DestroyWindow(screen);
        SDL_Quit();
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, texts->getText("OpenGLContext"), SDL_GetError());
    }

    GLuint GLEWerr = glewInit(); // Initialisation de GLEW

    if(GLEW_OK != GLEWerr)  // Mesure de sécurité en cas d'erreur lors de l'initialisation de GLEW
    {
        SDL_DestroyWindow(screen);
        SDL_Quit();
        gut::sdl::MessageBox::reportMessage(FATAL_ERROR, texts->getText("InitGLEW"), std::string(reinterpret_cast<GUTtext>(glewGetErrorString(GLEWerr))));
    }

    Application application(rect.w, rect.h); // Création d'un objet de la classe Application qui est la classe principale de la simulation

    std::string text_var; // Texte pour les FPS/UPS avec une variable String
    std::string informations;

    while(!application.menu->_end)  // Boucle principale
    {
        SDL_GL_SetSwapInterval(0);  //Pour laisser les FPS aller au delà du taux de rafraichissement de l'ecran

        if(SDL_GetTicks() - timer > 1000) // Toutes les secondes, on met à jours les éléments dans le if
        {
            text_var.clear();

            if(glIsBuffer(application.MAP->_vboID))
                text_var.append("VBO: ON");
            else
                text_var.append("VBO: OFF");
            text_var.append("\nFPS: ");
            text_var.append(std::to_string(fps));
            text_var.append("\nUPS: ");
            text_var.append(std::to_string(updatePerSecond));
            text_var.append(texts->getText("People"));
            text_var.append(std::to_string(application.MAP->_TableauPersonnes.size() * application.MAP->_TableauPersonnes.front().size()));

            application.text->Init(text_var);

            fps = 0;
            updatePerSecond = 0;
            timer += 1000;
        }

        elapsed_time = SDL_GetTicks() - before; // Temps écoulé depuis le dernier passage de la boucle
        if(elapsed_time >= ms)
        {
            /*========= Updates =========*/
            informations.clear();
            informations.append(texts->getText("Days"));
            informations.append(std::to_string(application.MAP->_daysPassed));
            informations.append(texts->getText("Healthy"));
            informations.append(std::to_string(application.MAP->_healthyNumber));
            informations.append(texts->getText("Sicks"));
            informations.append(std::to_string(application.MAP->_sicksNumber));
            informations.append(texts->getText("Vaccinated"));
            informations.append(std::to_string(application.MAP->_vaccinatedNumber));
            informations.append(texts->getText("Deads"));
            informations.append(std::to_string(application.MAP->_deadNumber));
            application.infos->Init(informations);

            application.updates();
            updatePerSecond++;
            before += ms;
        }
        else
        {
            /*========== Render =========*/
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On éfface ce qui est rendu à l'écran
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // On donne une couleur au fond de la fenêtre

            glMatrixMode(GL_MODELVIEW); // Matrice 2D
            glLoadIdentity();   // Matrice mise à 0

            glOrtho(-10.0, rect.w, rect.h, -10.0, -1.0, 1.0); // Mise en place d'un plan 2D

            application.render();
            fps++;
            SDL_GL_SwapWindow(screen); // Mise à jour de l'écran pour rendre dans la fenêtre tout ce qui à été fait
        }
    }
    SDL_DestroyWindow(screen);
    SDL_GL_DeleteContext(context);
    SDL_Quit();

    delete texts;

    return 0;
}
