#include <GL/glut.h>
#ifdef _WIN32
#include "GL/glaux.h"
#endif
#include "camera_t.h"
#include "teclas_t.h"
#include "defines.h"
#include "objecto_t.h"
#include "studio.h"
#include "mdlviewer.h"

typedef struct MODELO{
	GLuint        texID[NUM_JANELAS][NUM_TEXTURAS];
	GLuint        labirinto[NUM_JANELAS];
	GLuint        chao[NUM_JANELAS];
	objecto_t	  objecto;
	GLuint        xMouse;
	GLuint        yMouse;
	StudioModel   homer[NUM_JANELAS];   // Modelo Homer
	GLboolean     andar;
	GLuint        prev;
};
