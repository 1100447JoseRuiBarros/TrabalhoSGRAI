#pragma once
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include "GL/glaux.h"
#endif

GLboolean detectaColisao(GLfloat nx,GLfloat ny);