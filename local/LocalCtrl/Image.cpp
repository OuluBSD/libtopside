#include "LocalCtrl.h"

NAMESPACE_TOPSIDE_BEGIN

#ifndef LIBTOPSIDE

#define IMAGECLASS Images
#define IMAGEFILE <LocalCtrl/Images.iml>
#include IML_SOURCE
#undef IMAGECLASS
#undef IMAGEFILE

#define IMAGECLASS DbgImages
#define IMAGEFILE <LocalCtrl/DbgImages.iml>
#include IML_SOURCE
#undef IMAGECLASS
#undef IMAGEFILE

#endif

NAMESPACE_TOPSIDE_END
