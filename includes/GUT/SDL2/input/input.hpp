/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// input.hpp
//
// AUTHOR: Malo DAVID
// CREATED: 04/11/2020
// UPDATED: 07/11/2020
/*=============================================================*/

#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#ifdef __cplusplus

#include <SDL2/SDL.h>
#include <string>

enum ButtonACTION
{
    UP,
    DOWN
};

namespace gut
{
namespace sdl
{
    class Input
    {
        public:
            Input();
            virtual ~Input();

            void update(); // Fonction pour mettre à jour les entrées clavier et souris

            bool getTouche(const SDL_Scancode touche, enum ButtonACTION type = DOWN) const;

            bool getBoutonSouris(const Uint8 bouton, enum ButtonACTION type = DOWN) const;
            bool mouvementSouris() const; // Fonction pour savoir si la souris bouge ou pas

            int getX() const; // Fonction pour récupérer la position X de la souris sur l'écran
            int getY() const; // Fonction pour récupérer la position Y de la souris sur l'écran

            int getXRel() const; // Fonction pour récupérer le mouvement horizontal de la souris
            int getYRel() const; // Fonction pour récupérer le mouvement vertical de la souris

            Uint32 getWindowMouseMotion();

            void activateTextInput(bool activate);

            std::string getTextEntry();
            bool _isTyping = false;

            bool fin() const; // Fonction pour savoir si la croix de fermeture de la fenêtre est cliquée
            void end();


        private:
            SDL_Event evenements; // Évenements SDL
            bool _touchesDOWN[SDL_NUM_SCANCODES]; // Tableau où sont stockés les informations sur les touches enfoncées
            bool _boutonsSourisDOWN[8]; // Tableau où sont stockés les informations sur les touches relachées
            bool _touchesUP[SDL_NUM_SCANCODES]; // Tableau où sont stockés les informations sur les boutons de la souris enfoncés
            bool _boutonsSourisUP[8]; // Tableau où sont stockés les informations sur les boutons de la souris relachés

            Uint32 winMouseMotion = 0;

            std::string _text_input_string = " ";

            int _x; // Position en abscisse de la souris sur l'écran
            int _y; // Position en ordonnées de la souris sur l'écran
            int _xRel; // Mouvement horizontal de la souris
            int _yRel; // Mouvement vertical de la souris

            bool fini = false; // Variable a renvoyer si la croix de fermeture de la fenêtre est cliquée

            bool _isTextInputAllow = false;
    };
}
}

#endif // __cplusplus

#endif
