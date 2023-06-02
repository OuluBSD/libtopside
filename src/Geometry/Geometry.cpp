#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK_(Geometry) {
	#define NO_CONST_V
	#undef OBJ_TYPE_NO
	#define OBJ_TYPE_NO(t, v) Object::RegisterType<t>(v, #t);
	#include "Types.inl"
	#undef OBJ_TYPE_NO
	#define OBJ_TYPE_NO(x, y) OBJ_TYPE_NO_(x,y)
	#undef NO_CONST_V
	
}


NAMESPACE_TOPSIDE_END
