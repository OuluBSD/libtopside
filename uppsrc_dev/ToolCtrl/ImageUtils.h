#ifndef _ToolCtrl_ImageUtils_h_
#define _ToolCtrl_ImageUtils_h_


BEGIN_TEXTLIB_NAMESPACE


String CacheImageFile(hash_t h);
String ThumbnailImageFile(hash_t h);
String FullImageFile(hash_t h);

Image RescaleToFit(const Image& img, int smaller_side_length);


END_TEXTLIB_NAMESPACE


#endif
