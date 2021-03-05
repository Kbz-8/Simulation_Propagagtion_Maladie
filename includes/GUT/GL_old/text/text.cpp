/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// text.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 04/11/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifdef __cplusplus

#include "text.hpp"

namespace gut
{
namespace gl2
{
    Text::Text(TTF_Font *font, enum ColorText color)
    {
        if(!TTF_WasInit() && TTF_Init() == -1) // Initialisation de SDL_TTF pour les textes
            sdl::MessageBox::reportMessage(ERROR, "Problème lors de l'initialisation de la librairie textuelle", SDL_GetError());

        _font = font;

        if(!_font) // Si il y a une erreur lors de la récupération de la police d'écriture, on envoie un message d'erreur
            sdl::MessageBox::reportMessage(ERROR, "Problème lors de l'initialisation d'une police d'écriture", SDL_GetError());

        _noir = {0, 0, 0}; // Couleur noire
        _blanc = {255, 255, 255}; // Couleur blanche

        switch(color)
        {
            case WHITE: _color = _blanc; break;
            case BLACK: _color = _noir; break;

            default: break;
        }

        glEnable(GL_BLEND); // Activations de la transparence
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Text::Text(const char* chemin, int Size, enum ColorText color)
    {
        _font = TTF_OpenFont(chemin, Size); // Récupération de la police d'écriture

        if(!_font) // Si il y a une erreur lors de la récupération de la police d'écriture, on envoie un message d'erreur
            sdl::MessageBox::reportMessage(ERROR, "Problème lors de la passation d'une police d'écriture", SDL_GetError());

        _noir = {0, 0, 0}; // Couleur noire
        _blanc = {255, 255, 255}; // Couleur blanche

        switch(color)
        {
            case WHITE: _color = _blanc; break;
            case BLACK: _color = _noir; break;

            default: break;
        }

        glEnable(GL_BLEND); // Activations de la transparence
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Text::Init(std::string text)
    {
     //=========== Recherche de demandes de retours à la ligne ===========//
        free_texture();

        newline = "\n";
        save = text; // Sauvegarde du texte
        found = text.find(newline); // Recherche de \n dans le texte

         // Nettoiyage des tableaux
        _lines.clear();
        _surf_hei.clear();
        _surf_wid.clear();

        COUNT = 0;

        if(found == std::string::npos) // Si aucun \n n'est trouvé, on créer la texture du texte
            _lines.push_back(generateTexture(text.c_str())); // On met la texture dans le tableau
        else
        {
            while(found != std::string::npos) // On compte combien de \n il y a dans le texte
            {
                COUNT++;
                found = text.find(newline, found + 1);
            }
            found = text.find(newline); // On rechrche le premier \n
            text.erase(found, text.size()); // On supprime ce qu'il y a à partir du \n
            _lines.push_back(generateTexture(text.c_str())); // On met la première ligne dans le tableau
            for(int i = 0; i < COUNT; i++)
            {
                text.clear(); // On supprime tout ce qu'il y a dans le texte
                if(i < COUNT-1) // Si il y a encore des \n après, on met dans le texte la partie qu'il y a entre les deux
                    text.append(save.begin() + found + newline.length(), save.begin() + save.find(newline, found + 1));
                else // Sinon on met dans le texte ce qu'il à apres le dernier \n
                    text.append(save.begin() + found + newline.length(), save.end());
                found = save.find(newline, found + 1); // On cherche le prochain \n dans le texte global
                _lines.push_back(generateTexture(text.c_str())); // On met la ligne dans le tableau
            }
        }
    }

    GLuint Text::generateTexture(const char* text)
    {
        SDL_Surface *_text_surf; // Surface SDL qui sera le texte

        _text_surf = TTF_RenderUTF8_Blended(_font, text, _color); // La surface SDL devient le texte

        if(!_text_surf) // Si la surface est nulle on envoie un message d'erreur
            sdl::MessageBox::reportMessage(ERROR, "Problème lors de l'initialisation d'un texte", SDL_GetError());

        _surf_wid.push_back(_text_surf->w); // On rempli les tableaux de dimensions de texte avec les dimensions de la ligne actuelle
        _surf_hei.push_back(_text_surf->h);

        GLuint _texture; // Texture OpenGL

        glGenTextures(1, &_texture); // On génère la texture
        glBindTexture(GL_TEXTURE_2D, _texture); // On vérouille la texture

        // ==================== Paramètres de la texture ==================== //
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // La texture prend la forme du texte
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _surf_wid.back(), _surf_hei.back(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _text_surf -> pixels);

        SDL_FreeSurface(_text_surf); // On libère la surface SDL car elle est devenue inutile

        if(_texture == NULL) // Si la texture est nulle on envoie un message d'erreur et on renvoie NULL
        {
            sdl::MessageBox::reportMessage(ERROR, "Impossible de génerer une texture à partir d'un texte", SDL_GetError());
            return NULL;
        }
        return _texture; // On renvoie la texture qui sera stockée dans le tableau
    }

    void Text::free_texture()
    {
        if(!_lines.empty())
        {
            for(int i = 0; i < _lines.size(); i++) // On supprime toutes les textures contenures dans le tableau
                glDeleteTextures(1, &_lines[i]);
        }
    }

    void Text::render(int x, int y, enum Alignement align)
    {
        for(int i = 0; i < _lines.size(); i++) // On parcoure toutes les textures du tableau pour les afficher
        {
            switch(align) // On regarde quel alignement est demandé
            {
                case RIGHT:
                    if(i > 0)
                        x += _surf_wid[i - 1] - _surf_wid[i];
                break;
                case CENTERED:
                    if(i > 0)
                        x += (_surf_wid[i - 1] - _surf_wid[i])/2;
                break;
                case LEFT:
                default: break;
            }

            if(_lines.size() > 1)
                y += TTF_FontLineSkip(_font); // Si il y a plus de 1 ligne, la position en Y prend la hauteur du texte du dessus

            glBindTexture(GL_TEXTURE_2D, _lines[i]); // On vérouille la texture du texte

        /* ============ Rendu du texte en Direct mode ============
         * Le direct est un autre mode de rendu avec OpenGL.
         * Il a la particularité d'être extrêmement simple
         * d'utilisation, mais aussi d'être assez lent car
         * les informations passent par la RAM avant d'être
         * envoyées à la carte graphique
         */

            glColor3f(1, 1, 1);

            glBegin(GL_QUADS); // On dit à OpenGL que rendu est carré

                //Coordonnées de la texture; Emplacement d'un vertex du texte;

                glTexCoord2f(0, 0); glVertex2f(x, y);
                glTexCoord2f(1, 0); glVertex2f(x + _surf_wid[i], y);
                glTexCoord2f(1, 1); glVertex2f(x + _surf_wid[i], y + _surf_hei[i]);
                glTexCoord2f(0, 1); glVertex2f(x, y + _surf_hei[i]);

            glEnd(); // Fin du rendu en Direct mode

            glBindTexture(GL_TEXTURE_2D, 0); // Dévérouillage de la texture
        }
    }

    Text::~Text()
    {
        if(!TTF_WasInit())
        {
            sdl::MessageBox::reportMessage(ERROR, "La TTF a été quittée avant de fermer les fonts", "Les fonts n'ont pas été libérées");
            return;
        }

        if(_font)
            TTF_CloseFont(_font); // Attention! Cela ferme aussi les font d'origines qui sont passées à l'objet!
        _font = NULL;
        free_texture(); // On libère les textures
    }
}
}

#endif // __cplusplus
