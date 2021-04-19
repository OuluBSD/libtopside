#ifndef _BeBrowser_Image_h_
#define _BeBrowser_Image_h_

NAMESPACE_OULU_BEGIN

#define IMAGECLASS Images
#define IMAGEFILE <OuluCtrl/Images.iml>
#include IML_HEADER
#undef IMAGECLASS
#undef IMAGEFILE

#define IMAGECLASS DbgImages
#define IMAGEFILE <OuluCtrl/DbgImages.iml>
#include IML_HEADER
#undef IMAGECLASS
#undef IMAGEFILE

NAMESPACE_OULU_END

#endif
