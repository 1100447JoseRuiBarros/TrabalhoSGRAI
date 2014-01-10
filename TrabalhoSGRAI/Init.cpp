#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include "GL/glaux.h"
#endif

#include "init.h"
#include "Globals.h"
#include "Window.h"
#include "Mapa.h"

void init()
{
	GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };

	estado.timer=100;	

	/*estado.camera.eye.x=0;
	estado.camera.eye.y=OBJECTO_ALTURA*2;
	estado.camera.eye.z=0;*/
	estado.camera1.fov=60;
	estado.camera2.fov=60;
	estado.camera2.dir_long=0;
	estado.camera2.dir_lat=0;

	estado.localViewer=1;
	estado.vista[JANELA_TOP]=0;
	estado.vista[JANELA_NAVIGATE]=0;

	gordon.objecto.pos.x=0;
	//gordon.objecto.pos.y=OBJECTO_ALTURA;
	gordon.objecto.pos.y=0;
	gordon.objecto.pos.z=0;
	gordon.objecto.dir=0;
	gordon.objecto.vel=OBJECTO_VELOCIDADE;
	gordon.andarFrente=GL_TRUE;
	gordon.saltar=GL_FALSE;

	//CRABS
	std::vector<int> posicoes;
	posicoes = posicoesCrabs();
	int i=0;

	for(std::vector<int>::iterator it = posicoes.begin();
		it != posicoes.end();it++)
	{
		headCrabs[i].objecto.pos.x= *it;
		headCrabs[i].objecto.pos.y=-0.5;
		headCrabs[i].objecto.pos.z=0;
		headCrabs[i].objecto.dir=M_PI;
		headCrabs[i].objecto.vel=OBJECTO_VELOCIDADE;
		headCrabs[i].andarFrente=GL_FALSE;
		headCrabs[i].saltar=GL_FALSE;
		i++;
	}

	modelo.xMouse=modelo.yMouse=-1;

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);  // por causa do Scale ao Homer

	if(glutGetWindow()==estado.mainWindow)
		glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	else
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
	
}