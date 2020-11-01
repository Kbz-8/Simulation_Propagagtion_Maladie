#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <GL/glew.h>

#include <iostream>
#include <string>

#include "../../../includes/GUT/GUT.hpp"

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

class Text
{
    public:
        Text(GUTtext chemin, int Size, enum ColorText color = BLACK);

        void Init(std::string text);
        void render(int x, int y, enum Alignement align = LEFT);

        void free_texture();

        virtual ~Text();

        std::vector<int> _surf_wid; // Tableau contenant toutes les largeurs des textes
        std::vector<int> _surf_hei; // Tableau contenant toutes les hauteurs des textes

    private:
        GLuint generateTexture(GUTtext text); // Fonction pour générer une texture à partir d'un texte

        TTF_Font *_font; // Police d'écriture

        SDL_Color _noir; // Couleurs
        SDL_Color _blanc;

        SDL_Color _color;

        int COUNT; // Conteur de retours à la ligne
        std::string newline; // String contenant \n pour chercher les retours à la ligne dans les textes
        std::string save; // Sauvegarde de tout le texte car il va être coupé dans l'opération
        std::size_t found; // Emplacements des \n
        std::size_t foundSAVE;

        std::vector<GLuint> _lines; // Tableau contenant toutes les lignes d'un texte
};

#endif // TEXT_HPP_INCLUDED
