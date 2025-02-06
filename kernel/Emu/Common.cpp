#include "Emu.h"



void PanicAssert(const char *file, unsigned int line, const char *desc) {
	LOG("ASSERTION-FAILED(" << desc << ") at " << file << ":" << line);
	Panic("assertion failed");
}


void MagicBreakpoint() {
	__BREAK__;
}

int Pow(int i, int exp) {
	if (exp == 0) return 1;
	int out = i;
	if (exp < 0)
		return 0;
	for(int j = 1; j < exp; j++)
		out *= i;
	return out;
}

int Pow10(int exp) {
	return Pow(10, exp);
}