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
GLfloat yInicial=0;
int plat1 [140] = {0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,3,3,0,0,3,3,0,0,0,0,0,0,0,0,0,3,3,3,0,0,3,3,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0};
int plat2 [140] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pipe[140] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,4,4,4,4,0,0,0,0,0,4,4,4,4,4,0,0,4,4,4,4,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4,4,4,4,4,4,0,0,0,0,0};
int esc[140] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,0,0,4,3,2,1,0,0,0,0,0,1,2,3,4,99,0,0,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,88,0,0,0,0,0};
int chao [140] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void reset()
{
	ny=gordon.objecto.pos.y;

	if(ny < -4.0)
	{
		alSourceStop(estado.source[0]);
		alSourcePlay(estado.source[2]);
		MessageBox(NULL,"Perdeu. Comece de novo.","FIM", MB_OK | MB_ICONEXCLAMATION);
		gordon.objecto.pos.x = 0;
		gordon.objecto.pos.y = 0;
		gordon.saltar = GL_FALSE;
		gordon.cair = GL_FALSE;
		estado.teclas.down = GL_FALSE;
		estado.teclas.left = GL_FALSE;
		estado.teclas.right = GL_FALSE;
		estado.teclas.up = GL_FALSE;
		estado.teclas.x = GL_FALSE;
		estado.teclas.z = GL_FALSE;
		alSourceStop(estado.source[2]);
		alSourcePlay(estado.source[0]);
	}
}

void saltar()
{
	gordon.andar=GL_FALSE;
	ny=gordon.objecto.pos.y+velocidade*10;
	if(!detectaColisao(nx,ny - 0.01))
	{
		if(gordon.objecto.pos.y < yInicial + 4)
		{
			gordon.objecto.pos.y=ny;
			gordon.saltar=GL_TRUE; 
		}
		else
		{
			gordon.saltar=GL_FALSE;
			gordon.cair=GL_TRUE;
		}
	}
	else
	{
		gordon.saltar=GL_FALSE;
		gordon.cair=GL_TRUE;
	}
}

void cair()
{
	gordon.andar=GL_FALSE;
	ny=gordon.objecto.pos.y-gravidade*10;
	if(!detectaColisao(nx,ny - 0.01))
	{
		gordon.objecto.pos.y=ny;
		gordon.cair=GL_TRUE; 
	}
	else
	{
		gordon.cair=GL_FALSE;
		//gordon.objecto.pos.y+=0.25;
	}

}

void verific()
{
	nx=gordon.objecto.pos.x;
	ny=gordon.objecto.pos.y;

	int x = floor(nx+0.5);

	if(ny > -0.5 && ny < 0.5)
	{
		if(chao[x]==1 && !detectaColisao(nx,ny))
		{
			gordon.cair=GL_TRUE;
		}
	}
}

void verificimacaesdaca()
{
	nx=gordon.objecto.pos.x;
	ny=gordon.objecto.pos.y;

	int x = floor(nx+0.5);

	if((ny > 0.8 && ny < 1.3))
	{
		if((esc[x+1]==1 && !detectaColisao(nx,ny)) || (esc[x-1]==1 && !detectaColisao(nx,ny)))
		{
			gordon.cair=GL_TRUE;
		}
	}
	else if((ny > 1.8 && ny < 2.3))
	{
		if((esc[x+1]==2 && !detectaColisao(nx,ny)) || (esc[x-1]==2 && !detectaColisao(nx,ny)))
		{
			gordon.cair=GL_TRUE;
		}
	}
	else if((ny > 2.8 && ny < 3.3))
	{
		if((esc[x+1]==3 && !detectaColisao(nx,ny)) || (esc[x-1]==3 && !detectaColisao(nx,ny)))
		{
			gordon.cair=GL_TRUE;
		}
	}
	else if((ny > 3.8 && ny < 4.3))
	{
		if((esc[x+1]==4 && !detectaColisao(nx,ny)) || ((esc[x-1]==4 && esc[x]!=99 && !detectaColisao(nx,ny))))
		{
			gordon.cair=GL_TRUE;
		}
	}
	else if((ny > 4.8 && ny < 5.3))
	{
		if((esc[x+1]==5 && !detectaColisao(nx,ny)) || ((esc[x-1]==5 && esc[x]!=88 && !detectaColisao(nx,ny))))
		{
			gordon.cair=GL_TRUE;
		}
	}
	if((ny > 3.8 && ny < 4.3))
	{
		if(esc[x-1]==99 && !detectaColisao(nx,ny))
		{
			gordon.cair=GL_TRUE;
		}
	}
	if((ny > 4.8 && ny < 5.3))
	{
		if(esc[x-1]==88 && !detectaColisao(nx,ny))
		{
			gordon.cair=GL_TRUE;
		}
	}
}

void verificacimapipe()
{
	nx=gordon.objecto.pos.x;
	ny=gordon.objecto.pos.y;

	int x = floor(nx+0.5);

	if((ny > 0.8 && ny < 1.3) || (ny > 1.8 && ny < 2.3))
	{
		if(pipe[x]==0 && !detectaColisao(nx,ny))
		{
			gordon.cair=GL_TRUE;
		}
	}
}

void verificacimaplataforma2()
{
	nx=gordon.objecto.pos.x;
	ny=gordon.objecto.pos.y;

	int x = floor(nx+0.5);

	if(ny > 5.8 && ny < 6.3)
	{
		if(plat2[x]==0 && !detectaColisao(nx,ny))
		{
			gordon.cair=GL_TRUE;
		}
	}
}

void verificacimaplataforma1()
{
	nx=gordon.objecto.pos.x;
	ny=gordon.objecto.pos.y;

	int x = floor(nx+0.5);

	if(ny > 2.8 && ny < 3.3)
	{
		if(plat1[x]==0 && !detectaColisao(nx,ny))
		{
			gordon.cair=GL_TRUE;
		}
	}
}

void virarFrente()
{

	if(!gordon.andarFrente)
	{
		gordon.objecto.dir+=M_PI;
		gordon.andarFrente=GL_TRUE;
	}
	// calcula nova posição nx,nz
	nx=gordon.objecto.pos.x+velocidade;
	if(!detectaColisao(nx - 0.05,ny))
	{
		gordon.objecto.pos.x=nx;
		if(!gordon.cair && !gordon.saltar)
			gordon.andar=GL_TRUE; 
	}
	/*else*/
	//printf("Colidiu a andar para a direita lolololololol!\n");
}

void virarTras()
{

	if(gordon.andarFrente)
	{
		gordon.objecto.dir-=M_PI;
		gordon.andarFrente=GL_FALSE;
	}
	// calcula nova posição nx,nz
	nx=gordon.objecto.pos.x-velocidade;

	if(!detectaColisao(nx - 0.05,ny))
	{

		gordon.objecto.pos.x=nx;
		if(!gordon.cair && !gordon.saltar)
			gordon.andar=GL_TRUE;
	}
}			

void setAnimacoes()
{
	//if((gordon.cair /*|| gordon.saltar*/) && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=0 )
	//{
	//	gordon.stdModel[JANELA_NAVIGATE].SetSequence(0);
	//	gordon.stdModel[JANELA_TOP].SetSequence(0);
	//	return;
	//}


	if( (!gordon.andar && !gordon.correr && !gordon.saltar) || (gordon.cair && gordon.andar) || 
		(gordon.cair && gordon.correr) || gordon.cair && gordon.stdModel[JANELA_NAVIGATE].GetSequence() != 0)
	{
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(0);
		gordon.stdModel[JANELA_TOP].SetSequence(0);
		//printf("Animação idle\n");
		return;
	}


	if(gordon.correr && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=3)
	{
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(3);
		gordon.stdModel[JANELA_TOP].SetSequence(3);
		//printf("Animação correr\n");
		return;
	}

	if(gordon.andar && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=4)
	{
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(4);
		gordon.stdModel[JANELA_TOP].SetSequence(4);
		//printf("Animação andar\n");
		return;
	}

	if(gordon.saltar && gordon.stdModel[JANELA_NAVIGATE].GetSequence()!=8)
	{
		gordon.stdModel[JANELA_NAVIGATE].SetSequence(8);
		gordon.stdModel[JANELA_TOP].SetSequence(8);
		//printf("Animação saltar\n");
		return;
	}
}

bool verificaChao()
{

	ny=gordon.objecto.pos.y-gravidade;
	if(!detectaColisao(nx,ny))
	{
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

void verificacrabs()
{
	nx=gordon.objecto.pos.x;
	ny=gordon.objecto.pos.y;

	if(ny > -0.5 && ny < 0.5)
	{
		for(int i=0; i< 3; i++)
		{
			GLfloat hx = headCrabs[i].objecto.pos.x;
			int nxint = floor(nx);
			int hnint = floor(hx);

			if(nxint == hnint)
			{
				alSourceStop(estado.source[0]);
				alSourcePlay(estado.source[2]);
				MessageBox(NULL,"Perdeu. Comece de novo.","FIM", MB_OK | MB_ICONEXCLAMATION);
				gordon.objecto.pos.x = 0;
				gordon.objecto.pos.y = 0;
				gordon.saltar = GL_FALSE;
				gordon.cair = GL_FALSE;
				estado.teclas.down = GL_FALSE;
				estado.teclas.left = GL_FALSE;
				estado.teclas.right = GL_FALSE;
				estado.teclas.up = GL_FALSE;
				estado.teclas.x = GL_FALSE;
				estado.teclas.z = GL_FALSE;
				alSourceStop(estado.source[2]);
				alSourcePlay(estado.source[0]);
			}
		}
	}
}

void fim()
{
	nx=gordon.objecto.pos.x;

	if((int)nx == 136)
	{
		alSourceStop(estado.source[0]);
		alSourcePlay(estado.source[3]);
		MessageBox(NULL,"Parabens ganhou o jogo!","FIM", MB_OK | MB_ICONEXCLAMATION);
		gordon.objecto.pos.x = 0;
		gordon.objecto.pos.y = 0;
		gordon.saltar = GL_FALSE;
		gordon.cair = GL_FALSE;
		estado.teclas.down = GL_FALSE;
		estado.teclas.left = GL_FALSE;
		estado.teclas.right = GL_FALSE;
		estado.teclas.up = GL_FALSE;
		estado.teclas.x = GL_FALSE;
		estado.teclas.z = GL_FALSE;
		alSourceStop(estado.source[3]);
		alSourcePlay(estado.source[0]);
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
	else if(verificaChao() && gordon.cair)
		cair();
	else
	{
		verificacimaplataforma1();
		verificacimaplataforma2();
		verificacimapipe();
		verificimacaesdaca();
		verific();
	}

	if(gordon.cair)
		reset();

	if(estado.teclas.x && !gordon.saltar /*&& !gordon.cair*/)
	{
		yInicial=gordon.objecto.pos.y;
		alSourcePlay(estado.source[1]);
		saltar();
	}

	if(estado.teclas.right)
	{
		virarFrente();
	}

	if(estado.teclas.left)
	{
		virarTras();
	}

	if(estado.teclas.z && !gordon.saltar && !gordon.cair)
	{
		gordon.andar=GL_FALSE;
		gordon.correr=GL_TRUE;
	}
	else
		gordon.correr=GL_FALSE;

	if(!estado.teclas.right && !estado.teclas.left)
	{
		gordon.andar=GL_FALSE;
		gordon.correr=GL_FALSE;
	}

	/*if(!verificaChaoParado())
	{
	gordon.cair = GL_TRUE;
	}*/

	verificacrabs();

	fim();

	setAnimacoes();

	redisplayAll();
}