#ifndef _AccelAudio_TestChains_h_
#define _AccelAudio_TestChains_h_


CHAIN3(TestMidiAudioChain, TestMidiAudioPart1, TestMidiAudioPart2, TestMidiAudioPart3, "0112")
CHAIN2(TestMidiAudioTopChainPart1, TestMidiAudioPart1, TestMidiAudioPart2, "01")


#endif
