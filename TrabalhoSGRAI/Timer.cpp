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
			gordon.cair=GL_TRUE;
		}
	}
	else{
		gordon.saltar=GL_FALSE;
		gordon.cair=GL_TRUE;
	}
}

void cair(){

	ny=gordon.objecto.pos.y-gravidade;
	if(!detectaColisao(nx,ny)){

		gordon.objecto.pos.y=ny;
		gordon.cair=GL_TRUE; 
	}
	else{
		gordon.cair=GL_FALSE;
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

	if(gordon.andar=GL_FALSE && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=0
		|| gordon.cair && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=0){
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

bool verificaChao(){

	ny=gordon.objecto.pos.y-gravidade;
	if(!detectaColisao(nx,ny)){

		return true; 
	}
	else
		return false; 
}

void crabsColisoes(GLuint curr)
{
	//crabs


	headCrabs[0].prev = curr;

	for(int i=0; i< 3; i++)
	{
		GLfloat hx = headCrabs[i].objecto.pos.x;
		GLfloat hy = headCrabs[i].objecto.pos.y;

		if(headCrabs[i].stdModel[JANELA_NAVIGATE].GetSequence()==0)
		{
			headCrabs[i].stdModel[JANELA_NAVIGATE].SetSequence(4);
			headCrabs[i].stdModel[JANELA_TOP].SetSequence(4);
		}

		if(headCrabs[i].andarFrente)
		{
			if(!detectaColisao2(hx + 0.05,hy))
			{
				headCrabs[i].objecto.pos.x=hx + 0.05;
				headCrabs[i].andar=GL_TRUE;
				/*headCrabs[0].stdModel[JANELA_NAVIGATE].SetSequence(3);
				headCrabs[0].stdModel[JANELA_TOP].SetSequence(3);*/
				headCrabs[i].objecto.dir = 0;
			}
			else
			{
				headCrabs[i].andarFrente = GL_FALSE;
				headCrabs[i].objecto.dir = M_PI;
			}		
		}
		else
		{
			if(!detectaColisao2(hx - 0.05,hy))
			{
				headCrabs[i].objecto.pos.x=hx - 0.05;
				headCrabs[i].andar=GL_TRUE;
				/*headCrabs[0].stdModel[JANELA_NAVIGATE].SetSequence(3);
				headCrabs[0].stdModel[JANELA_TOP].SetSequence(3);*/
				headCrabs[i].objecto.dir = M_PI;
			}
			else
			{
				headCrabs[i].andarFrente = GL_TRUE;
				headCrabs[i].objecto.dir = 0;
			}
		}
	}
}

void Timer(int value)
{
	GLuint curr = glutGet(GLUT_ELAPSED_TIME);
	crabsColisoes(curr);

	// calcula velocidade baseado no tempo passado
	if(!gordon.correr)
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001;
	else
		velocidade= gordon.objecto.vel*(curr - gordon.prev )*0.001*5;

	gravidade=gordon.objecto.vel*(curr - gordon.prev )*0.001;
	glutTimerFunc(estado.timer, Timer, 0);
	gordon.prev = curr;

	if(gordon.saltar)
		saltar();
	/*else
	if(verificaChao()||gordon.cair)
	cair();*/

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

	if(!estado.teclas.right && !estado.teclas.left){
		gordon.andar=GL_FALSE;
	}

	if(estado.teclas.z && gordon.andar && !gordon.saltar && !gordon.cair)
		gordon.correr=GL_TRUE;
	else
		gordon.correr=GL_FALSE;

	setAnimacoes();

	redisplayAll();
}