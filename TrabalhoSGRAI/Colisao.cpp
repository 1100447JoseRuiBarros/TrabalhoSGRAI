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

#include <stdio.h>
#include "Colisao.h"
#include "defines.h"
#include "mathlib.h"
#include "Globals.h"

GLboolean detectaColisao(GLfloat nx,GLfloat ny)
{
	//printf("nx:%f-ny:%f\n",nx,ny);

	//for(float i=0; i <= 2 * M_PI; i=i+M_PI/4){

	//	int yChao=floor((-ny+6 -  RAIOY_GORDON*sin(i))-0.5);//A arranjar
	//	//int yChao=floor(( -ny + 5  +   RAIOY_GORDON*sin(i)));
	//	int xChao=floor(( nx + 1  +   RAIOX_GORDON*cos(i))+0.5);
	//	printf("xChao:%d-yChao:%d\n",xChao,yChao);
	//	printf("i=%f\n",i);
	//	printf("Matriz Chao=%c\n",chao_mapa[yChao][xChao]);
	//	printf("Matriz Tecto=%c\n",tecto_mapa[yChao][xChao]);
	//	if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' 
	//		||tecto_mapa[yChao][xChao]=='*' ||tecto_mapa[yChao][xChao]=='1' || tecto_mapa[yChao][xChao]=='2'
	//		|| tecto_mapa[yChao][xChao]=='3' )
	//		return GL_TRUE;
	//}

	//Versão simplificada
								/*int yChao=0, xChao=0;

								if(gordon.saltar)
									yChao=floor((5.5-ny-RAIOY_GORDON));
	
								if(gordon.cair)
									yChao=floor((5.5-ny+RAIOY_GORDON));

								if(gordon.andarFrente)
									xChao=floor(( nx + 1.5 + RAIOX_GORDON));
								else
									xChao=floor(( nx + 1.5 - RAIOX_GORDON));

								if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' 
									||tecto_mapa[yChao][xChao]=='*' ||tecto_mapa[yChao][xChao]=='1' || tecto_mapa[yChao][xChao]=='2'
									|| tecto_mapa[yChao][xChao]=='3' )
									return GL_TRUE;*/

	int yChao=0, xChao=0;

	if(gordon.saltar)
	{
		yChao=floor((7.5-ny-RAIOY_GORDON));
		if(gordon.andarFrente)
		{
			xChao=floor(( nx + 1.5 + RAIOX_GORDON));
			if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' 
				||tecto_mapa[yChao][xChao]=='*' ||tecto_mapa[yChao][xChao]=='1' || tecto_mapa[yChao][xChao]=='2'
				|| tecto_mapa[yChao][xChao]=='3' )
				return GL_TRUE;
		}
		else
		{
			xChao=floor(( nx + 1.5 - RAIOX_GORDON));
			if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' 
				||tecto_mapa[yChao][xChao]=='*' ||tecto_mapa[yChao][xChao]=='1' || tecto_mapa[yChao][xChao]=='2'
				|| tecto_mapa[yChao][xChao]=='3' )
				return GL_TRUE;
		}
	}
	else
	{
		yChao=floor((7.5-ny+RAIOY_GORDON));
		if(gordon.andarFrente)
		{
			xChao=floor(( nx + 1.5 + RAIOX_GORDON));
			if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' 
				||tecto_mapa[yChao][xChao]=='*' ||tecto_mapa[yChao][xChao]=='1' || tecto_mapa[yChao][xChao]=='2'
				|| tecto_mapa[yChao][xChao]=='3' )
				return GL_TRUE;
		}
		else
		{
			xChao=floor(( nx + 1.5 - RAIOX_GORDON));
			if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' 
				||tecto_mapa[yChao][xChao]=='*' ||tecto_mapa[yChao][xChao]=='1' || tecto_mapa[yChao][xChao]=='2'
				|| tecto_mapa[yChao][xChao]=='3' )
				return GL_TRUE;
		}
	}

	return GL_FALSE;
}

GLboolean detectaColisao2(GLfloat nx,GLfloat ny)
{
	for(float i=0; i <= 2 * M_PI; i=i+M_PI/5)
	{
		int yChao=floor(( ny + 7  +   RAIOY_GORDON*sin(i))+0.5);
		int xChao=floor(( nx + 1  +   RAIOX_GORDON*cos(i))+0.5);
		if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' )
			return GL_TRUE;
	}
	return GL_FALSE;
}