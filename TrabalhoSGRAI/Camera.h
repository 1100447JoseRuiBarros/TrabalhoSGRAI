#pragma once

#include "camera_t.h"
#include "objecto_t.h"

void desenhaAngVisao(camera_t *cam);
void setNavigateSubwindowCamera(camera_t *cam, objecto_t obj);
void setTopSubwindowCamera( camera_t *cam,objecto_t obj);