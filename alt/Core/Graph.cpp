#include "Core.h"

NAMESPACE_UPP_BEGIN

bool operator==(const RGBA& a, const RGBA& b) {return MemoryCompare(&a, &b, sizeof(RGBA)) == 0;}
bool operator==(const RGBAf& a, const RGBAf& b) {return MemoryCompare(&a, &b, sizeof(RGBAf)) == 0;}


NAMESPACE_UPP_END
