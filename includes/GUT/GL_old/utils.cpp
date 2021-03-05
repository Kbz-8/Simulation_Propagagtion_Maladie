/*=============================================================*/
// Global Utility Toolkit
// GUT is a global extension for C++. It simplifies the development of 3D programs (especially with OpenGL).
// It can also be used in simple programs.
//
// utils.cpp
//
// AUTHOR: Malo DAVID
// CREATED: 13/11/2020
// UPDATED: 19/11/2020
/*=============================================================*/

#include "utils.hpp"

#ifdef __cplusplus

namespace gut
{
namespace gl2
{
    void Ortho(float width, float height)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, width, height, 0, -1.0, 10.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_CULL_FACE);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    void Perspec()
    {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glEnable(GL_CULL_FACE);
    }
}
}

#endif // __cplusplus
