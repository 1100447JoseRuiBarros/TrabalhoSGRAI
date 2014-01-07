#pragma once

#include "ESTADO.h"
#include "MODELO.h"
#include "Model.h"

/////////////////////////////////////
//variaveis globais

extern ESTADO estado;
extern MODELO modelo;
extern Model gordon;
extern Model headCrabs[3];

extern GLUquadric* quad;
extern GLuint *skybox;

extern char chao_mapa[ALT_CHAO][COMP_CHAO+1];
extern char tecto_mapa[ALT_TECTO][COMP_TECTO+1];

void desenhaBoundingBox();