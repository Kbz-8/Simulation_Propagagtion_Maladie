/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// shader.hpp
//
// AUTHOR: DAVID Malo
// CREATED: 04/11/2020
// UPDATED: 04/11/2020
/*=============================================================*/

#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <iostream>
#include <string>

// Include OpenGL
#include <GL/glew.h>

#include <SDL2/SDL.h>

class Shader
{
    public:
        Shader(const char* vertexFile, const char* fragmentFile); // Constructeur

        void bindShader(); // Fonction pour vérouiller le shader
        void unbindShader(); // Fonction pour dévérouiller le shader

        // Fonction pour modifier des variables dans le shader
        void setBool(const std::string &name, bool v);

        virtual ~Shader(); // Destructeur virtuel car héritée par la classe Application

        GLuint program; // Programme du shader

    private:
        char* LoadSourceShader(const char* filename); // Fonction pour charger la source d'un shader
        void creatShader(const char* source, int type); // Fonction pour créer un shader

        int shader; // Shader
};

#endif //__SHADER_HPP__
