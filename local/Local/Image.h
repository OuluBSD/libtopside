#ifndef _Local_Image_h_
#define _Local_Image_h_

NAMESPACE_TOPSIDE_BEGIN

enum {
	IMAGEID_GRID,
	
	IMAGEID_COUNT
};

Image GetDefaultImage(int code);
Image RealizeImage(Image& img, String path);



struct FloatImage {
	float* data = 0;
	Size sz;
	int pitch = 0;
	int channels = 0;
	int size = 0;
	
public:
	typedef FloatImage CLASSNAME;
	FloatImage() : sz(0,0) {}
	~FloatImage() {Clear();}
	FloatImage(Image& img) {*this = img;}
	
	void operator=(const Image& img) {Set(img);}
	void operator=(const Nuller&) {Clear();}
	
	bool Create() {return true;} // for IGraphics compatibility
	void Set(const Image& img);
	void Set(int w, int h, int stride, int src_pitch, const byte* data);
	void Set(Size sz, int channels);
	void Clear();
	void FlipVert();
	
	int GetPitch() const {return pitch;}
	int GetWidth() const {return sz.cx;}
	int GetHeight() const {return sz.cy;}
	int GetChannels() const {return channels;}
	int GetDataSize() const {return size;}
	Size GetSize() const {return sz;}
	
	float* Begin() {return data;}
	float* End() {if (!data) return 0; return data + sz.cy * pitch;}
	float* Detach() {float* f = data; data = 0; sz = Size(0,0); pitch = 0; channels = 0; size = 0; return f;}
	
	bool IsEmpty() {return data == 0;}
	operator bool() const {return data != 0;}
	
};

typedef const FloatImage ConstFloatImage;


struct ByteImage {
	byte* data = 0;
	Size sz;
	int pitch = 0;
	int channels = 0;
	int size = 0;
	
public:
	typedef ByteImage CLASSNAME;
	ByteImage() : sz(0,0) {}
	~ByteImage() {Clear();}
	ByteImage(Image& img) {*this = img;}
	
	void operator=(const Image& img) {Set(img);}
	void operator=(const Nuller&) {Clear();}
	
	bool Create() {return true;} // for IGraphics compatibility
	void Set(const Image& img);
	void Set(int w, int h, int stride, int src_pitch, const byte* data);
	void Set(Size sz, int channels);
	void Clear();
	void Zero();
	void Zero(RGBA clr);
	void FlipVert();
	void Randomize();
	
	int GetPitch() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetChannels() const;
	int GetSize() const;
	byte* GetIter(int x, int y);
	const byte* GetIter(int x, int y) const;
	
	byte* Begin() {return data;}
	byte* End() {if (!data) return 0; return data + sz.cy * pitch;}
	byte* Detach() {byte* f = data; data = 0; sz = Size(0,0); pitch = 0; channels = 0; size = 0; return f;}
	
	bool IsEmpty() {return data == 0;}
	operator bool() const {return data != 0;}
	
};

typedef const ByteImage ConstByteImage;

void	DataFromImage(const Image& img, Vector<byte>& data);
Image	MirrorVertical(const Image& img);



NAMESPACE_TOPSIDE_END

#endif
