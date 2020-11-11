/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// input.cpp
//
// AUTHOR: DAVID Malo
// CREATED: 04/11/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifdef __cplusplus

#include "input.hpp"

#include <iostream>

namespace gut
{
namespace sdl
{
    Input::Input()
    {
        std::cout << "Commandes initialisées" << std::endl;

        _x = 0;
        _y = 0;
        _xRel = 0;
        _yRel = 0;

        // Stockage de toutes les touches et boutons de souris dans les tableaux
        for(int i = 0; i < SDL_NUM_SCANCODES; i++)
        {
            _touchesUP[i] = false;
            _touchesDOWN[i] = false;
            if(i < 8)
            {
                _boutonsSourisUP[i] = false;
                _boutonsSourisDOWN[i] = false;
            }
        }
    }

    void Input::update()
    {
        _xRel = 0;
        _yRel = 0;

        // Réinitialisation des tableaux de relachement
        for(int i = 0; i < SDL_NUM_SCANCODES; i++)
        {
            _touchesUP[i] = false;
            if(i < 8)
                _boutonsSourisUP[i] = false;
        }

        while(SDL_PollEvent(&evenements)) // Tant que des évenements se passent
        {
            if(evenements.window.event == SDL_WINDOWEVENT_CLOSE) // On vérifie si la croix de fermeture de la fenêtre est cliquée
                fini = true;

            switch(evenements.type) // On regarde les types d'évenements
            {
                case SDL_KEYDOWN: // Touche du clavier enfoncée
                    _touchesDOWN[evenements.key.keysym.scancode] = true;
                    _touchesUP[evenements.key.keysym.scancode] = false;
                break;


                case SDL_KEYUP: // Touche du clavier relachée
                    _touchesDOWN[evenements.key.keysym.scancode] = false;
                    _touchesUP[evenements.key.keysym.scancode] = true;
                break;

                case SDL_MOUSEBUTTONDOWN: // Bouton de la souris enfoncé
                    _boutonsSourisDOWN[evenements.button.button] = true;
                    _boutonsSourisUP[evenements.button.button] = false;
                break;

                case SDL_MOUSEBUTTONUP: // Bouton de la souris relaché
                    _boutonsSourisDOWN[evenements.button.button] = false;
                    _boutonsSourisUP[evenements.button.button] = true;
                break;

                case SDL_TEXTINPUT: // Entrée de texte
                    if(_isTextInputAllow)
                    {
                        _text_input_string = evenements.text.text;
                        _isTyping = true;
                    }
                break;


                default: break;
            }

            if(evenements.type == SDL_MOUSEMOTION) // Mouvement de la souris
            {
                    _x = evenements.motion.x;
                    _y = evenements.motion.y;

                    _xRel = evenements.motion.xrel;
                    _yRel = evenements.motion.yrel;
            }
        }
    }

    void Input::activateTextInput(bool activate)
    {
        _isTextInputAllow = activate;
    }

    bool Input::getTouche(const SDL_Scancode touche, enum ButtonACTION type) const
    {
        if(type == DOWN) // Si la touche demandée est à enfoncer, on retourne la valeur de cette touche (true ou false)
            return _touchesDOWN[touche];
        return _touchesUP[touche]; // Si la touche demandée est à relacher, on retourne la valeur de cette touche (true ou false)
    }

    bool Input::getBoutonSouris(const Uint8 bouton, enum ButtonACTION type) const
    {
        if(type == DOWN) // Si le bouton souris demandé est à enfoncer, on retourne la valeur de ce bouton (true ou false)
            return _boutonsSourisDOWN[bouton];
        return _boutonsSourisUP[bouton]; // Si le bouton souris demandé est à relacher, on retourne la valeur de ce bouton (true ou false)
    }

    bool Input::mouvementSouris() const
    {
        if(!_xRel && !_yRel) // Si il y a un movement de souris on renvoie True sinon on renvoie False
            return false;
        return true;
    }

    int Input::getX() const
    {
        return _x; // Renvoie de la position X de la souris sur l'écran
    }
    int Input::getY() const
    {
        return _y; // Renvoie de la position Y de la souris sur l'écran
    }

    int Input::getXRel() const
    {
        return _xRel; // Renvoie du mouvement horizontal de la souris
    }
    int Input::getYRel() const
    {
        return _yRel; // Renvoie du mouvement vertical de la souris
    }

    std::string Input::getTextEntry()
    {
        return _text_input_string;
    }

    bool Input::fin() const
    {
        return fini;
    }


    Input::~Input()
    {
        std::cout << "Commandes liberées" << std::endl;
    }
}
}

#endif // __cplusplus
