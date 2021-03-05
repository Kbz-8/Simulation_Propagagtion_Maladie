#ifndef PERSON_HPP
#define PERSON_HPP

#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "../../../includes/GUT/GUT.hpp"

#define NULLPERSON Person()

enum TYPE
{
    HEALTHY,
    VACCINATED,
    SICK,
    DEAD,
    NONE
};

struct Person
{
    Person(double vaccinated_chance, double mortality);
    Person();
    ~Person();

    enum TYPE _type; // Type de personne
    bool _firstDaySick; // Si la personne vient de tomber malade
    int _daysSick; // Nombre de jours de maladie
    bool _resistant; // Si la personne est résistante à la maladie (elle peut l'attrapper mais n'en mourra pas)
};

#endif // PERSON_HPP
