#pragma once
#include <stdio.h>
#include <stdlib.h>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include "GL/glaux.h"
#endif


#include "defines.h"
#include "Globals.h"
#include "Key.h"
#include "Window.h"
#include "Illumination.h"
#include "Timer.h"
#include "Init.h"
#include "Texturas.h"
#include "Mapa.h"
#include "Mouse.h"

#pragma comment (lib, "glaux.lib")    /* link with Win32 GLAUX lib usada para ler bitmaps */

// função para ler jpegs do ficheiro readjpeg.c
extern "C" int read_JPEG_file(const char *, char **, int *, int *, int *);

/*
void strokeCenterString(char *str,double x, double y, double z, double s)
{
	int i,n;

	n = strlen(str);
	glPushMatrix();
	glTranslated(x-glutStrokeLength(GLUT_STROKE_ROMAN,(const unsigned char*)str)*0.5*s,y-119.05*0.5*s,z);
	glScaled(s,s,s);
	for(i=0;i<n;i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,(int)str[i]);
	glPopMatrix();

}
*/

void imprime_ajuda(void)
{
	printf("\n\n			Super Gordon Freeman \n\n");
	printf("******* Diversos ******* \n");
	printf("w,W - Wireframe \n");
	printf("f,F - Fill \n");
	printf("c,C - Color \n");
	printf("r,R - Restart \n");
	printf("ESC - Sair\n");
	printf("******* Movimento ******* \n");
	printf("righ- Andar para a frente \n");
	printf("left- Andar para tras \n");
	printf("F3 - Correr \n");
	printf("F4 - Saltar \n");
	printf("******* Camara ******* \n");
	printf("left mouse - Permite mover a camara com o movimento do rato \n");
}

////////////////////////////////////
// InicializaÁıes

void createDisplayLists(int janelaID)
{
	modelo.labirinto[janelaID]=glGenLists(2);
	glNewList(modelo.labirinto[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT );
	glPopAttrib();
	glEndList();

	modelo.chao[janelaID]=modelo.labirinto[janelaID]+1;
	glNewList(modelo.chao[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT );
	constroicena(janelaID);
	glPopAttrib();
	glEndList();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(900+GAP*3, 500+GAP*2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if ((estado.mainWindow=glutCreateWindow("Super Gordon Freeman")) == GL_FALSE)
		exit(1);

	imprime_ajuda();

	// Registar callbacks do GLUT da janela principal
	init();
	glutReshapeFunc(reshapeMainWindow);
	glutDisplayFunc(displayMainWindow);

	glutTimerFunc(estado.timer,Timer,0);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	// criar a sub window topSubwindow
	estado.topSubwindow=glutCreateSubWindow(estado.mainWindow, GAP, GAP, 400, 400);
	init();
	setLight();
	setMaterial();
	createTexturesSkybox();
	createTextures(modelo.texID[JANELA_TOP]);
	createDisplayLists(JANELA_TOP);

	mdlviewer_init("gordon.mdl", gordon.stdModel[JANELA_TOP] );

	for(int i=0;i<3;i++)
		mdlviewer_init("headcrab.mdl", headCrabs[i].stdModel[JANELA_TOP] );

	glutReshapeFunc(redisplayTopSubwindow);
	glutDisplayFunc(displayTopSubwindow);

	glutTimerFunc(estado.timer,Timer,0);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);


	// criar a sub window navigateSubwindow
	estado.navigateSubwindow=glutCreateSubWindow(estado.mainWindow, 400+GAP, GAP, 400, 800);
	init();
	setLight();
	setMaterial();
	createTexturesSkybox();

	createTextures(modelo.texID[JANELA_NAVIGATE]);
	createDisplayLists(JANELA_NAVIGATE);
	mdlviewer_init("gordon.mdl", gordon.stdModel[JANELA_NAVIGATE] );

	for(int i=0;i<3;i++)
		mdlviewer_init("headcrab.mdl", headCrabs[i].stdModel[JANELA_NAVIGATE] );

	glutReshapeFunc(reshapeNavigateSubwindow);
	glutDisplayFunc(displayNavigateSubwindow);
	glutMouseFunc(mouseNavigateSubwindow);

	glutTimerFunc(estado.timer,Timer,0);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);

	alutInit (&argc, argv);
	estado.buffer[0] = alutCreateBufferFromFile("mario.wav");
	estado.buffer[1] = alutCreateBufferFromFile("jump.wav");
	alGenSources(4, estado.source);
	alSourcei(estado.source[0], AL_BUFFER, estado.buffer[0]);
	alSourcei(estado.source[1], AL_BUFFER, estado.buffer[1]);
	alSourcePlay(estado.source[0]);

	glutMainLoop();
	return 0;

}