#include "TemplatesMach.h"


NAMESPACE_TOPSIDE_BEGIN


#if HAVE_OPENGL
template <>
bool ContextMachT<AccelAudioContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextMachT<AccelVideoContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextMachT<AccelDisplayContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextMachT<AccelStaticContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextMachT<AccelEventContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextMachT<AccelPhotoContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif


NAMESPACE_TOPSIDE_END
