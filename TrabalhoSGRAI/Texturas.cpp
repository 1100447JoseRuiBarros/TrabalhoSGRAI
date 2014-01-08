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
#include "Texturas.h"

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

void createTextures(GLuint texID[])
{
	AUX_RGBImageRec *TextureImage;

	glGenTextures(NUM_TEXTURAS,texID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
	//cubos do chão
	if (TextureImage=LoadBMP(NOME_TEXTURA_CUBOS))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CUBOS]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",NOME_TEXTURA_CUBOS);
		exit(0);
	}
	//cubos das plataformas
	if (TextureImage=LoadBMP(NOME_TEXTURA_PLATAFORMAS))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_PLATAFORMAS]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",NOME_TEXTURA_PLATAFORMAS);
		exit(0);
	}
	//cubos das escadas
	if (TextureImage=LoadBMP(NOME_TEXTURA_ESCADAS))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_ESCADAS]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",NOME_TEXTURA_ESCADAS);
		exit(0);
	}
	//cilindros dos pipes
	if (TextureImage=LoadBMP(NOME_TEXTURA_PIPES))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_PIPES]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",NOME_TEXTURA_PIPES);
		exit(0);
	}
	
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void createTexturesSkybox()
{
	AUX_RGBImageRec *TextureImage;

	glGenTextures(NUM_TEXTURAS_SKYBOX,skybox);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

	//skybox 1
	if (TextureImage=LoadBMP(SKYBOX1))
	{
		glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",SKYBOX1);
		exit(0);
	}
	//skybox 2
	if (TextureImage=LoadBMP(SKYBOX2))
	{
		glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",SKYBOX2);
		exit(0);
	}
	//skybox 3
	if (TextureImage=LoadBMP(SKYBOX3))
	{
		glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX3]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",SKYBOX3);
		exit(0);
	}
	//skybox 4
	if (TextureImage=LoadBMP(SKYBOX4))
	{
		glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX4]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",SKYBOX4);
		exit(0);
	}
	//skybox 5
	if (TextureImage=LoadBMP(SKYBOX5))
	{
		glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX5]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",SKYBOX5);
		exit(0);
	}
	//skybox 6
	if (TextureImage=LoadBMP(SKYBOX6))
	{
		glBindTexture(GL_TEXTURE_2D, skybox[ID_SKYBOX6]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	else
	{
		printf("Textura %s not Found\n",SKYBOX6);
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
}