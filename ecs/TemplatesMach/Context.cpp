#include "TemplatesMach.h"


NAMESPACE_TOPSIDE_BEGIN


#if HAVE_OPENGL
template <>
bool ContextT<AudioContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextT<VideoContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextT<DisplayContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextT<StaticContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif


NAMESPACE_TOPSIDE_END
