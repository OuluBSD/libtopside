#ifndef _FreeLib_Math_h_
#define _FreeLib_Math_h_

NAMESPACE_TOPSIDE_BEGIN



namespace LocationUtil {


inline vec3 position(const SpatialInteractionSourceLocation& location) {
	return !location.pos.IsNull() ? location.pos : zero<vec3>();
}

inline quat orientation(const SpatialInteractionSourceLocation& location) {
	return !location.orient.IsNull() ? location.orient : Identity<quat>();
}

inline mat4 Matrix(const SpatialInteractionSourceLocation& location) {
	return QuatMat(orientation(location)) * Translate(position(location));
}

}



NAMESPACE_TOPSIDE_END

#endif
