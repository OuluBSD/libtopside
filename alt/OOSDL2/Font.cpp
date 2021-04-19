#include "OOSDL2.h"

NAMESPACE_SDL2_BEGIN


bool Font::Open0() {
	return !TTF_Init();
}

void Font::Close0() {
	TTF_Quit();
}


NAMESPACE_SDL2_END
