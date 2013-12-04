#pragma once

#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif
#include "pos_t.h"

class camera_t{
public:
	pos_t    eye;  
	GLfloat  dir_long;  // longitude olhar (esq-dir)
	GLfloat  dir_lat;   // latitude olhar	(cima-baixo)
	GLfloat  fov;
};