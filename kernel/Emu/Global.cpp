#include "Emu.h"

SVar* global;


TVar& GetThreadVars() {
	thread_local static TVar v;
	return v;
}
