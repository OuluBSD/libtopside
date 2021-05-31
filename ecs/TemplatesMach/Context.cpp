#include "TemplatesMach.h"


NAMESPACE_TOPSIDE_BEGIN


#if HAVE_OPENGL
template <>
bool ContextDataT<AudioContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<VideoContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<DisplayContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<StaticContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<EventContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<PhotoContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<ModelContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<MidiContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ContextDataT<HumanContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif


NAMESPACE_TOPSIDE_END
