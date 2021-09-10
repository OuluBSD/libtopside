#ifndef _AtomLocal_AtomLocal_h_
#define _AtomLocal_AtomLocal_h_

#include <SerialLib/SerialLib.h>

//#define HAVE_MANUAL_DBG_CLASSES 1

#include "Internal.h"

#include "Customer.h"

#include "Audio.h"
#include "Record.h"
#include "Video.h"
#include "Media.h"
#include "FfmpegFileIn.h"
#include "Ffmpeg.h"
#include "PortaudioCore.h"
#include "Portaudio.h"
#include "Sdl.h"



#if HAVE_MANUAL_DBG_CLASSES

#else
	#include "Generated.h"
#endif


NAMESPACE_SERIAL_BEGIN


template <> inline
SideStatus MakeSide<AudioSideSink>(
	const AtomTypeCls& from_type,
	const Script::WorldState& from,
	const AtomTypeCls& to_type,
	const Script::WorldState& to) {
	ValDevCls f = from.GetSideCls();
	ValDevCls t = to.GetSideCls();
	if (f.val != t.val)
		return SIDE_NOT_ACCEPTED;
	bool accept_multiple = to_type.IsMultiSideConnection();
	return accept_multiple ? SIDE_ACCEPTED_MULTI : SIDE_ACCEPTED;
}

template <> inline
SideStatus MakeSide<AudioSideSrc>(
	const AtomTypeCls& from_type,
	const Script::WorldState& from,
	const AtomTypeCls& to_type,
	const Script::WorldState& to) {
	ValDevCls f = from.GetSideCls();
	ValDevCls t = to.GetSideCls();
	if (f.val != t.val)
		return SIDE_NOT_ACCEPTED;
	bool accept_multiple = to_type.IsMultiSideConnection();
	return accept_multiple ? SIDE_ACCEPTED_MULTI : SIDE_ACCEPTED;
}


NAMESPACE_SERIAL_END


#endif
