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

#include "Key.h"
#include "Globals.h"
#include "Window.h"

void Key(unsigned char key, int x, int y)
{

	switch (key) {
	case 27:
		exit(1);
		break;
	case 'w':
	case 'W':
		glutSetWindow(estado.navigateSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		glutSetWindow(estado.topSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		break;
	case 'f':
	case 'F':
		glutSetWindow(estado.navigateSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_TEXTURE_2D);
		glutSetWindow(estado.topSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_TEXTURE_2D);
		break;
	case 'c':
	case 'C':
		glutSetWindow(estado.navigateSubwindow);
		glEnable(GL_TEXTURE_2D);
		glutSetWindow(estado.topSubwindow);
		glEnable(GL_TEXTURE_2D);
		break;
	case 'r':
	case 'R':
		restart();
		break;
	}
}

void KeyUp(unsigned char key, int x, int y)
{

}

void SpecialKey(int key, int x, int y)
{
	switch (key) {
		
	case GLUT_KEY_UP: estado.teclas.up =GL_TRUE;
		break;
	case GLUT_KEY_DOWN: estado.teclas.down =GL_TRUE;
		break;
	case GLUT_KEY_LEFT: estado.teclas.left =GL_TRUE;
		break;
	case GLUT_KEY_RIGHT: estado.teclas.right =GL_TRUE;
		break;
	case GLUT_KEY_F1: estado.vista[JANELA_TOP]=!estado.vista[JANELA_TOP];
		break;
	case GLUT_KEY_F2: estado.vista[JANELA_NAVIGATE]=!estado.vista[JANELA_NAVIGATE];
		break;
	case GLUT_KEY_F3: estado.teclas.z=GL_TRUE;
		break;
	case GLUT_KEY_F4: estado.teclas.x=GL_TRUE;
		break;
	}

}
// Callback para interaccao via teclas especiais (largar na tecla)
void SpecialKeyUp(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: estado.teclas.up =GL_FALSE;
		break;
	case GLUT_KEY_DOWN: estado.teclas.down =GL_FALSE;
		break;
	case GLUT_KEY_LEFT: estado.teclas.left =GL_FALSE;
		break;
	case GLUT_KEY_RIGHT: estado.teclas.right =GL_FALSE;
		break;
	case GLUT_KEY_F3: estado.teclas.z=GL_FALSE;
		break;
	case GLUT_KEY_F4: estado.teclas.x=GL_FALSE;
		break;
	}
}