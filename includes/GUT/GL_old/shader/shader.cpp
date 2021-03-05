/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// shader.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 04/11/2020
// UPDATED: 21/11/2020
/*=============================================================*/

#ifdef __cplusplus

#include "shader.hpp"

namespace gut
{
namespace gl2
{
    Shader::Shader(const char* vertexFile, const char* fragmentFile)
    {
        /* ======================== DOCUMENTATION ========================
         * Un shader un est programme exécuté dans la carte vidéo pour modifier
         * l'image avant de la rendre à l'écran.
         *
         * En GLSL (OpenGL Shader Language), il existe deux types de shaders :
         * - Les vertex shaders qui sont les shaders permettant de récuperer
         *   les informations d'OpenGL (couleur vérouillée, position du vertex,
         *   les matrices, les coordonnées des textures, ...)
         *   et de les transmettre à l'autre type de shaders.
         * - Les fragment shaders qui sont les shaders qui modifient l'image.
         */

        program = glCreateProgram(); // On créer le programme d'un shader

        if(!program) // Si il n'y a pas de programme on envoie un message d'erreur
            sdl::MessageBox::reportMessage(ERROR, "Impossible de créer le programme d'un shader", SDL_GetError());

        creatShader(LoadSourceShader(vertexFile), GL_VERTEX_SHADER); // Création du vertex shader
        creatShader(LoadSourceShader(fragmentFile), GL_FRAGMENT_SHADER); // Création du fragment shader

        glLinkProgram(program); // Lien vers le programme du shader
        glValidateProgram(program); // Valide le programme du shader
    }

    void Shader::bindShader()
    {
        glUseProgram(program); // Utilise le shader
    }

    void Shader::unbindShader()
    {
        glUseProgram(0); // N'utilise plus aucun shaders
    }


    bool Shader::isBinded()
    {
        int current;
        glGetIntegerv(GL_CURRENT_PROGRAM, &current);
        if(current == program)
            return true;
        return false;
    }

    /* ========================= Fonctions pour modifier des variables du shader ========================= */
    void Shader::setFloat(const std::string &name, float v)
    {
        glUniform1f(glGetUniformLocation(program, name.c_str()), v);
    }

    void Shader::setVec3(const std::string &name, math::Vec3 v)
    {
        glUniform3f(glGetUniformLocation(program, name.c_str()), v.X, v.Y, v.Z);
    }

    void Shader::setVec2(const std::string &name, math::Vec2 v)
    {
        glUniform2f(glGetUniformLocation(program, name.c_str()), v.X, v.Y);
    }

    void Shader::setVec3(const std::string &name, int x, int y, int z)
    {
        glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
    }

    void Shader::setVec2(const std::string &name, int x, int y)
    {
        glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
    }

    void Shader::setInt(const std::string &name, int v)
    {
        glUniform1f(glGetUniformLocation(program, name.c_str()), v);
    }

    void Shader::setBool(const std::string &name, bool v)
    {
        glUniform1f(glGetUniformLocation(program, name.c_str()), v);
    }

    void Shader::setVec4(const std::string &name, math::Vec4 v)
    {
        glUniform4f(glGetUniformLocation(program, name.c_str()), v.X, v.Y, v.Z, v.W);
    }

    void Shader::setVec4(const std::string &name, int x, int y, int z, int t)
    {
        glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, t);
    }


    char* Shader::LoadSourceShader(const char* filename)
    {
        char *src = NULL;   // Code source de notre shader
        FILE *fp = NULL;    // Fichier
        long long SIZE;     // Taille du fichier
        long i;             // Compteur
        _filename = filename;


        fp = fopen(filename, "r"); // On ouvre le fichier
        if(fp == NULL) // Si le fichier ne s'est pas ouvert on envoie un message d'erreur et on renvoie NULL
        {
            sdl::MessageBox::reportMessage(ERROR, "Impossible d'ouvrir un code de shader", SDL_GetError());
            return NULL;
        }


        // On récupère la longueur du fichier
        fseek(fp, 0, SEEK_END);
        SIZE = ftell(fp);


        // On se replace au début du fichier
        rewind(fp);

        // On alloue de la mémoire pour y placer notre code source
        src = new char[SIZE + 1]; // +1 pour le caractère de fin de chaine '\0'
        if(src == NULL) // Si l'allocation dynamique de mémoire se passe mal on envoie un message d'erreur, on ferme le fichier et on renvoie NULL
        {
            fclose(fp);
            sdl::MessageBox::reportMessage(ERROR, "Erreur d'allocation memoire pour un shaders", SDL_GetError());
            return NULL;
        }


        // Lecture du code source
        for(i = 0; i < SIZE; i++)
            src[i] = fgetc(fp);

        src[SIZE] = '\0'; // On place le dernier caractère à '\0'

        fclose(fp); // Fermeture du fichier
        std::cout << filename << " : ";
        return src;
    }

    void Shader::creatShader(const char* source, int type)
    {
        shader = glCreateShader(type); // Création du shader

        if(!shader) // Si le shader ne s'est pas créé, on envoie un message d'erreur
            sdl::MessageBox::reportMessage(ERROR, "Impossible de créer un shader", SDL_GetError());

        glShaderSource(shader, 1, &source, NULL); // On récupère le code source du shader
        glCompileShader(shader); // On compile le sahder

        GLint shader_compiled = GL_TRUE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled); // On vérifie que le shader s'est bien compilé

        if(shader_compiled == GL_FALSE) // Si le shader ne s'est pas complié correctement
        {
            GLsizei logsize = 0;
            char *log = NULL;

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize); // On récupère la taille du message d'erreur

            // On alloue un espace mémoire dans lequel OpenGL écrira le message
            log = new char[logsize + 1];
            if(!log) // Si cet espace mémoire n'est pas alloué, on envoie un message d'erreur
                sdl::MessageBox::reportMessage(ERROR, "Erreur d'allocation memoire pour une erreur de shader (log)", SDL_GetError());

            memset(log, '\0', logsize + 1); // Initialisation du contenu

            glGetShaderInfoLog(shader, logsize, &logsize, log); // Récupération des informations du shader

            std::cout << log << std::endl;

            std::string _error = "Erreur de compilation d'un shader : ";
            _error.append(_filename);

            sdl::MessageBox::reportMessage(ERROR, _error, log);

            // Libération de la mémoire et du shader
            delete log;
            glDeleteShader(shader);

            return;
        }

        if(type == 35633 && shader)
            std::cout << "vertex shader créé avec succès" << std::endl;
        if(type == 35632 && shader)
            std::cout << "fragment shader créé avec succès" << std::endl << std::endl;

        glAttachShader(program, shader); // On attache le shader à son programme
    }

    Shader::~Shader()
    {
        if(shader) // S'il y a un shader créé, on le libère
            glDeleteShader(shader);
        if(program) // S'il y a un programme créé, on le libère
            glDeleteProgram(program);

        unbindShader(); // On dévérouille tous les shaders

        std::cout << "Shader libéré" << std::endl;
    }
}
}

#endif // __cplusplus
