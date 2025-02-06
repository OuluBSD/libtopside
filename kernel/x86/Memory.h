#ifndef _LittleKernel_Memory_h_
#define _LittleKernel_Memory_h_


//void  operator delete(void*);
void* operator new(unsigned int);

template <class T>
void* operator new(unsigned int, T*);

extern "C" {

	
}









static void SetFrame(uint32 frame_addr);
static void ClearFrame(uint32 frame_addr);
static uint32 TestFrame(uint32 frame_addr);
static uint32 FirstFrame();


void FreeFrame(Page *page);
void AllocFrame(Page *page, int is_kernel, int is_writeable);







#endif
