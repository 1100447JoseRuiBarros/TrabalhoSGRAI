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
#include "Key.h"
#include "Window.h"
#include "Illumination.h"
#include "Timer.h"

#pragma comment (lib, "glaux.lib")    /* link with Win32 GLAUX lib usada para ler bitmaps */

// função para ler jpegs do ficheiro readjpeg.c
extern "C" int read_JPEG_file(const char *, char **, int *, int *, int *);


void strokeCenterString(char *str,double x, double y, double z, double s)
{
	int i,n;

	n = strlen(str);
	glPushMatrix();
	glTranslated(x-glutStrokeLength(GLUT_STROKE_ROMAN,(const unsigned char*)str)*0.5*s,y-119.05*0.5*s,z);
	glScaled(s,s,s);
	for(i=0;i<n;i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,(int)str[i]);
	glPopMatrix();

}

///////////////////////////////////
/// Texturas

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
	//cubos do ch„o
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

/////////////////////////////////////
//Modelo



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
	createTexturesSkybox();

	GLfloat normais[][3] = {	{0,0,-1},
							{0,1,0},
							{-1,0,0},
							{1,0,0},
							{0,0,1},
							{0,-1,0}
							};

    glPushMatrix();
	
	glTranslatef(70,0,0);
	glScalef(180.0f,180.0f,180.0f);
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

//void desenhaModelo()
//{
//	glColor3f(0,1,0);
//	glutSolidCube(OBJECTO_ALTURA);
//	glPushMatrix();
//	glColor3f(1,0,0);
//	glTranslatef(GRAUS(modelo.objecto.dir),OBJECTO_ALTURA*0.75,0);
//	glRotatef(0,0,1,0);
//	glutSolidCube(OBJECTO_ALTURA*0.5);
//	glPopMatrix();
//}

/////////////////////////////////////
//navigateSubwindow

void motionNavigateSubwindow(int x, int y)
{

}

void mouseNavigateSubwindow(int button, int state, int x, int y)
{

}

void imprime_ajuda(void)
{
	printf("\n\nDesenho de um quadrado\n");
	printf("h,H - Ajuda \n");
	printf("******* Diversos ******* \n");
	printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
	printf("w,W - Wireframe \n");
	printf("f,F - Fill \n");
	printf("******* Movimento ******* \n");
	printf("up  - Acelera \n");
	printf("down- Trava \n");
	printf("left- Vira rodas para a direita\n");
	printf("righ- Vira rodas para a esquerda\n");
	printf("******* Camara ******* \n");
	printf("F1 - Alterna camara da janela da Esquerda \n");
	printf("F2 - Alterna camara da janela da Direita \n");
	printf("PAGE_UP, PAGE_DOWN - Altera abertura da camara \n");
	printf("botao esquerdo + movimento na Janela da Direita altera o olhar \n");
	printf("ESC - Sair\n");
}

////////////////////////////////////
// InicializaÁıes

void createDisplayLists(int janelaID)
{
	modelo.labirinto[janelaID]=glGenLists(2);
	glNewList(modelo.labirinto[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT );
	glPopAttrib();
	glEndList();

	modelo.chao[janelaID]=modelo.labirinto[janelaID]+1;
	glNewList(modelo.chao[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT );
	desenhaskybox();
	desenhachao(modelo.texID[janelaID][ID_TEXTURA_CUBOS]);
	desenhapips(modelo.texID[janelaID][ID_TEXTURA_PIPES]);
	desenhaescadas(modelo.texID[janelaID][ID_TEXTURA_ESCADAS]);
	desenhaplataformas(modelo.texID[janelaID][ID_TEXTURA_PLATAFORMAS]);
	glPopAttrib();
	glEndList();
}

void init()
{
	GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };

	estado.timer=100;	

	/*estado.camera.eye.x=0;
	estado.camera.eye.y=OBJECTO_ALTURA*2;
	estado.camera.eye.z=0;
	estado.camera.dir_long=0;
	estado.camera.dir_lat=0;*/
	estado.camera1.fov=60;
	estado.camera2.fov=60;

	estado.localViewer=1;
	estado.vista[JANELA_TOP]=0;
	estado.vista[JANELA_NAVIGATE]=0;

	gordon.objecto.pos.x=0;
	gordon.objecto.pos.y=OBJECTO_ALTURA;
	gordon.objecto.pos.z=0;
	gordon.objecto.dir=0;
	gordon.objecto.vel=OBJECTO_VELOCIDADE;
	gordon.andarFrente=GL_TRUE;
	gordon.saltar=GL_FALSE;

	modelo.xMouse=modelo.yMouse=-1;

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);  // por causa do Scale ao Homer

	if(glutGetWindow()==estado.mainWindow)
		glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	else
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
	
}

/////////////////////////////////////
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800+GAP*3, 400+GAP*2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if ((estado.mainWindow=glutCreateWindow("Labirinto")) == GL_FALSE)
		exit(1);

	imprime_ajuda();

	// Registar callbacks do GLUT da janela principal
	init();
	glutReshapeFunc(reshapeMainWindow);
	glutDisplayFunc(displayMainWindow);

	glutTimerFunc(estado.timer,Timer,0);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	// criar a sub window topSubwindow
	estado.topSubwindow=glutCreateSubWindow(estado.mainWindow, GAP, GAP, 400, 400);
	init();
	setLight();
	setMaterial();
	createTextures(modelo.texID[JANELA_TOP]);
	createDisplayLists(JANELA_TOP);

	mdlviewer_init("gordon.mdl", gordon.stdModel[JANELA_TOP] );

	for(int i=0;i<3;i++)
		mdlviewer_init("headcrab.mdl", headCrabs[i].stdModel[JANELA_TOP] );

	glutReshapeFunc(redisplayTopSubwindow);
	glutDisplayFunc(displayTopSubwindow);

	glutTimerFunc(estado.timer,Timer,0);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);


	// criar a sub window navigateSubwindow
	estado.navigateSubwindow=glutCreateSubWindow(estado.mainWindow, 400+GAP, GAP, 400, 800);
	init();
	setLight();
	setMaterial();

	createTextures(modelo.texID[JANELA_NAVIGATE]);
	createDisplayLists(JANELA_NAVIGATE);
	mdlviewer_init("gordon.mdl", gordon.stdModel[JANELA_NAVIGATE] );

	for(int i=0;i<3;i++)
		mdlviewer_init("headcrab.mdl", headCrabs[i].stdModel[JANELA_NAVIGATE] );

	glutReshapeFunc(reshapeNavigateSubwindow);
	glutDisplayFunc(displayNavigateSubwindow);
	glutMouseFunc(mouseNavigateSubwindow);

	glutTimerFunc(estado.timer,Timer,0);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);

	alutInit (&argc, argv);
	estado.buffer[0] = alutCreateBufferFromFile("mario.wav");
	estado.buffer[1] = alutCreateBufferFromFile("jump.wav");
	alGenSources(4, estado.source);
	alSourcei(estado.source[0], AL_BUFFER, estado.buffer[0]);
	alSourcei(estado.source[1], AL_BUFFER, estado.buffer[1]);
	alSourcePlay(estado.source[0]);

	glutMainLoop();
	return 0;

}