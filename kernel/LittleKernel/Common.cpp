#include "Kernel.h"


// Write a byte out to the specified port.
void outb(uint16 port, uint8 value) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8 inb(uint16 port) {
   uint8 ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16 inw(uint16 port) {
   uint16 ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
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


// Copy len bytes from src to dest.
void memcpy(void *dst, const void *src, uint32 len)
{
	#if 0
    const uint8 *sp = (const uint8 *)src;
    uint8 *dp = (uint8 *)dst;
    for(; len != 0; len--) *dp++ = *sp++;
    #else
	int u32_len = len / 4;
	len = len % 4;
	
	const uint32* src_u32 = (uint32*)src;
	uint32* dst_u32 = (uint32*)dst;
    for ( ; u32_len != 0; u32_len--) {
		*dst_u32++ = *src_u32++;
    }
    
	const uint8 *src_u8 = (uint8 *)src_u32;
	uint8 *dst_u8 = (uint8 *)dst_u32;
    for ( ; len != 0; len--) {
		*dst_u8++ = *src_u8++;
    }
    #endif
}

// Write len copies of val into dest.
void memset(void *dest, uint8 val, uint32 len) {
	//MON.Write("memset: ").WriteHex(dest).Write(", ").WriteDec(val).Write(", ").WriteDec(len).NewLine();
	
	int u32_len = len / 4;
	len = len % 4;
	
	uint32 def = val << 24 | val << 16 | val << 8 | val;
	uint32* u32 = (uint32*)dest;
    for ( ; u32_len != 0; u32_len--) {
		*u32++ = def;
    }
    
	uint8 *u8 = (uint8 *)u32;
    for ( ; len != 0; len--) {
		*u8++ = val;
    }
}
/*void memset(uint32 *dest, uint32 val, uint32 len) {
    uint32 *temp = (uint32 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}*/


// Compare two strings. Should return -1 if
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(const char *str1, const char *str2) {
	int i = 0;
	int failed = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] != str2[i]) {
			failed = 1;
			break;
		}
		i++;
	}
	// why did the loop exit?
	if ((str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0'))
		failed = 1;
		
	return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src) {
	do {
		*dest++ = *src++;
	}
	while (*src != 0);
	return dest;
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src) {
	while (*dest != 0) {
		*dest = *dest++;
	}
	
	do {
		*dest++ = *src++;
	}
	while (*src != 0);
	return dest;
}

int strlen(char *src) {
	int i = 0;
	while (*src++)
		i++;
	return i;
}







void PanicAssert(const char *file, unsigned int line, const char *desc) {
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    MON.Write("ASSERTION-FAILED(");
    MON.Write(desc);
    MON.Write(") at ");
    MON.Write(file);
    MON.Write(":");
    MON.WriteDec(line);
    MON.Write("\n");
    // Halt by going into an infinite loop.
    for(;;);
}


void MagicBreakpoint() {
	asm volatile ("xchgw %bx, %bx");
}

