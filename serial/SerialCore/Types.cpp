#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


Format GetDefaultFormat(ValDevCls type) {
	//DUMP(type)
	Format fmt;
	
	if (type.dev == DevCls::CENTER ||
		type.dev == DevCls::ACCEL) {
		if (type.val == ValCls::AUDIO) {
			fmt.SetAudio(SoundSample::FLT_LE, 2, 44100, 1024);
		}
		else if (type.val == ValCls::ORDER) {
			fmt.SetOrder();
		}
		else if (type.val == ValCls::RECEIPT) {
			fmt.SetReceipt();
		}
		else if (type.val == ValCls::MIDI) {
			fmt.SetMidi();
		}
		else {
			TODO
		}
	}
	else {
		TODO
	}
	
	return fmt;
}


NAMESPACE_SERIAL_END
