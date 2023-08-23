#ifndef _LittleLibrary_Common_h_
#define _LittleLibrary_Common_h_

#if REALHW
	#define EXTERN_C_BEGIN extern "C" {
	#define EXTERN_C_END }
#endif

#if EMU
	#define EXTERN_C_BEGIN
	#define EXTERN_C_END
#endif

int Pow(int i, int exp);
int Pow10(int exp);




void PanicAssert(const char *file, unsigned int line, const char *desc);
void MagicBreakpoint();



#endif
