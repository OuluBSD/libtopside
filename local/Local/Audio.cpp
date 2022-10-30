#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN




MAKE_STATIC(GlobalAudioTime, audtime);

GlobalAudioTime& GlobalAudioTime::Local() {
	return audtime;
}


NAMESPACE_TOPSIDE_END

