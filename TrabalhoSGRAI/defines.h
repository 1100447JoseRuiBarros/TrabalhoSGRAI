#pragma once

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

#define	GAP					              25

#define	OBJECTO_ALTURA		      0.4
#define OBJECTO_VELOCIDADE	      0.5
#define OBJECTO_ROTACAO		        5
#define OBJECTO_RAIO		      0.12
#define SCALE_GORDON               0.015
#define SCALE_GORDONY              0.01
#define RAIOX_GORDON               0.15
#define RAIOY_GORDON               RAIOX_GORDON*2.5
#define EYE_ROTACAO			        1
#define GRAVIDADE					0.001;

#define NOME_TEXTURA_CUBOS			"Cubo.bmp"
#define NOME_TEXTURA_PLATAFORMAS	"Plataforma.bmp"
#define NOME_TEXTURA_ESCADAS		"Escada.bmp"
#define NOME_TEXTURA_PIPES			"Pipe.bmp"

#define SKYBOX1						"s1.bmp"
#define SKYBOX2						"s2.bmp"
#define SKYBOX3						"s3.bmp"
#define SKYBOX4						"s4.bmp"
#define SKYBOX5						"s5.bmp"
#define SKYBOX6						"s6.bmp"

#define NUM_TEXTURAS            4
#define NUM_TEXTURAS_SKYBOX		6

#define ID_TEXTURA_CUBOS		0
#define ID_TEXTURA_PLATAFORMAS	1
#define ID_TEXTURA_ESCADAS		2
#define ID_TEXTURA_PIPES		3
#define ID_SKYBOX1				0
#define ID_SKYBOX2				1
#define ID_SKYBOX3				2
#define ID_SKYBOX4				3
#define ID_SKYBOX5				4
#define ID_SKYBOX6				5

#define	CHAO_DIMENSAO		    10

#define NUM_JANELAS             2
#define JANELA_TOP              0
#define JANELA_NAVIGATE         1

#define TEMPO_SALTO				900

#define COMP_CHAO				140
#define ALT_CHAO				12
#define COMP_TECTO				140
#define ALT_TECTO				9