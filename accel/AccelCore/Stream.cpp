#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN



const char* AcceleratorHeader::type_names[ACCEL_TYPE_COUNT+1] = {
	#define ACCEL_TYPE_ITEM(x,y) y,
	ACCEL_TYPE_LIST
	#undef ACCEL_TYPE_ITEM
	0
};

const char* AcceleratorHeader::filter_names[ACCEL_FILTER_COUNT+1] = {
	#define ACCEL_FILTER_ITEM(x,y) y,
	ACCEL_FILTER_LIST
	#undef ACCEL_FILTER_ITEM
	0
};

const char* AcceleratorHeader::wrap_names[ACCEL_WRAP_COUNT+1] = {
	#define ACCEL_WRAP_ITEM(x,y) y,
	ACCEL_WRAP_LIST
	#undef ACCEL_WRAP_ITEM
	0
};




String AcceleratorHeader::GetStringFromType(Type i) {
	return type_names[(int)i];
}

String AcceleratorHeader::GetStringFromFilter(Filter i) {
	ASSERT(i >= 0 && i < ACCEL_FILTER_COUNT);
	return filter_names[(int)i];
}

String AcceleratorHeader::GetStringFromWrap(Wrap i) {
	return wrap_names[(int)i];
}

AcceleratorHeader::Type AcceleratorHeader::GetTypeFromString(String s) {
	#define ACCEL_TYPE_ITEM(x,y) if (s == y) return x;
	ACCEL_TYPE_LIST
	#undef ACCEL_TYPE_ITEM
	return TYPE_INVALID;
}

AcceleratorHeader::Filter AcceleratorHeader::GetFilterFromString(String s) {
	#define ACCEL_FILTER_ITEM(x,y) if (s == y) return x;
	ACCEL_FILTER_LIST
	#undef ACCEL_FILTER_ITEM
	return FILTER_INVALID;
}

AcceleratorHeader::Wrap AcceleratorHeader::GetWrapFromString(String s) {
	#define ACCEL_WRAP_ITEM(x,y) if (s == y) return x;
	ACCEL_WRAP_LIST
	#undef ACCEL_WRAP_ITEM
	return WRAP_INVALID;
}

void AcceleratorHeader::Set(int id, Type t, String path, Filter filter, Wrap wrap, bool vflip) {
	this->id = id;
	this->type = t;
	this->filepath = path;
	this->filter = filter;
	this->wrap = wrap;
	this->vflip = vflip;
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
	astream = in.astream;
	vstream = in.vstream;
}

bool AcceleratorHeader::IsTypeComponentSource(Type i) {
	#define IFACE(x) \
		if (i == AsTypeCls<Accel##x##PipeComponent>()) return true; \
		if (i == AsTypeCls<ConvertCenterAccel##x##InputComponent>()) return true;
	IFACE_LIST
	#undef IFACE
	return false;
}











void AccelStream::Clear() {
	//name.Clear();
	//description.Clear();
	time = Time(2020,1,1);
	total_time.Reset();
	frame_seconds = 0;
	time_us = 0;
	
	mouse = Point(0,0);
	mouse_toycompat_drag = Point(0,0);
	mouse_toycompat_click = Point(0,0);
	
	draw = 0;
	video_size = Size(640,480);
	video_offset = Point(0,0);
	mouse = Point(0,0);
	vframe_time.Reset();
	vtotal_seconds = 0;
	vframes = 0;
	fps_limit = 60;// Real
	
	//sys_aud = 0;
	//aframe_time.Reset();
	//audio_sync_ival = 1.0f;
	atotal_seconds = 0;
	audio_last_sync_sec = 0;
	/*audio_sample_freq = 0;
	audio_sample_rate = 0;
	audio_sample_size = 0;
	audio_sample_channels = 0;*/
	aud_fmt.Set(SoundSample::FLT_LE, 2, 44100, 1024);
	aframes = 0;
	aframes_after_sync = 0;
	asink_frame = 0;
	is_audio_sync = false;
}

void AccelStream::Reset() {
	vframe_time.Reset();
	vframes = 0;
	audio_last_sync_sec = 0;
}













int AcceleratorHeaderVector::Find(const AcceleratorHeader& a) const {
	int i = 0;
	for (AcceleratorHeader& b : in) {
		if (a.IsEqualHeader(b))
			return i;
		++i;
	}
	return -1;
}

void AcceleratorHeaderVector::Add(const AcceleratorHeader& a) {
	ASSERT(Find(a) < 0);
	in.Add(a);
}




NAMESPACE_TOPSIDE_END
