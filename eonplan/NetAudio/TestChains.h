#ifndef _NetAudio_TestChains_h_
#define _NetAudio_TestChains_h_

CHAIN1(TestRemoteAudioGenLocalPart1,
	TestCenterNetOrderSrc,
	"")

CHAIN2(TestRemoteAudioGenLocalPart2,
	TestNetCenterAudioSink,
	TestAudioPart2,
	"")

CHAIN1(TestRemoteAudioGenRemote,
	TestNetAudioSrc,
	"")


#endif
