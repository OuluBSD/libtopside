#include "Oulu.h"


NAMESPACE_OULU_BEGIN


VideoFormat MakeVideoFormat(Size res, double fps, int var_size, int channels, int pitch) {
	VideoFormat f;
	f.res = res;
	f.fps = fps;
	f.var_size = var_size;
	f.channels = channels;
	f.pitch = pitch;
	return f;
}



void VolatileVideoBuffer::Clear() {
	
}

void VolatileVideoBuffer::SetSize(VideoFormat vid_fmt, int frames) {
	this->vid_fmt = vid_fmt;
	this->frames = frames;
	frame_size = vid_fmt.pitch * vid_fmt.res.cy;
	ASSERT(vid_fmt.var_size >= 1);
	ASSERT(vid_fmt.channels >= 1);
	ASSERT(vid_fmt.pitch >= 1);
	ASSERT(frames >= 2);
	int total = frame_size * frames;
	ASSERT(total > 0 && total < size_limit);
	for(int i = 0; i < 2; i++)
		data[i].SetCount(total);
}

void VolatileVideoBuffer::Zero() {
	if (!IsEmpty())
		for(int i = 0; i < 2; i++)
			memset(data[i].Begin(), 0, data[i].GetCount());
	data_i = 0;
	read_pos = 0;
	write_pos = 0;
	queue_size = 0;
}

void VolatileVideoBuffer::Exchange(VideoEx& e) {
	if (e.IsLoading()) {
		
	}
	else if (e.IsStoring()) {
		
	}
	else
		Panic("Invalid exchange");
	TODO
}

bool VolatileVideoBuffer::CheckSize(int size_) {
	ASSERT(!IsEmpty());
	if (IsEmpty())
		return false;
	int size_frames = size_ / frame_size;
	ASSERT(size_ % frame_size == 0);
	if (!size_frames)
		return false;
	return true;
}

#ifdef flagOPENGL
bool VolatileVideoBuffer::PaintOpenGLTexture(int texture) {
	TODO
}
#endif

void VideoFormat::Clear() {
	res = Size(0,0);
	fps = 0;
	var_size = 0;
	channels = 0;
	pitch = 0;
}





NAMESPACE_OULU_END
