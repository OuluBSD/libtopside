#include "ToolCtrl.h"
#include <TextDatabase/TextDatabase.h>


BEGIN_TEXTLIB_NAMESPACE


Image RescaleToFit(const Image& img, int smaller_side_length) {
	Size orig_sz = img.GetSize();
	double orig_small = max(orig_sz.cx, orig_sz.cy);
	double ratio = (double)smaller_side_length / orig_small;
	Size new_sz = orig_sz * ratio;
	Image scaled_img = CachedRescale(img, new_sz, FILTER_BILINEAR);
	return scaled_img;
}

String CacheImageFile(hash_t h) {
	String filename = MD5String(&h, sizeof(h)) + ".jpg";
	String cache_dir = ConfigFile("image-cache");
	String cache_path = AppendFileName(cache_dir, filename);
	return cache_path;
}

String ThumbnailImageFile(hash_t h) {
	String filename = MD5String(&h, sizeof(h)) + ".jpg";
	String thumb_dir = AppendFileName(MetaDatabase::GetDirectory(), "images" DIR_SEPS "thumbnails");
	String thumb_path = AppendFileName(thumb_dir, filename);
	return thumb_path;
}

String FullImageFile(hash_t h) {
	String filename = MD5String(&h, sizeof(h)) + ".jpg";
	String thumb_dir = AppendFileName(MetaDatabase::GetDirectory(), "images" DIR_SEPS "full");
	String thumb_path = AppendFileName(thumb_dir, filename);
	return thumb_path;
}



END_TEXTLIB_NAMESPACE
