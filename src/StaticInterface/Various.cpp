#include "StaticInterface.h"
#include "tga_reader.h"

#if HAVE_LIBPNG
	#include <png.h>
#endif

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
	img->backend = GetTypeIdClass<CLASSNAME>();
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


#if HAVE_LIBPNG

// http://zarb.org/~gc/html/libpng.html
Image LibPngBackend::LoadFileAny(String path) {
	int x, y;
	
	int width, height;
	png_byte color_type;
	png_byte bit_depth;
	
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;
	
	
	unsigned char header[8]; // 8 is the maximum size that can be checked
	
	// open file and test for it being a png */
	FILE *fp = fopen(path.Begin(), "rb");
	if (!fp) {
		RTLOG("LibPngBackend::LoadFileAny: error: File " << path << " could not be opened for reading");
		return Image();
	}
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8)) {
		RTLOG("LibPngBackend::LoadFileAny: error: File " << path << " is not recognized as a PNG file");
		return Image();
	}
	
	
	// initialize stuff
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	if (!png_ptr) {
		RTLOG("LibPngBackend::LoadFileAny: error: png_create_read_struct failed");
		return Image();
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		RTLOG("LibPngBackend::LoadFileAny: error: png_create_info_struct failed");
		return Image();
	}
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		RTLOG("LibPngBackend::LoadFileAny: error: Error during init_io");
		return Image();
	}
	
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);
	
	png_read_info(png_ptr, info_ptr);
	
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	
	number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);
	
	
	/* read file */
	if (setjmp(png_jmpbuf(png_ptr))) {
		RTLOG("LibPngBackend::LoadFileAny: error: Error during read_image");
		return Image();
	}
	
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	int pitch = png_get_rowbytes(png_ptr,info_ptr);
	for (y=0; y<height; y++)
	row_pointers[y] = (png_byte*) malloc(pitch);
	
	png_read_image(png_ptr, row_pointers);
	
	fclose(fp);
	
	
	
	int depth = 0;
	int bpp = 0;
	switch (color_type) {
		case PNG_COLOR_TYPE_GRAY:		bpp = 1 * bit_depth / 8; break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:	bpp = 2 * bit_depth / 8; break;
		case PNG_COLOR_TYPE_RGB:		bpp = 3 * bit_depth / 8; break;
		case PNG_COLOR_TYPE_RGB_ALPHA:	bpp = 4 * bit_depth / 8; break;
		default: break;
	}
	int len = width * height * bpp;
	RawSysImage* img = new RawSysImage();
	img->data.SetCount(len);
	img->backend = GetTypeIdClass<CLASSNAME>();
	img->w = width;
	img->h = height;
	img->ch = bpp;
	img->pitch = width * bpp;
	ASSERT(pitch >= img->pitch)
	
	byte* dst = img->data.Begin();
	for (y = 0; y < height; y++) {
		png_byte* row = row_pointers[y];
		memcpy(dst, row, img->pitch);
		dst += img->pitch;
		free(row_pointers[y]);
	}
	free(row_pointers);
	
	
	// Invert red and blue
	static_assert(sizeof(RGBA) == 4, "invalid size");
	byte* it = (byte*)img->data.Begin();
	byte* end = (byte*)img->data.End();
	if (img->data.GetCount() % bpp == 0) {
		while (it != end) {
			byte b = it[0];
			it[0] = it[2];
			it[2] = b;
			it += bpp;
		}
	}
	else {ASSERT(0);}
	
	return img;
}

Image LibPngBackend::LoadStringAny(String str) {
	
	TODO
	
}

void LibPngBackend::ClearImage(SysImage& img) {
	
}

#endif


NAMESPACE_TOPSIDE_END
