#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


Image DefaultImages::Arrow;


Image GetDefaultImage(int code) {
	static Image cube;
	
	switch (code) {
		case IMAGEID_GRID: return RealizeImage(cube, ShareDirFile("models" DIR_SEPS "cube.png"));
	}
	return Image();
}

Image RealizeImage(Image& img, String path) {
	if (img.IsEmpty())
		img = StreamRaster::LoadFileAny(path);
	return img;
}

void SetCenterHotSpot(Image& img) {
	Size sz = img.GetSize();
	if (!sz.IsEmpty()) {
		Point hs(sz.cx / 2, sz.cy / 2);
		#ifdef UPP_VERSION
		ImageBuffer ib(img);
		ib.SetHotSpot(hs);
		img = ib;
		#else
		img.SetHotSpot(hs);
		#endif
	}
}



void FloatImage::operator=(const FloatImage& i) {
	TODO
}

void FloatImage::Clear() {
	if (data) {
		free(data);
		sz = Size(0, 0);
		pitch = 0;
		channels = 0;
		size = 0;
	}
}

void FloatImage::FlipVert() {
	int half = sz.cy / 2;
	for(int y = 0; y < half; y++) {
		int yb = sz.cy - 1 - y;
		float* a = data + y * pitch;
		float* b = data + yb * pitch;
		for(int i = 0; i != pitch; i++)
			Swap(*a++, *b++);
	}
}

void FloatImage::Set(const Image& img) {
	Size sz = img.GetSize();
	#ifdef LIBTOPSIDE
	Set(sz.cx, sz.cy, img.GetStride(), img.GetPitch(), img.Begin());
	#else
	Set(sz.cx, sz.cy, 4, sz.cx, (const byte*)img.Begin());
	#endif
}

void FloatImage::Set(int w, int h, int stride, int src_pitch, const byte* src_data) {
	Clear();
	
	sz = Size(w,h);
	channels = stride;
	pitch = sz.cx * channels;
	size = pitch * sz.cy;
	
	ASSERT(channels >= 1 && channels <= 4);
	data = (float*)malloc(sizeof(float) * size);
	
	float* f = data;
	const byte* it = src_data;
	const byte* end = src_data + sz.cy * pitch;
	
	if (src_pitch == pitch) {
		int exp_size = (int)(end - it);
		ASSERT(exp_size == size);
		while (it != end) {
			double v = *it++ / 255.0;
			ASSERT(IsFin(v));
			*f++ = (float)v;
		}
	}
	else {
		for(int y = 0; y < sz.cy; y++) {
			const byte* it0 = it + y * src_pitch;
			const byte* end0 = it0 + pitch;
			while (it0 != end0)
				*f++ = (float)(*it0++ / 255.0);
		}
	}
}

void FloatImage::Set(Size sz, int channels) {
	Clear();
	
	this->sz = sz;
	this->channels = channels;
	pitch = sz.cx * channels;
	size = pitch * sz.cy;
	
	ASSERT(channels >= 1 && channels <= 4);
	data = (float*)malloc(sizeof(float) * size);
}





void ByteImage::operator=(const ByteImage& i) {
	if (i.data)
		Set(i.sz.cx, i.sz.cy, i.channels, i.pitch, i.data);
	else
		Clear();
}

void ByteImage::FlipVert() {
	int half = sz.cy / 2;
	for(int y = 0; y < half; y++) {
		int yb = sz.cy - 1 - y;
		byte* a = data + y * pitch;
		byte* b = data + yb * pitch;
		for(int i = 0; i != pitch; i++)
			Swap(*a++, *b++);
	}
}

void ByteImage::Set(const Image& img) {
	Size sz = img.GetSize();
	#ifdef LIBTOPSIDE
	Set(sz.cx, sz.cy, img.GetStride(), img.GetPitch(), img.Begin());
	#else
	Set(sz.cx, sz.cy, 4, sz.cx, (const byte*)img.Begin());
	#endif
}

void ByteImage::Set(int w, int h, int stride, int src_pitch, const byte* src_data) {
	Clear();
	sz = Size(w,h);
	channels = stride;
	pitch = sz.cx * channels;
	size = pitch * sz.cy;
	ASSERT(channels >= 1 && channels <= 4);
	
	data = (byte*)malloc(sizeof(byte) * size);
	
	if (src_data) {
		byte* b = data;
		const byte* it = src_data;
		const byte* end = src_data + size;
		
		if (src_pitch == pitch) {
			#if 1
			memcpy(b, it, size);
			#else
			while (it != end)
				*b++ = *it++;
			#endif
		}
		else {
			for(int y = 0; y < sz.cy; y++) {
				const byte* it0 = it + y * src_pitch;
				const byte* end0 = it0 + pitch;
				while (it0 != end0)
					*b++ = *it0++;
			}
		}
	}
}

void ByteImage::Resize(Size sz) {
	ASSERT(channels > 0);
	if (channels)
		Set(sz, channels);
}

void ByteImage::Set(Size sz, int channels) {
	if (this->sz == sz && this->channels == channels)
		return;
	if (lock_channels && this->channels != 0 && this->channels != channels) {
		Panic("ByteImage: trying to change channel number, but the number is locked");
	}
	Clear();
	this->sz = sz;
	this->channels = channels;
	pitch = sz.cx * channels;
	size = pitch * sz.cy;
	ASSERT(channels >= 1 && channels <= 4);
	
	data = (byte*)malloc(sizeof(byte) * size);
}

void ByteImage::Clear() {
	if (data) {
		free(data);
		sz = Size(0, 0);
		pitch = 0;
		channels = 0;
		size = 0;
		data = 0;
	}
}

void ByteImage::Zero(RGBA clr) {
	if (clr.r == 0 && clr.g == 0 && clr.b == 0 && clr.a == 0)
		Zero();
	else if (data) {
		ASSERT(channels >= 1 && channels <= 4);
		if (!((channels >= 1 && channels <= 4))) return;
		
		for(int y = 0; y < sz.cy; y++) {
			byte* dst = data + y * pitch;
			for (int x = 0; x < sz.cx; x++) {
				const byte* src = &clr.r;
				for(int i = 0; i < channels; i++)
					*dst++ = src[i];
			}
		}
	}
}

void ByteImage::Zero() {
	if (data)
		memset(data, 0, size);
}

void ByteImage::SwapRedBlue() {
	byte* it = data;
	byte* end = data + size;
	int stride = this->channels;
	if (stride >= 3 && (size % stride) == 0) {
		while (it != end) {
			byte s = it[0];
			it[0] = it[2];
			it[2] = s;
			it += stride;
		}
	}
}

void ByteImage::ToGrayscaleRGB() {
	if (!data || channels >= 3)
		return;
	int old_channels = this->channels;
	int old_pitch = this->pitch;
	this->channels = 3;
	pitch = sz.cx * 3;
	size = pitch * sz.cy;
	ASSERT(channels >= 1 && channels <= 4);
	
	byte* old_data = data;
	data = (byte*)malloc(sizeof(byte) * size);
	
	for(int y = 0; y < sz.cy; y++) {
		byte* from = old_data + y * old_pitch;
		byte* to = data + y * pitch;
		for(int x = 0; x < sz.cx; x++) {
			byte gray = *from;
			for(int i = 0; i < old_channels; i++)
				*to++ = *from++;
			for(int i = old_channels; i < 3; i++)
				*to++ = gray;
		}
	}
	
	free(old_data);
}

void ByteImage::SetSwapRedBlue(const ByteImage& i, bool add_alpha_ch) {
	int new_ch = i.GetChannels();
	if (new_ch == 3 && add_alpha_ch)
		new_ch = 4;
	
	if (this->sz != i.sz || this->channels != new_ch) {
		Clear();
		this->sz = i.sz;
		this->channels = new_ch;
		pitch = sz.cx * channels;
		size = pitch * sz.cy;
		ASSERT(channels >= 1 && channels <= 4);
		
		data = (byte*)malloc(sizeof(byte) * size);
	}
	
	if (channels == 4 && i.channels == 4) {
		ASSERT(pitch == i.pitch);
		const dword* src = (const dword*)i.data;
		union {
			dword* dst;
			byte* b;
		};
		dst = (dword*)data;
		dword* end = dst + size / 4;
		while (dst != end) {
			*dst = *src++;
			byte s = b[0];
			b[0] = b[2];
			b[2] = s;
			dst++;
		}
	}
	else if (channels == 4 && i.channels == 3) {
		ASSERT(pitch / 4 == i.pitch / 3);
		const byte* src = (const byte*)i.data;
		byte* dst = (byte*)data;
		byte* end = dst + size;
		ASSERT(size % 4 == 0);
		while (dst != end) {
			dst[0] = src[2];
			dst[1] = src[1];
			dst[2] = src[0];
			dst[3] = 255;
			dst += 4;
			src += 3;
		}
	}
	else {
		TODO
	}
}

void ByteImage::Randomize() {
	byte* it = data;
	byte* end = data + size;
	while (it != end)
		*it++ = (byte)Random(256);
}

int ByteImage::GetPitch() const {
	return pitch;
}

int ByteImage::GetWidth() const {
	return sz.cx;
}

int ByteImage::GetHeight() const {
	return sz.cy;
}

int ByteImage::GetChannels() const {
	return channels;
}

int ByteImage::GetLength() const {
	return size;
}

Size ByteImage::GetSize() const {
	return sz;
}

byte* ByteImage::GetIter(int x, int y) {
	ASSERT(x >= 0 && y >= 0 && x < sz.cx && y < sz.cy);
	ASSERT(sz.cx && sz.cy && data && pitch && channels);
	return data + y * pitch + x * channels;
}

const byte* ByteImage::GetIter(int x, int y) const {
	ASSERT(x >= 0 && y >= 0 && x < sz.cx && y < sz.cy);
	ASSERT(sz.cx && sz.cy && data && pitch && channels);
	return data + y * pitch + x * channels;
}








void DataFromImage(const Image& img, Vector<byte>& out) {
	#ifdef UPP_VERSION
	
	TODO
	
	#else
	Image::ImageDataRef* data = img.GetData();
	if (!data)
		return;
	
	SysImage& simg = data->img;
	
	const byte* it = simg.GetData();
	int pitch = simg.GetPitch();
	int stride = simg.GetStride();
	int width = simg.GetWidth();
	int height = simg.GetHeight();
	
	int line = stride * width;
	int sz = line * height;
	ASSERT(pitch >= line);
	
	if (stride == 4) {
		out.SetCount(sz);
		
		if (line == pitch)
			memcpy(out.Begin(), it, sz);
		else {
			TODO
		}
	}
	else {
		ASSERT(stride < 4);
		int dst_stride = 4;
		int dst_size = dst_stride * width * height;
		out.SetCount(dst_size);
		
		byte* out_it = out.Begin();
		int line_pad = pitch - line;
		ASSERT(line_pad >= 0);
		
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				for (int i = 0; i < dst_stride; i++) {
					byte val = i < stride ? *it++ : 0;
					*out_it++ = val;
				}
			}
			it += line_pad;
		}
		
		ASSERT(out_it == out.End());
	}
	#endif
}

Image MirrorVertical(const Image& img) {
	#ifdef UPP_VERSION
	
	TODO
	
	#else
	Image::ImageDataRef* data = img.GetData();
	if (img.GetSize().IsNull() || !data)
		return img;
	
	SysImage& simg = data->img;
	
	const byte* it = simg.GetData();
	int pitch = simg.GetPitch();
	int stride = simg.GetStride();
	int width = simg.GetWidth();
	int height = simg.GetHeight();
	
	ImageBuffer ib(width, height);
	RGBA* dst = ib.End();
	
	int line = stride * width;
	int sz = line * height;
	ASSERT(pitch >= line);
	
	if (stride == 4) {
		
		if (line == pitch) {
			for (int y = height-1; y >= 0; y--) {
				dst -= width;
				memcpy(dst, it, line);
				it += line;
			}
		}
		else {
			TODO
		}
	}
	else {
		ASSERT(stride < 4);
		const int dst_stride = 4;
		int dst_size = dst_stride * width * height;
		
		int line_pad = pitch - line;
		ASSERT(line_pad >= 0);
		
		for (int y = height-1; y >= 0; y--) {
			dst -= width;
			byte* out_it = (byte*)dst;
			for (int x = 0; x < width; x++) {
				for (int i = 0; i < dst_stride; i++) {
					byte val = i < stride ? *it++ : 0;
					*out_it++ = val;
				}
			}
			it += line_pad;
		}
	}
	
	return ib;
	#endif
}









DescriptorImage::DescriptorImage() {
	
}

void DescriptorImage::AddDescriptor(float x, float y, float angle, void* descriptor) {
	ASSERT(resolution.cx > 0 && resolution.cy > 0);
	if (x >= 0 && x < resolution.cx &&
		y >= 0 && y < resolution.cy) {
		angle = fmodf(angle, 2*M_PI);
		Descriptor& d = descriptors.Add();
		d.x = x;
		d.y = y;
		d.angle = angle / (2*M_PI) * 0x100;
		uint32* u = (uint32*)descriptor;
		for(int i = 0; i < 8; i++)
			d.u[i] = u[i];
	}
}

String DescriptorImage::ToString() const {
	String s;
	int i = 0;
	for(const Descriptor& d : descriptors) {
		s << i++ << ": " << d.x << ", " << d.y << ", " << (int)d.angle << "\n";
	}
	return s;
}





int GetDescriptor8HammingDistance(const uint32* a, const uint32* b) {
	int dist = 0;
	for(int i = 0; i < 8; i++)
		dist += PopCount32(a[i] ^ b[i]);
	return dist;
}


NAMESPACE_TOPSIDE_END
