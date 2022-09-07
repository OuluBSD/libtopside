#undef STB_IMAGE_IMPLEMENTATION
#include <ports/stb/stb_image.h>

#undef STB_TRUETYPE_IMPLEMENTATION
#include <ports/stb/stb_truetype.h>

NAMESPACE_UPP

typedef stbtt_fontinfo		RawSysFont;

struct RawSysImage {
	const char* data;
	int w, h, ch, pitch;
};

typedef RawSysImage		RawSysTexture;
typedef RGBA			SysColor;

struct SysFont {
	RawSysFont* raw = 0;
	
	SysFont() {}
	SysFont(RawSysFont* f) : raw(f) {}
	~SysFont() {Clear();}
	
	void Clear();
	bool IsEmpty() const {return raw == 0;}
	
	RawSysFont* GetRaw() const {return raw;}
	RawSysImage* RenderTextBlended(const char* s, SysColor c);
};

struct SysImage {
	RawSysImage* raw = 0;
	
	//SysImage() {}
	SysImage(RawSysImage* raw) : raw(raw) {}
	~SysImage() {Clear();}
	void Clear();
	int GetWidth() const {return raw ? raw->w : 0;}
	int GetHeight() const {return raw ? raw->h : 0;}
	int GetStride() const {return raw ? raw->ch : 0;}
	int GetPitch() const {return raw ? raw->pitch : 0;}
	const unsigned char* GetData() const {return raw ? (const unsigned char*)raw->data : 0;}
	
};


struct SysAccelImage {
	int tex = 0;
	
};

END_UPP_NAMESPACE
