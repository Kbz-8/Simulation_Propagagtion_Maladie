#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <iostream>
#include <string>

// Include OpenGL
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include "../../../includes/GUT/GUT.hpp"

class Shader
{
    public:
        Shader(GUTtext vertexFile, GUTtext fragmentFile); // Constructeur

        void bindShader(); // Fonction pour vérouiller le shader
        void unbindShader(); // Fonction pour dévérouiller le shader

        // Fonction pour modifier des variables dans le shader
        void setBool(const std::string &name, bool v);

        virtual ~Shader(); // Destructeur virtuel car héritée par la classe Application

        GLuint program; // Programme du shader

    private:
        char* LoadSourceShader(GUTtext filename); // Fonction pour charger la source d'un shader
        void creatShader(GUTtext source, int type); // Fonction pour créer un shader

        int shader; // Shader
};

#endif //__SHADER_HPP__
