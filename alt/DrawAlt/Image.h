#ifndef _DrawAlt_Image_h_
#define _DrawAlt_Image_h_


NAMESPACE_UPP_BEGIN


typedef enum {
	IMGDATA_NULL,
	IMGDATA_RAW,
	
	#ifdef flagSDL2
	IMGDATA_SDL2_SURFACE,
	#endif
} ImgDataType;

class Image : Moveable<Image> {
	
public:
	/*struct ImageDataRef {
		ImgDataType type = IMGDATA_NULL;
		void* obj = NULL;
		const byte* pixels = NULL;
		uint16 width = 0, height = 0, stride = 0, pitch = 0;
		Point hotspot;
		int refs = 0;
		ImageDataRef() : hotspot(0,0) {}
		~ImageDataRef() {Clear();}
		void Inc() {refs++;}
		void Dec() {refs--; if (refs <= 0) delete this;}
		void Clear();
	};*/
	struct ImageDataRef {
		SysImage img;
		SysAccelImage accel;
		Point hotspot;
		int refs = 1;
		
		//ImageDataRef() : hotspot(0,0) {}
		ImageDataRef(RawSysImage* raw) : img(raw), hotspot(0,0) {}
		void Inc() {refs++;}
		void Dec() {refs--; if (refs <= 0) delete this;}
	};
	
	Image() {}
	Image(const Image& img) {*this = img;}
	Image(Image&& img) {data = img.data; img.data = NULL;}
	Image(ImageDataRef* data) : data(data) {data->Inc();}
	Image(RawSysImage* raw) {if (raw) {data = new ImageDataRef(raw);}}
	~Image() {Clear();}
	void operator=(const Image& img) {Clear(); data = img.data; if (data) data->Inc();}
	void Clear() {if (data) data->Dec(); data = NULL;}
	bool IsEmpty() const {return data == NULL;}
	void SetHotSpot(Point pt) {if (data) data->hotspot = pt;}
	Point GetHotSpot() const {if (data) return data->hotspot; return Point(0,0);}
	void CenterHotSpot() {if (data) data->hotspot = Point(GetWidth()/2, GetHeight()/2);}
	ImageDataRef* GetData() const {return data;}
	int GetWidth() const {if (!data) return 0; return data->img.GetWidth();}
	int GetHeight() const {if (!data) return 0; return data->img.GetHeight();}
	Size GetSize() const {if (!data) return Size(0,0); return Size(data->img.GetWidth(), data->img.GetHeight());}
	int GetStride() const {if (!data) return 0; return data->img.GetStride();}
	int GetPitch() const {if (!data) return 0; return data->img.GetPitch();}
	const byte* GetIter(int x, int y) const;
	const byte* Begin() const {return GetIter(0,0);}
	const byte* End() const {Size sz = GetSize(); return GetIter(0, sz.cy);}
	void Serialize(Stream& s) {TODO}
	operator bool() const {return data;}
	
	void MakeSysAccel();
	//GLuint GetTexture() const {if (!data) return 0; return data->texture;}
	
	
private:
	ImageDataRef* data = NULL;
	
};

#ifdef flagSDL2
Image LoadAnyImage_SDL2(String path);
void FreeImageData_SDL2_Surface(void* v);
#endif


struct DefaultImages {
	static Image Arrow;
};

class ImageBuffer : Moveable<ImageBuffer> {
	Vector<RGBA> buf;
	Size sz;
	
public:
	ImageBuffer() : sz(0,0) {}
	ImageBuffer(Size sz) {Create(sz);}
	ImageBuffer(int w, int h) {Create(Size(w, h));}
	
	
	void Create(Size sz);
	void Clear();
	
	RGBA* Begin() {return buf.Begin();}
	RGBA* End() {return buf.End();}
	
	Image GetImage();
	
	operator Image() {return GetImage();}
};





class StreamRaster {
	
	
public:
	
	static Image LoadFileAny(String path);
	
};







NAMESPACE_UPP_END


#endif
