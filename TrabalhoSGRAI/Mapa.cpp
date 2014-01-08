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
#include "Mapa.h"

void desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[])
{
	
    glBegin(GL_POLYGON);
		glColor3f(0.5f,0.5f,0.5f);
        glNormal3fv(normal);
		glTexCoord2f(0.0f, 0.0f);
        glVertex3fv(a);
		glTexCoord2f(1.0f, 0.0f);
        glVertex3fv(b);
		glTexCoord2f(1.0f, 1.0f);
        glVertex3fv(c);
		glTexCoord2f(0.0f, 1.0f);
        glVertex3fv(d);
    glEnd();
}

void desenhaCubo()
{

	GLfloat vertices[][3] = {	{-0.5,-0.5,-0.5}, 
								{0.5,-0.5,-0.5}, 
								{0.5,0.5,-0.5}, 
								{-0.5,0.5,-0.5}, 
								{-0.5,-0.5,0.5},  
								{0.5,-0.5,0.5}, 
								{0.5,0.5,0.5}, 
								{-0.5,0.5,0.5}
								};

	GLfloat normais[][3] = {	{0,0,-1},
								{0,1,0},
								{-1,0,0},
								{1,0,0},
								{0,0,1},
								{0,-1,0}
								};

	desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],normais[0]);
	desenhaPoligono(vertices[2],vertices[3],vertices[7],vertices[6],normais[1]);
	desenhaPoligono(vertices[3],vertices[0],vertices[4],vertices[7],normais[2]);
	desenhaPoligono(vertices[6],vertices[5],vertices[1],vertices[2],normais[3]);
	desenhaPoligono(vertices[4],vertices[5],vertices[6],vertices[7],normais[4]);
	desenhaPoligono(vertices[5],vertices[4],vertices[0],vertices[1],normais[5]);
	
}

void desenhachao(GLuint texID)
{
	int x=0;
	int y=6;

	glBindTexture(GL_TEXTURE_2D, texID);

	for(int i=0;i<ALT_CHAO;i++)
	{
		for(int j=0;j<COMP_CHAO+1;j++)
		{
			if(chao_mapa[i][j]=='*')
			{
				glPushMatrix();
				glTranslatef(x-1,y-0.5,0);
				desenhaCubo();
				glPopMatrix();
				x++;
			}
			else
				x++;
		}
		x = 0;
		y--;
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhapips(GLuint texID)
{
	int x=0;
	int y=6;

	int numlados = 32;
	float tamanho = 0.5;
	GLfloat ang=2*M_PI/numlados;

	glBindTexture(GL_TEXTURE_2D, texID);

	for(int i=0;i<ALT_CHAO;i++)
	{
		for(int j=0;j<COMP_CHAO+1;j++)
		{
			if(chao_mapa[i][j]=='1')
			{
				glPushMatrix();
					glTranslatef(x-1,y,0);
					glRotatef(90,1,0,0);
					glRotatef(180,0,0,1);
					glColor3f(0.5f,0.5f,0.5f);
					gluQuadricTexture(quad,1);
					gluCylinder(quad,0.5,0.5,1,20,2);
				glPopMatrix();

				//desenhar o topo do pipe
				glBindTexture(GL_TEXTURE_2D, NULL);

				glPushMatrix();
				glTranslatef(x-1,y,0);
				glRotatef(90,1,0,0);
				glBegin(GL_POLYGON);
				//glColor3f(0.031f,0.476f,0.105f);
				glColor3f(0.0f,0.0f,0.0f);
				for(int i=0;i<numlados;i++)
				{
					glVertex3f(tamanho*cos(i*ang),tamanho*sin(i*ang),0.0);
				}
				glEnd();
				glPopMatrix();

				x++;

				glBindTexture(GL_TEXTURE_2D, texID);
			}
			else
				x++;
		}
		x = 0;
		y--;
	}
}

void desenhaescadas(GLuint texID)
{
	int x=0;
	int y=6;

	glBindTexture(GL_TEXTURE_2D, texID);

	for(int i=0;i<ALT_CHAO;i++)
	{
		for(int j=0;j<COMP_CHAO+1;j++)
		{
			if(chao_mapa[i][j]=='2')
			{
				glPushMatrix();
				glTranslatef(x-1,y-0.5,0);
				desenhaCubo();
				glPopMatrix();
				x++;
			}
			else
				x++;
		}
		x = 0;
		y--;
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhaplataformas(GLuint texID)
{
	int x=0;
	int y=6;

	glBindTexture(GL_TEXTURE_2D, texID);

	for(int i=0;i<ALT_TECTO;i++)
	{
		for(int j=0;j<COMP_TECTO+1;j++)
		{
			if(tecto_mapa[i][j]=='3')
			{
				glPushMatrix();
				glTranslatef(x-1,y-0.5,0);
				desenhaCubo();
				glPopMatrix();
				x++;
			}
			else
				x++;
		}
		x = 0;
		y--;
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhaskybox()
{
	GLfloat normais[][3] = {	{0,0,-1},
							{0,1,0},
							{-1,0,0},
							{1,0,0},
							{0,0,1},
							{0,-1,0}
							};

    glPushMatrix();
	
	glTranslatef(70,0,0);
	glScalef(2000.0f,2000.0f,2000.0f);
	glColor3f(0.5f,0.5f,0.5f);
	//face de tras
	glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX6]);
    glBegin(GL_QUADS);
		glNormal3fv(normais[4]);
        glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
    //face da direita
    glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX1]);
    glBegin(GL_QUADS);
		glNormal3fv(normais[3]);
        glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
    glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
    //face da frente
    glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX2]);
    glBegin(GL_QUADS);
		glNormal3fv(normais[4]);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
    glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
    //face da esquerda
	glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX3]);
    glBegin(GL_QUADS);
		glNormal3fv(normais[3]);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
    //face de cima
	glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX4]);
    glBegin(GL_QUADS);
		glNormal3fv(normais[1]);
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
    //face de baixo
    glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX5]);
    glBegin(GL_QUADS);
		glNormal3fv(normais[1]);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, NULL);
}
