#pragma once

#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif
#include "camera_t.h"
#include "teclas_t.h"
#include "defines.h"

class ESTADO{

public:
	camera_t      camera;
	GLint         timer;
	GLint         mainWindow,topSubwindow,navigateSubwindow;
	teclas_t      teclas;
	GLboolean     localViewer;
	GLuint        vista[NUM_JANELAS];
};