#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif
#include "mdlviewer.h"
#include "objecto_t.h"
#include "defines.h"

class Model{

public:
	
	objecto_t	  objecto;
	StudioModel   stdModel[NUM_JANELAS];   // Modelo
	GLboolean     andarFrente;
	GLboolean     andar;
	GLboolean	  correr;
	GLuint        prev;
	
	Model();
	~Model();
};