#include "LocalCtrl.h"

NAMESPACE_TOPSIDE_BEGIN

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

NAMESPACE_TOPSIDE_END
