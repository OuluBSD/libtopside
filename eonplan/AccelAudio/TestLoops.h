#ifndef _AccelAudio_TestLoops_h_
#define _AccelAudio_TestLoops_h_

NAMESPACE_PLAN_BEGIN


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


NAMESPACE_PLAN_END

#endif
