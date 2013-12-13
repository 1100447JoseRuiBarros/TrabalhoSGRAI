#pragma once

#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif
#include "mdlviewer.h"
#include "objecto_t.h"

class MODELO{

public:
	GLuint        texID[NUM_JANELAS][NUM_TEXTURAS];
	GLuint        labirinto[NUM_JANELAS];
	GLuint        chao[NUM_JANELAS];
	objecto_t	  objecto;
	GLuint        xMouse;
	GLuint        yMouse;
	StudioModel   stdModel[NUM_JANELAS];   // Modelo
	GLboolean     andarFrente;
	GLboolean     andarTras;
	GLboolean	  correr;
	GLuint        prev;
};
