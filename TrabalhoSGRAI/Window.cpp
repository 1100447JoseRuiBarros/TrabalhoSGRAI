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

#include "Window.h"
#include "Globals.h"
#include "Camera.h"
#include "Illumination.h"


///////////////////////////////////
//// Redisplays

void redisplayTopSubwindow(int width, int height)
{
	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL
	glViewport(0, 0, (GLint) width, (GLint) height);
	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(60,(GLfloat)width/height,.5,100);
	// Matriz Modelview
	// Matriz onde são realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);

}


void reshapeNavigateSubwindow(int width, int height)
{
	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL
	glViewport(0, 0, (GLint) width, (GLint) height);
	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(estado.camera.fov,(GLfloat)width/height,0.1,50);
	// Matriz Modelview
	// Matriz onde são realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
}


void reshapeMainWindow(int width, int height)
{
	GLint w,h;
	w = (width-GAP*3)*.5;
	h = (height-GAP*2);    
	glutSetWindow(estado.topSubwindow);
	glutPositionWindow(GAP, GAP);
	glutReshapeWindow(w, h);
	glutSetWindow(estado.navigateSubwindow);
	glutPositionWindow(GAP+w+GAP, GAP);
	glutReshapeWindow(w, h);

}

void displayNavigateSubwindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setNavigateSubwindowCamera(&estado.camera, gordon.objecto);
	setLight();

	glCallList(modelo.labirinto[JANELA_NAVIGATE]);
	glCallList(modelo.chao[JANELA_NAVIGATE]);

	if(!estado.vista[JANELA_NAVIGATE])
	{
		glPushMatrix();
		glTranslatef(gordon.objecto.pos.x,gordon.objecto.pos.y,gordon.objecto.pos.z);
		glRotatef(GRAUS(gordon.objecto.dir),0,1,0);
		glRotatef(-90,1,0,0);
		glScalef(SCALE_HOMER,SCALE_HOMER,SCALE_HOMER);
		mdlviewer_display(gordon.stdModel[JANELA_NAVIGATE]);
		glPopMatrix();

		GLint x=2;

		for(int i=0;i<3;i++){

			glPushMatrix();
			glTranslatef(x+i,0,0);
			//glRotatef(GRAUS(gordon.objecto.dir),0,1,0);
			glRotatef(-90,1,0,0);
			glScalef(SCALE_HOMER,SCALE_HOMER,SCALE_HOMER);
			mdlviewer_display(headCrabs[i].stdModel[JANELA_NAVIGATE]);
			glPopMatrix();
		}
	}

	glutSwapBuffers();
}

void displayTopSubwindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	setTopSubwindowCamera(&estado.camera,gordon.objecto);
	setLight();

	glCallList(modelo.labirinto[JANELA_TOP]);
	glCallList(modelo.chao[JANELA_TOP]);

	glPushMatrix();		
	glTranslatef(gordon.objecto.pos.x,gordon.objecto.pos.y,gordon.objecto.pos.z);
	glRotatef(GRAUS(gordon.objecto.dir),0,1,0);
	glRotatef(-90,1,0,0);
	glScalef(SCALE_HOMER,SCALE_HOMER,SCALE_HOMER);
	mdlviewer_display(gordon.stdModel[JANELA_TOP]);
	glPopMatrix();

	GLint x=2;

		for(int i=0;i<3;i++){

			glPushMatrix();
			glTranslatef(x+i,0,0);
			//glRotatef(GRAUS(gordon.objecto.dir),0,1,0);
			glRotatef(-90,1,0,0);
			glScalef(SCALE_HOMER,SCALE_HOMER,SCALE_HOMER);
			mdlviewer_display(headCrabs[i].stdModel[JANELA_TOP]);
			glPopMatrix();
		}

	desenhaAngVisao(&estado.camera);
	glutSwapBuffers();
}

/////////////////////////////////////
//mainWindow

void redisplayAll(void)
{
	glutSetWindow(estado.mainWindow);
	glutPostRedisplay();
	glutSetWindow(estado.topSubwindow);
	glutPostRedisplay();
	glutSetWindow(estado.navigateSubwindow);
	glutPostRedisplay();
}

void displayMainWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glutSwapBuffers();
}