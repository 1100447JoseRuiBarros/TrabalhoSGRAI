#pragma once
#include <stdlib.h>

#include "ESTADO.h"
#include "MODELO.h"
#include "Globals.h"
#include "Model.h"

/////////////////////////////////////
//variaveis globais

ESTADO estado;
MODELO modelo;
Model gordon;
Model headCrabs[3];

void desenhaBoundingBox(){

	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(gordon.objecto.pos.x,gordon.objecto.pos.y,gordon.objecto.pos.z);
	glScalef(1,4,1);
	glColor3f(10,0.0,0.0); 
	glutSolidSphere(0.05,20,20);
	glPopMatrix();
}