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
// Graphic Library: OpenGL(3.0), SDL_2 TTF, GLSL
// Window: SDL_2
// Extension: GUT(Global Utility Toolkit)
//
// AUTHOR: DAVID Malo
// CREATED: 28/10/2020
// UPDATED: 10/11/2020
/*==========================================================================*/

/*====================== Includes ======================*/
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

#include "src/code/application.hpp"

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

    /*================ OpenGL version ================*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if(SDL_Init(SDL_INIT_VIDEO) != 0) // Initialisation de la SDL
    {
        gut::sdl::MessageBox::reportMessage(ERROR, "Impossible d'initialiser SDL_INIT_VIDEO", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Attributs d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if(SDL_GetDisplayUsableBounds(0, &rect) != 0) // Récupération de la zone utilisable par la fenêtre
        gut::sdl::MessageBox::reportMessage(ERROR, "Impossible de récupérer les dimensions de l'écran (Display Bounds)", SDL_GetError());

    screen = SDL_CreateWindow("Simulation", 0, 0, rect.w, rect.h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // Création de la fenêtre

    if(!screen)     // Mesure de sécurité en cas d'erreur lors de la création de la fenêtre
    {
        SDL_Quit();
        gut::sdl::MessageBox::reportMessage(ERROR, "Impossible de créer la fenêtre", SDL_GetError());
        return -1;
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
        gut::sdl::MessageBox::reportMessage(ERROR, "Erreur lors de la création du contexte OpenGL", SDL_GetError());
        return -1;
    }

    GLuint GLEWerr = glewInit(); // Initialisation de GLEW

    if(GLEW_OK != GLEWerr)  // Mesure de sécurité en cas d'erreur lors de l'initialisation de GLEW
    {
        SDL_DestroyWindow(screen);
        SDL_Quit();
        gut::sdl::MessageBox::reportMessage(ERROR, "Erreur lors de l'initialisation de GLEW:", std::string(reinterpret_cast<GUTtext>(glewGetErrorString(GLEWerr))));
        return -1;
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
            text_var.append("\nPersonnes: ");
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
            informations.append("Jours: ");
            informations.append(std::to_string(application.MAP->_daysPassed));
            informations.append("\n \n \nSains: ");
            informations.append(std::to_string(application.MAP->_healthyNumber));
            informations.append("\nMalades: ");
            informations.append(std::to_string(application.MAP->_sicksNumber));
            informations.append("\nImmunisés: ");
            informations.append(std::to_string(application.MAP->_vaccinatedNumber));
            informations.append("\nMorts: ");
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
    return 0;
}
