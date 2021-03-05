/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// shader.hpp
//
// AUTHOR: Malo DAVID
// CREATED: 04/11/2020
// UPDATED: 21/11/2020
/*=============================================================*/

#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#ifdef __cplusplus

#include <iostream>
#include <string>

// Include OpenGL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../SDL2/messagebox/messagebox.hpp"
#include "../../math/math.hpp"

namespace gut
{
namespace gl3
{
    class Shader
    {
        public:
            Shader(const char* vertexFile, const char* fragmentFile); // Constructeur

            void bindShader(); // Fonction pour vérouiller le shader
            void unbindShader(); // Fonction pour dévérouiller le shader
            bool isBinded();

            // Fonctions pour modifier des variables dans le shader
            void setFloat(const std::string &name, float v);
            void setInt(const std::string &name, int v);
            void setBool(const std::string &name, bool v);
            void setVec3(const std::string &name, math::Vec3 v);
            void setVec2(const std::string &name, math::Vec2 v);
            void setVec4(const std::string &name, math::Vec4 v);
            void setVec3(const std::string &name, int x, int y, int z);
            void setVec2(const std::string &name, int x, int y);
            void setVec4(const std::string &name, int x, int y, int z, int t);
            void setMat4(const std::string &name, glm::mat4 matrix);

            virtual ~Shader(); // Destructeur virtuel car héritée par la classe Application

            GLuint program; // Programme du shader

        private:
            char* LoadSourceShader(const char* filename); // Fonction pour charger la source d'un shader
            void creatShader(const char* source, int type); // Fonction pour créer un shader

            int shader; // Shader

            const char* _filename;
    };
}
}

#endif // __cplusplus

#endif //__SHADER_HPP__
