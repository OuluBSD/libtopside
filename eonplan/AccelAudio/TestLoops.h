
LOOP3(TestMidiAudioPart1,
	Customer,
	TestMidiSrc,
	TestCenterAccelMidiSrc)

LOOP4(TestMidiAudioPart2,
	AccelCustomer,
	TestCenterAccelMidiSink,
	TestAccelMidiAudioConv,
	TestAccelCenterAudioSink)

LOOP3(TestMidiAudioPart3,
	Customer,
	TestAccelCenterAudioSrc,
	DefAudioHardwareSink)
