/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// utils.hpp
//
// Use these functions with glm
//
// AUTHOR: Malo DAVID
// CREATED: 13/11/2020
// UPDATED: 04/12/2020
/*=============================================================*/

#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef __cplusplus

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "text/text.hpp"
#include "shader/shader.hpp"
#include "getPixelColor/getpixelcolor.hpp"
#include "button/button.hpp"

#include <vector>
#include <string>

#define GUT_PROJECTION_MATRIX 1
#define GUT_MODEL_MATRIX 2
#define GUT_VIEW_MATRIX 3

namespace gut
{
namespace gl3
{
    void perspective(float FOV, float aspect, float near, float far);

    void MatrixMode(int type);
    glm::mat4 getMatrix(int type);
    glm::mat4 getCurrentMatrix();

    void lookAt(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z);

    void LoadIdentity();

    void Translate3D(double x, double y, double z);
    void color4f(float r, float g, float b, float a, int verticesNumber);
};
}

#endif // __cplusplus
#endif // UTILS_HPP
