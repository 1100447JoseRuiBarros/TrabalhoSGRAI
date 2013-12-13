#pragma once

#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif
#include "pos_t.h"

class objecto_t{
public:
	pos_t    pos;  
	GLfloat  dir; 
	GLfloat  vel; 
};