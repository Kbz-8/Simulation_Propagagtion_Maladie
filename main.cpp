/*==========================================================================*/
// Maths en JEAN
// Lycée Albert Claveille
//
// Simulation de la propagation d'un virus dans une
// population donnée, selon plusieurs paramètres
// Cette simulation est grandement inspirée de celle-ci:
//
// https://github.com/angeluriot/Disease_propagation
//
// Simulation of the propagation of a virus in a
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
// UPDATED: 31/10/2020
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
        std::cout << "Impossible d'initialiser SDL_INIT_VIDEO" << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Attributs d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if(SDL_GetDisplayUsableBounds(0, &rect) != 0) // Récupération de la zone utilisable par la fenêtre
        std::cout << "Impossible de récupérer les dimensions de l'écran (Display Bounds)" << SDL_GetError() << std::endl; // Message en cas d'erreur

    screen = SDL_CreateWindow("Simulation", 0, 0, rect.w, rect.h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // Création de la fenêtre

    if(!screen)     // Mesure de sécurité en cas d'erreur lors de la création de la fenêtre
    {
        SDL_Quit();
        std::cout <<  "Impossible de créer la fenêtre" << SDL_GetError() << std::endl;
        return -1;
    }

    context = SDL_GL_CreateContext(screen); // Création du contexte OpenGL

    if(!context)    // Mesure de sécurité en cas d'erreur lors de la création du contexte OpenGL
    {
        SDL_DestroyWindow(screen);
        SDL_Quit();
        std::cout << "Erreur lors de la création du contexte OpenGL" << SDL_GetError() << std::endl;
        return -1;
    }

    GLuint GLEWerr = glewInit(); // Initialisation de GLEW

    if(GLEW_OK != GLEWerr)  // Mesure de sécurité en cas d'erreur lors de l'initialisation de GLEW
    {
        SDL_DestroyWindow(screen);
        SDL_Quit();
        std::cout << "Erreur lors de l'initialisation de GLEW: " << std::string(reinterpret_cast<GUTtext>(glewGetErrorString(GLEWerr))) << std::endl;
        return -1;
    }

    Application application(rect.w, rect.h); // Création d'un objet de la classe Application qui est la classe principale de la simulation

    std::string text_var; // Création du contenu du texte pour les FPS/UPS avec une variable String
    std::string days_var;

    while(!application.fin())  // Boucle principale
    {
        SDL_GL_SetSwapInterval(0);  //Pour laisser les FPS aller au delà du taux de rafraichissement de l'ecran

        if(SDL_GetTicks() - timer > 1000) // Toutes les secondes, on met à jours les éléments dans le if
        {
            text_var.clear();

            text_var.append("FPS: ");
            text_var.append(std::to_string(fps));
            text_var.append("\nUPS: ");
            text_var.append(std::to_string(updatePerSecond));

            application.text->free_texture();
            application.text->Init(text_var);

            fps = 0;
            updatePerSecond = 0;
            timer += 1000;
        }

        if(application.getTouche(SDL_SCANCODE_ESCAPE)) // Si la touche esc est préssée on sort de la boucle et le programme s'arrête
            break;

        elapsed_time = SDL_GetTicks() - before; // Temps écoulé depuis le dernier passage de la boucle
        if(elapsed_time >= ms)
        {
            /*========= Updates =========*/
            application.updates();
            updatePerSecond++;
            before += ms;

            days_var.clear();
            days_var.append("Jour: ");
            days_var.append(std::to_string(application._daysPassed));

            application.days->free_texture();
            application.days->Init(days_var);
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
