#pragma once

#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif
#include "camera_t.h"
#include "teclas_t.h"
#include "defines.h"
//#include "AL/alMain.h"

class ESTADO{

public:
	camera_t      camera1;
	camera_t      camera2;
	GLint         timer;
	GLint         mainWindow,topSubwindow,navigateSubwindow;
	teclas_t      teclas;
	GLboolean     localViewer;
	GLuint        vista[NUM_JANELAS];
	//ALuint        buffer[9], source[3];
};