#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


VideoFormat MakeVideoFormat(Size res, double fps, int var_size, int channels, int pitch, int depth, String codec) {
	VideoFormat f;
	f.res = res;
	f.depth = depth;
	f.fps = fps;
	f.var_size = var_size;
	f.channels = channels;
	if (pitch <= 0)
		pitch = res.cx * var_size * channels;
	f.pitch = pitch;
	f.codec = codec;
	ASSERT(f.IsValid());
	return f;
}



#if HAVE_OPENGL
template <>
bool ContextT<VideoContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif



void VideoFormat::Clear() {
	res = Size(0,0);
	depth = 0;
	fps = 0;
	var_size = 0;
	channels = 0;
	pitch = 0;
	codec.Clear();
}





NAMESPACE_TOPSIDE_END
