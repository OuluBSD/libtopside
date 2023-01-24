#undef STB_IMAGE_IMPLEMENTATION
#include <ports/stb/stb_image.h>

#undef STB_TRUETYPE_IMPLEMENTATION
#include <ports/stb/stb_truetype.h>


/*#if defined flagWIN32 && defined flagMSC
	#include <SDL.h>
	#include <SDL_ttf.h>
	#include <SDL_image.h>
	#include <SDL_syswm.h>
	#ifdef flagSCREEN
		#include <SDL_opengl.h>
	#endif
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_image.h>
	#ifdef flagSCREEN
			#include <SDL2/SDL_opengl.h>
	#endif
#endif

#undef main*/


NAMESPACE_UPP


struct RawSysFont {
	void* native;
	TypeCls backend;
	String dir;
	String name;
	int ptsize = 0;
	int weight = 1;
	bool italic = false;
};

struct RawSysImage {
	Vector<byte> data;
	void* native = 0;
	TypeCls backend;
	int w, h, ch, pitch;
};

typedef RawSysImage		RawSysTexture;
typedef RGBA			SysColor;

struct SysFont {
	RawSysFont* raw = 0;
	
	SysFont(RawSysFont* f) : raw(f) {}
	~SysFont() {Clear();}
	
	void Clear();
	bool IsEmpty() const {return raw == 0;}
	
	RawSysFont* GetRaw() const {return raw;}
};


struct SysImage {
	RawSysImage* raw = 0;
	
	//SysImage() {}
	SysImage(RawSysImage* raw) : raw(raw) {}
	~SysImage() {Clear();}
	void Clear();
	int GetWidth() const;
	int GetHeight() const;
	int GetStride() const;
	int GetPitch() const;
	const unsigned char* GetData() const;
	
};


struct SysAccelImage {
	int tex = 0;
	
};

END_UPP_NAMESPACE
