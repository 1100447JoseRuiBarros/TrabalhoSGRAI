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
#include <AL/alut.h>
#include "Globals.h"
#include "Window.h"
#include "Colisao.h"

//Variáveis Globais
GLfloat nx,ny;
float velocidade;
float gravidade;
GLfloat yInicial;

void saltar(){

	ny=gordon.objecto.pos.y+velocidade;
	if(!detectaColisao(nx,ny)){
		if(gordon.objecto.pos.y < yInicial + 3){
			gordon.objecto.pos.y=ny;
			gordon.saltar=GL_TRUE; 
		}
		else{
			gordon.saltar=GL_FALSE;
			//gordon.cair=GL_TRUE;
		}
	}
	else{
		gordon.saltar=GL_FALSE;
		//gordon.cair=GL_TRUE;
	}
}

void cair(){

	ny=gordon.objecto.pos.y-gravidade;
	if(!detectaColisao(nx,ny)){

		gordon.objecto.pos.y=ny;
		gordon.cair=GL_TRUE; 
	}
	else{
		//gordon.cair=GL_FALSE;
		//gordon.objecto.pos.y+=0.25;
	}
}

void virarFrente(){

	if(!gordon.andarFrente){
		gordon.objecto.dir+=M_PI;
		gordon.andarFrente=GL_TRUE;
	}
	// calcula nova posição nx,nz
	nx=gordon.objecto.pos.x+velocidade;
	if(!detectaColisao(nx,ny)){

		gordon.objecto.pos.x=nx;
		gordon.andar=GL_TRUE; 
	}
	/*else*/
		//printf("Colidiu a andar para a direita lolololololol!\n");
}

void virarTras(){

	if(gordon.andarFrente){
		gordon.objecto.dir-=M_PI;
		gordon.andarFrente=GL_FALSE;
	}
	// calcula nova posição nx,nz
	nx=gordon.objecto.pos.x-velocidade;

	if(!detectaColisao(nx,ny)){

		gordon.objecto.pos.x=nx;
		gordon.andar=GL_TRUE;
	}
}			

void setAnimacoes(){

	if(gordon.andar=GL_FALSE && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=0){
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(0);
		gordon.stdModel[JANELA_TOP].SetSequence(0);
	}

	if( gordon.andar && !gordon.correr && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=4){
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(4);
		gordon.stdModel[JANELA_TOP].SetSequence(4);
	}

	if(gordon.correr && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=3){
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(3);
		gordon.stdModel[JANELA_TOP].SetSequence(3);
	}

	if(gordon.saltar && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=8){
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(8);
		gordon.stdModel[JANELA_TOP].SetSequence(8);
	}
}

void Timer(int value)
{
	GLuint curr = glutGet(GLUT_ELAPSED_TIME);
	// calcula velocidade baseado no tempo passado
	if(!gordon.correr)
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001;
	else
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001*5;

	gravidade=gordon.objecto.vel*(curr - gordon.prev )*0.001;
	glutTimerFunc(estado.timer, Timer, 0);
	gordon.prev = curr;

	/*gordon.correr=GL_FALSE;
	gordon.andar=GL_FALSE;
	gordon.saltar=GL_FALSE;
	gordon.cair=GL_FALSE;*/

	if(gordon.saltar)
		saltar();
	else
		cair();

	if(estado.teclas.x && !gordon.saltar){
		yInicial=gordon.objecto.pos.y;
		alSourcePlay(estado.source[1]);
		saltar();
	}

	if(estado.teclas.right){
		virarFrente();
	}

	if(estado.teclas.left){
		virarTras();
	}

	if(estado.teclas.z && gordon.andar)
		gordon.correr=GL_TRUE;

	setAnimacoes();

	redisplayAll();
}