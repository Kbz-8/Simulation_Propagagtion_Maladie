/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// text.hpp
//
// AUTHOR: Malo DAVID
// CREATED: 04/11/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#ifdef __cplusplus

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <GL/glew.h>

#include <iostream>
#include <string>

#include "../../SDL2/messagebox/messagebox.hpp"

#include <vector>

enum ColorText
{
    WHITE, // Couleur possible du texte
    BLACK
};

enum Alignement
{
    LEFT,
    CENTERED,
    RIGHT
};

namespace gut
{
namespace gl3
{
    class Text
    {
        public:
            Text(TTF_Font *font, enum ColorText color = BLACK);
            Text(const char* chemin, int Size, enum ColorText color = BLACK);

            void Init(std::string text);
            void render(int x, int y, enum Alignement align = LEFT);

            void free_texture();

            virtual ~Text();

            std::vector<int> _surf_wid; // Tableau contenant toutes les largeurs des textes
            std::vector<int> _surf_hei; // Tableau contenant toutes les hauteurs des textes

        private:
            GLuint generateTexture(const char* text); // Fonction pour générer une texture à partir d'un texte

            TTF_Font *_font = NULL; // Police d'écriture

            SDL_Color _noir; // Couleurs
            SDL_Color _blanc;

            SDL_Color _color;

            float *_coords_tex;

            int COUNT; // Conteur de retours à la ligne
            std::string newline; // String contenant \n pour chercher les retours à la ligne dans les textes
            std::string save; // Sauvegarde de tout le texte car il va être coupé dans l'opération
            std::size_t found; // Emplacements des \n

            std::vector<GLuint> _lines; // Tableau contenant toutes les lignes d'un texte
    };
}
}

#endif // __cplusplus

#endif // TEXT_HPP_INCLUDED
