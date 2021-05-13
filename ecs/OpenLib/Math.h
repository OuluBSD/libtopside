#ifndef _OpenLib_Math_h_
#define _OpenLib_Math_h_

NAMESPACE_OULU_BEGIN



namespace LocationUtil {


inline vec3 position(const SpatialInteractionSourceLocation& location) {
	return !location.pos.IsNull() ? location.pos : zero<vec3>();
}

inline quat orientation(const SpatialInteractionSourceLocation& location) {
	return !location.orient.IsNull() ? location.orient : identity<quat>();
}

inline mat4 Matrix(const SpatialInteractionSourceLocation& location) {
	return make_mat4_from_quat(orientation(location)) * translate(position(location));
}

}



NAMESPACE_OULU_END

#endif
