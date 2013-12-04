#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

#define	GAP					              25

#define MAZE_HEIGHT			          18
#define MAZE_WIDTH			          18

#define	OBJECTO_ALTURA		      0.4
#define OBJECTO_VELOCIDADE	      0.5
#define OBJECTO_ROTACAO		        5
#define OBJECTO_RAIO		      0.12
#define SCALE_HOMER               0.005
#define EYE_ROTACAO			        1

#ifdef _WIN32
#define NOME_TEXTURA_CUBOS        "Textura.bmp"
#else
#define NOME_TEXTURA_CUBOS        "Textura.jpg"
#endif

#define NOME_TEXTURA_CHAO         "Chao.jpg"


#define NUM_TEXTURAS              2
#define ID_TEXTURA_CUBOS          0
#define ID_TEXTURA_CHAO           1

#define	CHAO_DIMENSAO		      10

#define NUM_JANELAS               2
#define JANELA_TOP                0
#define JANELA_NAVIGATE           1