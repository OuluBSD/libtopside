#ifndef _AccelAudio_TestChains_h_
#define _AccelAudio_TestChains_h_

NAMESPACE_PLAN_BEGIN


CHAIN3(TestMidiAudioChain, TestMidiAudioPart1, TestMidiAudioPart2, TestMidiAudioPart3, "0112")
CHAIN2(TestMidiAudioTopChainPart1, TestMidiAudioPart1, TestMidiAudioPart2, "01")


NAMESPACE_PLAN_END

#endif
