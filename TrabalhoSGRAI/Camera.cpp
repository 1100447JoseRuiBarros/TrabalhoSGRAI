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
/*
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
*/
//janela direita
void setNavigateSubwindowCamera(camera_t *cam, objecto_t obj)
{

	pos_t center;
	/*
	if(estado.vista[JANELA_NAVIGATE])
	{
	*/
	if(gordon.andarFrente)
		cam->eye.x=obj.pos.x+0.25;
	else
		cam->eye.x=obj.pos.x-0.25;
	cam->eye.y=obj.pos.y+(OBJECTO_ALTURA+OBJECTO_ALTURA/4);
	cam->eye.z=obj.pos.z;
	if(gordon.andarFrente)
	{
		center.x=obj.pos.x+cos(cam->dir_long)*cos(cam->dir_lat);
		center.y=cam->eye.y+sin(cam->dir_lat);
		center.z=obj.pos.z+sin(-cam->dir_long)*cos(cam->dir_lat);
	}
	else
	{
		center.x=obj.pos.x-cos(cam->dir_long)*cos(cam->dir_lat);
		center.y=cam->eye.y+sin(cam->dir_lat);
		center.z=obj.pos.z-sin(-cam->dir_long)*cos(cam->dir_lat);
	}
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
//janela esquerda
void setTopSubwindowCamera( camera_t *cam,objecto_t obj)
{
	pos_t center;

	cam->eye.x=obj.pos.x;
	cam->eye.y=2;
	cam->eye.z=obj.pos.z+6;
	center.x=obj.pos.x;
	center.y=2;
	center.z=obj.pos.z;
	//if(estado.vista[JANELA_TOP])
	gluLookAt(cam->eye.x,cam->eye.y,cam->eye.z,center.x,center.y,center.z,0,1,0);
	//else
	//gluLookAt(obj.pos.x,CHAO_DIMENSAO*2,obj.pos.z,obj.pos.x,obj.pos.y,obj.pos.z,0,0,-1);
}
