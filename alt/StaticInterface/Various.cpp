#include "StaticInterface.h"
#include "tga_reader.h"


NAMESPACE_TOPSIDE_BEGIN


Image TgaReaderBackend::LoadFileAny(String path) {
	String content = LoadFile(path);
	if (content.IsEmpty())
		return Image();
	
	int w = 0;
	int h = 0;
	int depth = 0;
	int bpp = 4; // always, see tgaRead impl
	void* src = (void*)tgaRead((const unsigned char*)content.Begin(), TGA_READER_ARGB, &w, &h, &depth);
	int len = w * h * bpp;
	RawSysImage* img = new RawSysImage();
	img->data.SetCount(len);
	memcpy(img->data.Begin(), src, len);
	img->backend = TypeIdClass();
	img->w = w;
	img->h = h;
	img->ch = bpp;
	img->pitch = w * bpp;
	
	tgaFree(src);
	
	/*Image i(img);
	auto* data = i.GetData();
	int w0 = data->img.GetWidth();
	Size sz = i.GetSize();*/
	
	return img;
}

Image TgaReaderBackend::LoadStringAny(String str) {
	
	TODO
	
}

void TgaReaderBackend::ClearImage(SysImage& img) {
	
}


NAMESPACE_TOPSIDE_END
