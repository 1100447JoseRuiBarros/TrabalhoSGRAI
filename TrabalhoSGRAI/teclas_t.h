#pragma once

#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif


class teclas_t
{
public:
	GLboolean   up,down,left,right;
};