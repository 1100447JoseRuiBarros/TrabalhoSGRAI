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
#include "Mouse.h"

void motionNavigateSubwindow(int x, int y)
{
	int dif;
	dif=y-modelo.yMouse;
	if(dif>0){//olhar para baixo
		estado.camera2.dir_lat-=dif*RAD(EYE_ROTACAO);
		if(estado.camera2.dir_lat<-RAD(45))
			estado.camera2.dir_lat=-RAD(45);
	}

	if(dif<0){//olhar para cima
		estado.camera2.dir_lat+=abs(dif)*RAD(EYE_ROTACAO);
		if(estado.camera2.dir_lat>RAD(45))
		  estado.camera2.dir_lat=RAD(45);
	}

	dif=x-modelo.xMouse;

	if(dif>0){ //olhar para a direita
		estado.camera2.dir_long-=dif*RAD(EYE_ROTACAO);
		if(estado.camera2.dir_long<modelo.objecto.dir-RAD(45))
			estado.camera2.dir_long=modelo.objecto.dir-RAD(45);
	}
	if(dif<0){//olhar para a esquerda
		estado.camera2.dir_long+=abs(dif)*RAD(EYE_ROTACAO);
		if(estado.camera2.dir_long>modelo.objecto.dir+RAD(45))
		estado.camera2.dir_long=modelo.objecto.dir+RAD(45);
	}
	modelo.xMouse=x;
	modelo.yMouse=y;
}

void mouseNavigateSubwindow(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
		  modelo.xMouse=x;
		  modelo.yMouse=y;
		  glutMotionFunc(motionNavigateSubwindow);
		}
		else
		  glutMotionFunc(NULL);
	}
}