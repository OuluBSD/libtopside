#ifndef _LittleKernel_Memory_h_
#define _LittleKernel_Memory_h_

#include "Common.h"
#include "Heap.h"

//void  operator delete(void*);
void* operator new(unsigned int);

extern "C" {

	
}









static void SetFrame(uint32 frame_addr);
static void ClearFrame(uint32 frame_addr);
static uint32 TestFrame(uint32 frame_addr);
static uint32 FirstFrame();


void FreeFrame(Page *page);
void AllocFrame(Page *page, int is_kernel, int is_writeable);






void InitLinkerVariables(uint32 end=0);

#endif
