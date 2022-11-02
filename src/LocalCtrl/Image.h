#ifndef _BeBrowser_Image_h_
#define _BeBrowser_Image_h_

NAMESPACE_TOPSIDE_BEGIN

#ifndef LIBTOPSIDE

#define IMAGECLASS Images
#define IMAGEFILE <LocalCtrl/Images.iml>
#include IML_HEADER
#undef IMAGECLASS
#undef IMAGEFILE

#define IMAGECLASS DbgImages
#define IMAGEFILE <LocalCtrl/DbgImages.iml>
#include IML_HEADER
#undef IMAGECLASS
#undef IMAGEFILE

#endif

NAMESPACE_TOPSIDE_END

#endif
