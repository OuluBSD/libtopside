#include "OOSDL2.h"

NAMESPACE_SDL2_BEGIN


bool Image::Open0() {
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP))	return true;
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))	return true;
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))	return true;
    if (IMG_Init(IMG_INIT_PNG))	return true;
	return false;
}

void Image::Close0() {
	IMG_Quit();
}


NAMESPACE_SDL2_END
