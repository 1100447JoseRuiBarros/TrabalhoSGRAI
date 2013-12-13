#pragma once
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include "GL/glaux.h"
#endif

#include "Illumination.h"
#include "Globals.h"

////////////////////////////////////
/// Iluminação e materiais

void setLight()
{	
	GLfloat light_pos[4] =	{-5.0, 20.0, -8.0, 0.0};
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[]=	{ 0.5f, 0.5f, 0.5f, 1.0f };

	// ligar iluminação
	glEnable(GL_LIGHTING);

	// ligar e definir fonte de luz 0
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,estado.localViewer);
}

void setMaterial()
{
	GLfloat mat_specular[]= { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_shininess = 104;

	// criação automática das componentes Ambiente e Difusa do material a partir das cores
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// definir de outros parâmetros dos materiais estáticamente
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess); 
}