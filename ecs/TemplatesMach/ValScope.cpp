#include "TemplatesMach.h"


NAMESPACE_TOPSIDE_BEGIN


#if HAVE_OPENGL
template <>
bool ScopeValMachT<AudioSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<VideoSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<DisplaySpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<StaticSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<EventSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<PhotoSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<ModelSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<MidiSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

template <>
bool ScopeValMachT<HumanSpec>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif


NAMESPACE_TOPSIDE_END
