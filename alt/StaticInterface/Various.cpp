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
	RawSysImage* img = new RawSysImage();
	img->data = (const char*)tgaRead((const unsigned char*)content.Begin(), TGA_READER_ARGB, &w, &h, &depth);
	img->backend = TypeIdClass();
	img->w = w;
	img->h = h;
	img->ch = bpp;
	img->pitch = w * bpp;
	
	/*Image i(img);
	auto* data = i.GetData();
	int w0 = data->img.GetWidth();
	Size sz = i.GetSize();*/
	
	return img;
}

Image TgaReaderBackend::LoadStringAny(String str) {
	
	TODO
	
}


NAMESPACE_TOPSIDE_END
