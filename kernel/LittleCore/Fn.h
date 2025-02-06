#ifndef _LittleCore_Fn_h_
#define _LittleCore_Fn_h_


#ifndef flagEMU
int strnlen(const char* s, int n);
void memcpy(void *dest, const void *src, uint32 len);
void memset(void *dest, uint8 val, uint32 len);
//void memset(uint32 *dest, uint32 val, uint32 len);
int strcmp(const char *str1, const char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strlen(char *src);
void PanicAssert(const char *file, unsigned int line, const char *desc);
#endif



#endif
