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
	/* Coordenadas recebidas por parametro
	z
	^
	|
	-> x
	*/

	printf("nx:%f-ny:%f\n",nx,ny);


	for(float i=0; i <= 2 * M_PI; i=i+M_PI/5){


		/*int xChao=(int)COMP_CHAO-0.5+nx+RAIOX_GORDON*cos(i);
		int yChao=(int)ALT_CHAO+0.5+ny+RAIOY_GORDON*sin(i);*/
		int yChao=floor(( ny + 5  +   RAIOY_GORDON*sin(i))+0.5);
		int xChao=floor(( nx + 1  +   RAIOX_GORDON*cos(i))+0.5);
		printf("xChao:%d-yChao:%d\n",xChao,yChao);
		printf("i=%f\n",i);
		printf("Matriz=%c\n",chao_mapa[yChao][xChao]);
		if(chao_mapa[yChao][xChao]=='*' ||chao_mapa[yChao][xChao]=='1' || chao_mapa[yChao][xChao]=='2' )
			return GL_TRUE;
	}

	return GL_FALSE;
}

