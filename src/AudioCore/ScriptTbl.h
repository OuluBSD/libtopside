#ifndef _AudioCore_SCRIPTTBL_H
#define _AudioCore_SCRIPTTBL_H

NAMESPACE_AUDIO_BEGIN

#define __SK_MaxMsgTypes_ 80

struct ScriptSpec {
	char messageString[32];
	long type;
	long data2;
	long data3;
};

extern struct ScriptSpec skini_msgs[__SK_MaxMsgTypes_];


NAMESPACE_AUDIO_END

#endif
