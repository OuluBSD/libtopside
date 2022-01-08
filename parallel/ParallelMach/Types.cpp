#include "ParallelMach.h"

NAMESPACE_PARALLEL_BEGIN






DevCls GetCenterDevCls() {
	DevCls c;
	c.type = DevCls::CENTER;
	return c;
}


String ValCls::GetName(Type t) {
	switch (t) {
		case AUDIO:			return "audio";
		case VIDEO:			return "video";
		case VOLUME:		return "volume";
		case MIDI:			return "midi";
		case EVENT:			return "event";
		case DATA:			return "data";
		case ORDER:			return "order";
		case RECEIPT:		return "receipt";
		case FBO:			return "fbo";
		case INVALID:
		default: return "invalid";
	}
}

ValCls::Type ValCls::Get(String s) {
	if (s == "audio")
		return AUDIO;
	if (s == "video")
		return VIDEO;
	if (s == "midi")
		return MIDI;
	if (s == "event")
		return EVENT;
	if (s == "data")
		return DATA;
	if (s == "order")
		return ORDER;
	if (s == "receipt")
		return RECEIPT;
	if (s == "fbo")
		return FBO;
	
	return INVALID;
}



String DevCls::GetName(Type t) {
	switch (t) {
		case CENTER:	return "center";
		case PERMA:		return "perma";
		case NET:		return "net";
		case OGL:		return "ogl";
		case INVALID:
		default: return "invalid";
	}
}

DevCls::Type DevCls::Get(String s) {
	if (s == "center")
		return CENTER;
	if (s == "perma")
		return PERMA;
	if (s == "ogl")
		return OGL;
	if (s == "net")
		return NET;
	if (s == "ogl")
		return OGL;
	
	return INVALID;
}









NAMESPACE_PARALLEL_END
