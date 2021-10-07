#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


Format GetDefaultFormat(ValDevCls type) {
	//DUMP(type)
	Format fmt;
	
	if (type.val == ValCls::AUDIO) {
		fmt.SetAudio(type.dev, SoundSample::FLT_LE, 2, 44100, 1024);
	}
	else if (type.val == ValCls::ORDER) {
		fmt.SetOrder(type.dev);
	}
	else if (type.val == ValCls::RECEIPT) {
		fmt.SetReceipt(type.dev);
	}
	else if (type.val == ValCls::MIDI) {
		fmt.SetMidi(type.dev);
	}
	else if (type.val == ValCls::VIDEO) {
		fmt.SetVideo(type.dev, LightSampleFD::U8_LE_ABC, 1280, 720, 60, 1);
	}
	else if (type.val == ValCls::EVENT) {
		fmt.SetEvent(type.dev);
	}
	else if (type.val == ValCls::FBO) {
		fmt.SetFbo(type.dev, LightSampleFD::U8_LE_ABC, 1280, 720, 60, 1);
	}
	else {
		TODO
	}
	
	return fmt;
}


NAMESPACE_SERIAL_END
