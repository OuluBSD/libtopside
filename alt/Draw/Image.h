#ifndef _DrawAlt_Image_h_
#define _DrawAlt_Image_h_


NAMESPACE_UPP


#if 0
typedef enum {
	IMGDATA_NULL,
	IMGDATA_RAW,
	
	#if HAVE_SDL2
	IMGDATA_SDL2_SURFACE,
	#endif
} ImgDataType;
#endif


class Image : Moveable<Image> {
	
public:
	RTTI_SECONDARY(Image)
	
	#undef NO_DATA
	typedef enum {
		NO_DATA,
		IMAGE_DATA_REF,
		SDL_CURSOR,
	} DataType;
	
	struct ImageDataRef {
		SysImage img;
		SysAccelImage accel;
		Point hotspot;
		int refs = 1;
		
		ImageDataRef(RawSysImage* raw) : img(raw), hotspot(0,0) {}
		void Inc() {refs++;}
		void Dec() {refs--; if (refs <= 0) delete this;}
	};
	
	Image();
	Image(const Nuller&);
	Image(const Image& img);
	Image(Image&& img);
	Image(ImageDataRef* data);
	Image(RawSysImage* raw);
	Image(Image (*fn)());
	Image(const Image& (*fn)());
	~Image();
	
	void operator=(const Image& img);
	void Clear();
	void SetHotSpot(Point pt);
	void SetAuxData(int64 d);
	void Set(void* data, DataType dt, int64 aux_data=0);
	
	bool IsSame(const Image& i) const;
	bool IsEmpty() const;
	Point GetHotSpot() const;
	void CenterHotSpot();
	ImageDataRef* GetData() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetLength() const;
	Size GetSize() const;
	Size GetResolution() const;
	int GetStride() const;
	int GetPitch() const;
	const byte* GetIter(int x, int y) const;
	const byte* Begin() const;
	const byte* End() const;
	bool IsImageDataRef() const;
	operator bool() const;
	bool IsNullInstance() const;
	hash_t GetHashValue() const;
	
	void Chk();
	void Serialize(Stream& s);
	String ToString() const;
	
	int32 GetSerialId() const;
	int64 GetAuxData() const;
	
	#define STD_CURSOR(x) static const Image& x();
	STD_CURSOR(Arrow)
	STD_CURSOR(Wait)
	STD_CURSOR(IBeam)
	STD_CURSOR(No)
	STD_CURSOR(SizeAll)
	STD_CURSOR(SizeHorz)
	STD_CURSOR(SizeVert)
	STD_CURSOR(SizeTopLeft)
	STD_CURSOR(SizeTop)
	STD_CURSOR(SizeTopRight)
	STD_CURSOR(SizeLeft)
	STD_CURSOR(SizeRight)
	STD_CURSOR(SizeBottomLeft)
	STD_CURSOR(SizeBottom)
	STD_CURSOR(SizeBottomRight)
	STD_CURSOR(Hand)
	#undef STD_CURSOR
private:
	DataType data_type = NO_DATA;
	void* data = NULL;
	int64 aux_data = 0;
	int32 serial_id = 0;
	
	static Atomic serial_counter;
	
};

#if HAVE_SDL2
Image LoadAnyImage_SDL2(String path);
void FreeImageData_SDL2_Surface(void* v);
#endif


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



struct Iml {
	inline static void ResetAll() {TODO}
	
};


END_UPP_NAMESPACE


#endif
