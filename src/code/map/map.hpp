#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include "../../../includes/GUT/GUT.hpp"
#include "../person/person.hpp"

class Map
{
    public:
        Map(int width, int height); // Constructeur de la classe

        void restart();

        void clearTabular(); // Fonction pour nettoyer le tableau principal

        void renderPopulation(bool pause); // Fonction pour afficher la population à l'écran

        virtual ~Map(); // Destructeur de la classe

        std::vector<std::vector<Person>> _TableauPersonnes; // Tableau principal où sont stockés les gens

        int _sicks;
        double _mortality;
        double _contagiousness;
        double _vaccinated_chance;
        int _time_before_death;
        int _time_before_cure;

        int _daysPassed;
        int _sicksNumber;
        int _vaccinatedNumber;
        int _deadNumber;
        int _healthyNumber;

        GLuint _vboID; // VBO

    private:
        int _width;
        int _height;

        void LoadVBO(); // Fonction pour générer un VBO
        void updateColor(int x, int y); // Fonction pour mettre à jour la couleur de la population

        void renderPerson(int x, int y); // Fonction pour rendre une personne seule

        void updateMap();

        void updateSick(int x, int y);
        void updateNewSick();
        void updateHealthy(int x, int y);

        Person getPerson(int x, int y); // Fonction pour récupérer les caractéristiques d'une personne
        void setPerson(int x, int y, enum TYPE SET);  // Fonction pour modifier manuellement la caractéristiques d'une personne

        std::vector<float> _vertices; // Tableau contenant les coordonnées des sommets d'un carré pour le VBO
};

#endif // MAP_HPP
