#include "OuluCtrl.h"

NAMESPACE_OULU_BEGIN

#define IMAGECLASS Images
#define IMAGEFILE <OuluCtrl/Images.iml>
#include IML_SOURCE
#undef IMAGECLASS
#undef IMAGEFILE

#define IMAGECLASS DbgImages
#define IMAGEFILE <OuluCtrl/DbgImages.iml>
#include IML_SOURCE
#undef IMAGECLASS
#undef IMAGEFILE

NAMESPACE_OULU_END
