#ifndef _DrawAlt_Image_h_
#define _DrawAlt_Image_h_


NAMESPACE_UPP


typedef enum {
	IMGDATA_NULL,
	IMGDATA_RAW,
	
	#if HAVE_SDL2
	IMGDATA_SDL2_SURFACE,
	#endif
} ImgDataType;

class Image : Moveable<Image> {
	
public:
	struct ImageDataRef {
		SysImage img;
		SysAccelImage accel;
		Point hotspot;
		int refs = 1;
		
		ImageDataRef(RawSysImage* raw) : img(raw), hotspot(0,0) {}
		void Inc() {refs++;}
		void Dec() {refs--; if (refs <= 0) delete this;}
	};
	
	Image() {}
	Image(const Image& img) {*this = img;}
	Image(Image&& img) {data = img.data; Chk(); img.data = NULL;}
	Image(ImageDataRef* data) : data(data) {data->Inc();}
	Image(RawSysImage* raw) {if (raw) {data = new ImageDataRef(raw);}}
	~Image() {Clear();}
	void Chk();
	void operator=(const Image& img) {Clear(); data = img.data; Chk(); if (data) data->Inc();}
	void Clear() {if (data) data->Dec(); data = NULL;}
	bool IsEmpty() const {return data == NULL;}
	void SetHotSpot(Point pt) {if (data) data->hotspot = pt;}
	Point GetHotSpot() const {if (data) return data->hotspot; return Point(0,0);}
	void CenterHotSpot() {if (data) data->hotspot = Point(GetWidth()/2, GetHeight()/2);}
	ImageDataRef* GetData() const {return data;}
	int GetWidth() const {if (!data) return 0; return data->img.GetWidth();}
	int GetHeight() const {if (!data) return 0; return data->img.GetHeight();}
	Size GetSize() const {if (!data) return Size(0,0); return Size(data->img.GetWidth(), data->img.GetHeight());}
	Size GetResolution() const {if (!data) return Size(0,0); return Size(data->img.GetWidth(), data->img.GetHeight());}
	int GetStride() const {if (!data) return 0; return data->img.GetStride();}
	int GetPitch() const {if (!data) return 0; return data->img.GetPitch();}
	const byte* GetIter(int x, int y) const;
	const byte* Begin() const {return GetIter(0,0);}
	const byte* End() const {Size sz = GetSize(); return GetIter(0, sz.cy);}
	void Serialize(Stream& s);
	operator bool() const {return data;}
	
	String ToString() const;
	
private:
	ImageDataRef* data = NULL;
	
};

#if HAVE_SDL2
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
	static Image LoadStringAny(String data);
	
};





enum {
	FILTER_NEAREST = 0,
	FILTER_BILINEAR = 1,
	FILTER_BSPLINE = 2,
	FILTER_COSTELLO = 3,
	FILTER_BICUBIC_MITCHELL = 4,
	FILTER_BICUBIC_CATMULLROM = 5,
	FILTER_LANCZOS2 = 6,
	FILTER_LANCZOS3 = 7,
	FILTER_LANCZOS4 = 8,
	FILTER_LANCZOS5 = 9,
};

Image RescaleFilter(const Image& img, int cx, int cy, int filter);
Image RescaleFilter(const Image& img, Size sz, Rect r, int filter);
Image CachedRescale(const Image& img, Size sz);


END_UPP_NAMESPACE


#endif
