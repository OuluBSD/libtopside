#ifndef _DAW_Loops_h_
#define _DAW_Loops_h_

NAMESPACE_PLAN_BEGIN


LOOP4(DawMidiInstrument,
	Customer,
	DawMidiSrc,
	DawMidiAudioConv,
	DawAudioFx)
	
LOOP3(DawFxChannel,
	Customer,
	DawAudioIn,
	DawAudioFx)

LOOP4(DawMasterChannel,
	Customer,
	DawAudioIn,
	DawAudioFx,
	DawAudioHwOutSrc)

LOOP3(DawHwSink,
	Customer,
	DawAudioOutSink,
	DefAudioSideSink)

LOOP3(DawFileSink,
	Customer,
	DawAudioOutSink,
	DefAudioFileSink)


NAMESPACE_PLAN_END

#endif
