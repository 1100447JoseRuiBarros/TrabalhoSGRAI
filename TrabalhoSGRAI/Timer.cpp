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

#include "Globals.h"
#include "Window.h"
#include "Colisao.h"
#include <AL/alut.h>

void Timer(int value)
{
	GLfloat nx=0,nz=0;
	float velocidade;

	GLuint curr = glutGet(GLUT_ELAPSED_TIME);
	// calcula velocidade baseado no tempo passado

	if(!gordon.correr)
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001;
	else
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001*2;

	glutTimerFunc(estado.timer, Timer, 0);
	gordon.prev = curr;

	if(!gordon.saltar){

		if(estado.teclas.z && gordon.andar)
			gordon.correr=GL_TRUE;
		else
			gordon.correr=GL_FALSE;

		if(!estado.teclas.right && !estado.teclas.left){
			gordon.andar=GL_FALSE;
			if(gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=0)
				gordon.stdModel[JANELA_NAVIGATE].SetSequence(0);
		}

		if(estado.teclas.right){
			//Roda Objecto
			if(!gordon.andarFrente){
				gordon.objecto.dir+=M_PI;
				gordon.andarFrente=GL_TRUE;
			}
			// calcula nova posição nx,nz
			nx=gordon.objecto.pos.x+velocidade;
			//nz=modelo.objecto.pos.z-velocidade*sin(modelo.objecto.dir);

			if(!detectaColisao(nx,nz)){

				gordon.objecto.pos.x=nx;
				gordon.andar=GL_TRUE;
			}
		}

		if(estado.teclas.left){
			//roda o objecto

			if(gordon.andarFrente){
				gordon.objecto.dir-=M_PI;
				gordon.andarFrente=GL_FALSE;
			}
			// calcula nova posição nx,nz
			nx=gordon.objecto.pos.x-velocidade;

			if(!detectaColisao(nx,nz)){

				gordon.objecto.pos.x=nx;
				gordon.andar=GL_TRUE;
			}
		}

		if( gordon.andar && !gordon.correr && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=4)
			gordon.stdModel[JANELA_NAVIGATE].SetSequence(4);

		if(gordon.correr && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=3)
			gordon.stdModel[JANELA_NAVIGATE].SetSequence(3);

		if(estado.teclas.x){
			gordon.andar=GL_FALSE;
			gordon.saltar=GL_TRUE;
			gordon.stdModel[JANELA_NAVIGATE].SetSequence(8);
			gordon.saltarStartTime=curr;
			alSourcePlay(estado.source[1]);
		}
	}
	else{
		float yInicial=gordon.objecto.pos.y;
		

		if(gordon.saltarStartTime + TEMPO_SALTO > curr){
			//	gordon.saltar = GL_FALSE;
			//gordon.stdModel[JANELA_NAVIGATE].SetSequence(0);
			gordon.objecto.pos.y=abs((yInicial+0.7)*sin(M_PI*curr/TEMPO_SALTO));

			/*	else{*/
			if(estado.teclas.right){
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
				//gordon.andar=GL_TRUE;
				//}
			}

			if(estado.teclas.left){
				//roda o objecto
				if(gordon.andarFrente){
					gordon.objecto.dir-=M_PI;
					gordon.andarFrente=GL_FALSE;
				}
				// calcula nova posição nx,nz
				nx=gordon.objecto.pos.x-velocidade;

				//if(!detectaColisao(nx,nz)){

				gordon.objecto.pos.x=nx;
				//gordon.andar=GL_TRUE;
				//}
			}

		}
		else{
			alSourceStop(estado.source[1]);
			gordon.saltar = GL_FALSE;
			gordon.stdModel[JANELA_NAVIGATE].SetSequence(0);
		}
	}

	redisplayAll();
}