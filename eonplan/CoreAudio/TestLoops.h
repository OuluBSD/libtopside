#ifndef _CoreAudio_TestLoops_h_
#define _CoreAudio_TestLoops_h_


LOOP3(TestAudio,		Customer,	DefAudioGenerator,		DefAudioHardwareSink)
LOOP3(TestAudioPart1,	Customer,	DefAudioGenerator,		DefAudioSideSink)
LOOP3(TestAudioPart2,	Customer,	DefAudioSideSrc,		DefAudioHardwareSink)


#endif
