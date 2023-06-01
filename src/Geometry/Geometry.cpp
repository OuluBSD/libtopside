#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK_(Geometry) {
	#define NO_CONST_V
	#undef OBJ_TYPE_NO
	#define OBJ_TYPE_NO(t, v) Object::RegisterType<t>(v, #t);
	#include "Types.inl"
	#undef OBJ_TYPE_NO
	#undef NO_CONST_V
	
}


NAMESPACE_TOPSIDE_END
