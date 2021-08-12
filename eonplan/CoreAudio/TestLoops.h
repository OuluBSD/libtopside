#ifndef _CoreAudio_TestLoops_h_
#define _CoreAudio_TestLoops_h_

NAMESPACE_PLAN_BEGIN


LOOP3(TestAudio,		Customer,	DefAudioGenerator,		DefAudioHardwareSink)
LOOP3(TestAudioPart1,	Customer,	DefAudioGenerator,		DefAudioSideSink)
LOOP3(TestAudioPart2,	Customer,	DefAudioSideSrc,		DefAudioHardwareSink)


NAMESPACE_PLAN_END

#endif
