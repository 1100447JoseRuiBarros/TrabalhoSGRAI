/***
 *
 *	Copyright (c) 1998, Valve LLC. All rights reserved.
 *
 *  Last modified 11/26/2001, Michael Haller, haller@fhs-hagenberg.ac.at
 *
 **/

#include <stdio.h>

#ifdef _WIN32         // Windows 32 ou 64 bits
  #include <windows.h>
  #include <gl\glut.h>
#else
  //  unsigned long GetTickCount();
#endif

#ifdef  __APPLE__
#include <glut/glut.h>
#endif

#if defined(__linux__) || defined(__unix__)
#include <gl/glut.h>
#endif

#include "mathlib.h"
#include "studio.h"
#include "mdlviewer.h"


#pragma warning( disable : 4244 ) // conversion from 'double ' to 'float ', possible loss of data
#pragma warning( disable : 4305 ) // truncation from 'const double ' to 'float '

vec3_t		g_vright;		// needs to be set to viewer's right in order for chrome to work
float		g_lambert = 1.5;

float		gldepthmin = 0;
float		gldepthmax = 10.0;


/*
=============
R_Clear
=============
*/
void R_Clear (void)
{
	glDepthFunc (GL_LEQUAL);
	glDepthRange (gldepthmin, gldepthmax);
	glDepthMask( 1 );
}

void mdlviewer_display( StudioModel &tempmodel )
{
	R_Clear( );

	tempmodel.SetBlending( 0, 0.0 );
	tempmodel.SetBlending( 1, 0.0 );

	float curr = glutGet(GLUT_ELAPSED_TIME)/1000.0;//GetTickCount( ) / 1000.0;
	tempmodel.AdvanceFrame( curr - tempmodel.GetPrev() );
	tempmodel.SetPrev( curr );

  glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT );
	  tempmodel.DrawModel();
  glPopAttrib();
}


void mdlviewer_init( char *modelname, StudioModel &tempmodel )
{
	// make a bogus texture
	// R_InitTexture( );

	tempmodel.Init( modelname );
	tempmodel.SetSequence( 0 );

	tempmodel.SetController( 0, 0.0 );
	tempmodel.SetController( 1, 0.0 );
	tempmodel.SetController( 2, 0.0 );
	tempmodel.SetController( 3, 0.0 );
	tempmodel.SetMouth( 0 );
}


void mdlviewer_nextsequence( StudioModel &tempmodel )
{
	int iSeq = tempmodel.GetSequence( );
	if (iSeq == tempmodel.SetSequence( iSeq + 1 ))
	{
		tempmodel.SetSequence( 0 );
	}

  printf("Seq: %d\n",tempmodel.GetSequence( ));
}


void mdlviewer_prevsequence( StudioModel &tempmodel )
{
	int iSeq = tempmodel.GetSequence( );
	if (iSeq == tempmodel.SetSequence( iSeq - 1 ))
	{
		tempmodel.SetSequence( 0 );
	}

  printf("Seq: %d\n",tempmodel.GetSequence( ));
}


//////////////////////////////////////////////////////////////////


static int pstyle;
static int translate = 1;
static int mesh = 1;
static float transx = 0, transy = 0, transz = -2, rotx=235, roty=-90;
static float scale = 0.01;
static float amplitude = 0.03;
static float freq = 5.0f;
static float phase = .00003;
static int ox = -1, oy = -1;
static int show_t = 1;
static int mot;
#define PAN	1
#define ROT	2
#define ZOOM 3
/*
void pan(int x, int y) 
{
    transx +=  (x-ox)/500.;
    transy -= (y-oy)/500.;
    ox = x; oy = y;
    glutPostRedisplay();
}


void zoom(int x, int y) 
{
    transz +=  (x-ox)/20.;
    ox = x;
    glutPostRedisplay();
}


void rotate(int x, int y) 
{
    rotx += x-ox;
    if (rotx > 360.) rotx -= 360.;
    else if (rotx < -360.) rotx += 360.;
    roty += y-oy;
    if (roty > 360.) roty -= 360.;
    else if (roty < -360.) roty += 360.;
    ox = x; oy = y;
    glutPostRedisplay();
}


void motion(int x, int y) 
{
    if (mot == PAN) 
		pan(x, y);
    else if (mot == ROT) 
		rotate(x,y);
	else if ( mot == ZOOM )
		zoom( x, y );
}


void mouse(int button, int state, int x, int y) 
{
    if(state == GLUT_DOWN) {
	switch(button) {
	case GLUT_LEFT_BUTTON:
	    mot = PAN;
	    motion(ox = x, oy = y);
	    break;
	case GLUT_RIGHT_BUTTON:
		mot = ROT;
	    motion(ox = x, oy = y);
	    break;
	case GLUT_MIDDLE_BUTTON:
	    break;
	}
    } else if (state == GLUT_UP) {
	mot = 0;
    }
}


void help(void) 
{
    printf("left mouse     - pan\n");
    printf("right mouse    - rotate\n");
}


void init( char *arg ) 
{
	mdlviewer_init( arg );

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.,1.,.1,10.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    
    glClearColor( 0, 0, 0.5, 0 );
}


void display(void) 
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
		glTranslatef(transx, transy, transz);   
		glRotatef(rotx, 0., 1., 0.);
		glRotatef(roty, 1., 0., 0.);
		glScalef( scale, scale, scale );
		glCullFace( GL_FRONT );
		glEnable( GL_DEPTH_TEST );
		mdlviewer_display( );
    glPopMatrix();

    glutSwapBuffers();    
}
*/