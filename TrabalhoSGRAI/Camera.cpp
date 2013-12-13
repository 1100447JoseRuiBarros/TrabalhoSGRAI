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

#include "Camera.h"
#include "defines.h"
#include "mathlib.h"
#include "Globals.h"

void desenhaAngVisao(camera_t *cam)
{
	GLfloat ratio;
	ratio=(GLfloat)glutGet(GLUT_WINDOW_WIDTH)/glutGet(GLUT_WINDOW_HEIGHT); // proporção 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	glPushMatrix();
	glTranslatef(cam->eye.x,OBJECTO_ALTURA,cam->eye.z);
	glColor4f(0,0,1,0.2);
	glRotatef(GRAUS(cam->dir_long),0,1,0);

	glBegin(GL_TRIANGLES);
	glVertex3f(0,0,0);
	glVertex3f(5*cos(RAD(cam->fov*ratio*0.5)),0,-5*sin(RAD(cam->fov*ratio*0.5)));
	glVertex3f(5*cos(RAD(cam->fov*ratio*0.5)),0,5*sin(RAD(cam->fov*ratio*0.5)));
	glEnd();
	glPopMatrix();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void setNavigateSubwindowCamera(camera_t *cam, objecto_t obj)
{

	pos_t center;
	/*
	if(estado.vista[JANELA_NAVIGATE])
	{
	*/
	cam->eye.x=obj.pos.x-1;
	cam->eye.y=obj.pos.y+.2;
	cam->eye.z=obj.pos.z-1;
	center.x=obj.pos.x;
	center.y=obj.pos.y+.2;
	center.z=obj.pos.z;
	/*
	}
	else
	{

	}
	*/
	gluLookAt(cam->eye.x,cam->eye.y,cam->eye.z,center.x,center.y,center.z,0,1,0);
}


/////////////////////////////////////
//topSubwindow
void setTopSubwindowCamera( camera_t *cam,objecto_t obj)
{
	cam->eye.x=obj.pos.x;
	cam->eye.z=obj.pos.z;
	if(estado.vista[JANELA_TOP])
		gluLookAt(obj.pos.x,CHAO_DIMENSAO*.2,obj.pos.z,obj.pos.x,obj.pos.y,obj.pos.z,0,0,-1);
	else
		gluLookAt(obj.pos.x,CHAO_DIMENSAO*2,obj.pos.z,obj.pos.x,obj.pos.y,obj.pos.z,0,0,-1);
}
