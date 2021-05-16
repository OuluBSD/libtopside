#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


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
	#ifndef flagUPP
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
	#ifndef flagUPP
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

void ByteImage::Randomize() {
	byte* it = data;
	byte* end = data + size;
	while (it != end)
		*it++ = (byte)Random(256);
}

NAMESPACE_TOPSIDE_END
