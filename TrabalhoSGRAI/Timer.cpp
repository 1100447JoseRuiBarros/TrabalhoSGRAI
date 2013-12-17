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

#include "Globals.h"
#include "Window.h"

void Timer(int value)
{
	GLfloat nx=0,nz=0;
	float velocidade;

	if(estado.teclas.z && gordon.andar)
		gordon.correr=GL_TRUE;
	else
		gordon.correr=GL_FALSE;

	if(!estado.teclas.up && !estado.teclas.down){
		/*modelo.andarFrente=GL_FALSE;
		modelo.andarTras=GL_FALSE;
		modelo.correr=GL_FALSE;*/
		gordon.andar=GL_FALSE;
		if(gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=0)
			gordon.stdModel[JANELA_NAVIGATE].SetSequence(0);
	}

	GLuint curr = glutGet(GLUT_ELAPSED_TIME);
	// calcula velocidade baseado no tempo passado

	if(!gordon.correr)
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001;
	else
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001*2;


	glutTimerFunc(estado.timer, Timer, 0);
	gordon.prev = curr;


	if(estado.teclas.up){
		//Roda Objecto
		if(!gordon.andarFrente){
			gordon.objecto.dir+=M_PI;
			gordon.andarFrente=GL_TRUE;
		}
		// calcula nova posição nx,nz
		nx=gordon.objecto.pos.x+velocidade;
		//nz=modelo.objecto.pos.z-velocidade*sin(modelo.objecto.dir);

		//if(!detectaColisao(nx,nz)){

		gordon.objecto.pos.x=nx;
		//	//modelo.objecto.pos.z=nz;
		gordon.andar=GL_TRUE;
		//}
	}

	if(estado.teclas.down){
		//roda o objecto

		if(gordon.andarFrente){
			gordon.objecto.dir-=M_PI;
			gordon.andarFrente=GL_FALSE;
		}
		// calcula nova posição nx,nz
		nx=gordon.objecto.pos.x-velocidade;
		//nz=modelo.objecto.pos.z-velocidade*sin(modelo.objecto.dir);

		//if(!detectaColisao(nx,nz)){

		gordon.objecto.pos.x=nx;
		//	//dmodelo.objecto.pos.z=nz;
		gordon.andar=GL_TRUE;
		//}
	}


	if(estado.teclas.left){
		// rodar camara e objecto
	}
	if(estado.teclas.right){
		// rodar camara e objecto
	}

	if( gordon.andar && !gordon.correr && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=4)
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(4);

	//if(!modelo.andarFrente && !modelo.andarTras && !modelo.correr && modelo.stdModel[JANELA_NAVIGATE].GetSequence()!=0)
	//	modelo.stdModel[JANELA_NAVIGATE].SetSequence(0);

	if(gordon.correr && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=3)
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(3);

	// Sequencias - 0(parado) 3(andar) 20(choque)
	//  modelo.homer[JANELA_NAVIGATE].GetSequence()  le Sequencia usada pelo homer
	//  modelo.homer[JANELA_NAVIGATE].SetSequence()  muda Sequencia usada pelo homer

	redisplayAll();

}