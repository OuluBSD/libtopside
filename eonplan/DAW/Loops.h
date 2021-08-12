
LOOP5(DawMidiInstrument,
	AccelCustomer,
	DawMidiSrc,
	DawMidiAudioConv,
	DawAudioFx,
	DawAudioOut)
	
LOOP4(DawFxChannel,
	AccelCustomer,
	DawAudioIn,
	DawAudioFx,
	DawAudioOut)

LOOP4(DawMasterChannel,
	AccelCustomer,
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
