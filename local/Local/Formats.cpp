#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


#if HAVE_OPENGL
template <>
bool ContextT<AudioContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif


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







void AVMediaProxy::Exchange(MediaEx& e) {
	TODO
}

int AVMediaProxy::GetQueueSize() const {
	TODO
}

MediaFormat AVMediaProxy::GetFormat() const {
	TODO
}

bool AVMediaProxy::IsQueueFull() const {
	TODO
}




#if HAVE_OPENGL
template <>
bool ContextT<DisplayContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif








#if 0
template <>
bool ContextT<MediaContext>::SimpleStream::FindClosestFormat(const MediaFormat& fmt, int& idx) {
	// Size cap_sz, double fps, double bw_min, double bw_max, int& ret_fmt, int& ret_res
	double tgt_bw = (double)cap_sz.cx * (double)cap_sz.cy * (double)fps;
	double bw_low = bw_min * tgt_bw;
	double bw_high = bw_max * tgt_bw;
	if (bw_low > bw_high)
		return false;
	
	struct Result : Moveable<Result> {
		double diff;
		int fmt, res;
		bool operator()(const Result& a, const Result& b) const {return a.diff < b.diff;}
	};
	Vector<Result> results;
	
	for(int i = 0; i < fmts.GetCount(); i++) {
		const VideoSourceFormat& fmt = fmts[i];
		for(int j = 0; j < fmt.GetResolutionCount(); j++) {
			const VideoSourceFormatResolution& fmt_res = fmt.GetResolution(j);
			VideoFormat vid_fmt = fmt_res.GetFormat();
			Size fmt_sz = vid_fmt.res;
			double fmt_fps = vid_fmt.fps;
			double fmt_bw = (double)fmt_sz.cx * (double)fmt_sz.cy * fmt_fps;
			if (fmt_bw >= bw_low && fmt_bw <= bw_high) {
				Result& r = results.Add();
				r.diff = fabs(tgt_bw - fmt_bw);
				r.fmt = i;
				r.res = j;
			}
		}
	}
	if (results.GetCount()) {
		Sort(results, Result());
		if (0) {
			for(int i = 0; i < results.GetCount(); i++) {
				const Result& r = results[i];
				LOG(i << ": " << r.diff << ": " << r.fmt << ", " << r.res);
			}
		}
		const Result& res = results[0];
		ret_fmt = res.fmt;
		ret_res = res.res;
		return true;
	}
	return false;
}
#endif








void AcceleratorHeader::Set(int id, Type t, String path, int filter, int wrap, bool vflip) {
	this->id = id;
	this->type = t;
	this->filepath = path;
	this->filter = filter;
	this->wrap = wrap;
	this->vflip = vflip;
}

#define VALUE(str, i) if (t == i) return #str;

String AcceleratorHeader::GetStringFromType(AcceleratorHeader::Type t) {
	VALUE(texture, TEXTURE);
	VALUE(cubemap, CUBEMAP);
	VALUE(webcam, WEBCAM);
	VALUE(music, MUSIC);
	VALUE(musicstream, MUSICSTREAM);
	VALUE(keyboard, KEYBOARD);
	VALUE(volume, VOLUME);
	VALUE(video, VIDEO);
	VALUE(buffer, BUFFER);
	VALUE(empty, EMPTY);
	return "invalid";
}

#undef VALUE

#define VALUE(str, i) if (s == #str) return i;

AcceleratorHeader::Type AcceleratorHeader::GetTypeFromString(String s) {
	VALUE(texture, TEXTURE);
	VALUE(cubemap, CUBEMAP);
	VALUE(webcam, WEBCAM);
	VALUE(music, MUSIC);
	VALUE(musicstream, MUSICSTREAM);
	VALUE(keyboard, KEYBOARD);
	VALUE(volume, VOLUME);
	VALUE(video, VIDEO);
	VALUE(buffer, BUFFER);
	VALUE(empty, EMPTY);
	return INVALID;
}

int AcceleratorHeader::GetFilterFromString(String s) {
	VALUE(nearest, FILTER_NEAREST);
	VALUE(linear, FILTER_LINEAR);
	VALUE(mipmap, FILTER_MIPMAP);
	return DEFAULT_FILTER;
}

int AcceleratorHeader::GetWrapFromString(String s) {
	VALUE(clamp, WRAP_CLAMP);
	VALUE(repeat, WRAP_REPEAT);
	return DEFAULT_WRAP;
}

bool AcceleratorHeader::IsEqualHeader(const AcceleratorHeader& i) const {
	return	filepath == i.filepath &&
			type == i.type &&
			wrap == i.wrap &&
			filter == i.filter &&
			vflip == i.vflip;
}

void AcceleratorHeader::SetHeader(const AcceleratorHeader& i) {
	filepath = i.filepath;
	type = i.type;
	wrap = i.wrap;
	filter = i.filter;
	vflip = i.vflip;
}

void AcceleratorHeader::CopyIdStream(const AcceleratorHeader& in) {
	id = in.id;
	stream = in.stream;
}

#undef VALUE





















int AcceleratorHeaderVector::Find(const AcceleratorHeader& a) const {
	for(int i = 0; i < in.GetCount(); i++) {
		const AcceleratorHeader& b = in[i];
		if (a.IsEqualHeader(b))
			return i;
	}
	return -1;
}

void AcceleratorHeaderVector::Add(const AcceleratorHeader& a) {
	in.Add().SetHeader(a);
}







#if HAVE_OPENGL
template <>
bool ContextT<StaticContext>::PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}
#endif


NAMESPACE_TOPSIDE_END
