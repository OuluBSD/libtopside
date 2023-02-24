#ifndef _Draw_ImageOp_h_
#define _Draw_ImageOp_h_

NAMESPACE_UPP_BEGIN

Image Rescale(const Image& src, Size sz, Gate<int, int> progress = Null);

void SweepMkImageCache();

NAMESPACE_UPP_END

#endif
